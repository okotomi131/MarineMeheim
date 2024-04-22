/*********************************************************************
 * @file   DirectXWriteFont.cpp
 * @brief  テキスト描画用のフォント読み込み
 *********************************************************************/
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "DirectXWriteFont.h"

/*
===================================================================

	フォント読み込み

===================================================================
*/

FontFileEnumerator::FontFileEnumerator(
	IDWriteFactory* factory, const std::vector<std::wstring>& FilePath)
	:m_refCnt(0), m_Factory(factory), m_FilePath(FilePath), m_curFileIdx(-1)
{
	//- ファクトリーの参照カウントを増やす
	m_Factory->AddRef();
}

FontFileEnumerator::~FontFileEnumerator()
{
	Release_and_Null(m_Factory, "m_Factory");
}


IFACEMETHODIMP FontFileEnumerator::QueryInterface(REFIID iid, void** ppvObject)
{
	if (iid == __uuidof(IUnknown) || iid == __uuidof(IDWriteFontCollectionLoader))
	{
		*ppvObject = this;
		AddRef();
		return S_OK;
	}
	else
	{
		*ppvObject = nullptr;
		return E_NOINTERFACE;
	}
}

IFACEMETHODIMP_(ULONG) FontFileEnumerator::AddRef()
{
	return InterlockedIncrement(&m_refCnt);
}

IFACEMETHODIMP_(ULONG) FontFileEnumerator::Release()
{
	ULONG newCount = InterlockedDecrement(&m_refCnt);
	if (newCount == 0){	delete this;	}

	return newCount;
}

IFACEMETHODIMP FontFileEnumerator::MoveNext(OUT BOOL* hasCurrentFile)
{
	if (++m_curFileIdx < static_cast<int>(m_FilePath.size()))
	{
		*hasCurrentFile = TRUE;
		return S_OK;
	}
	else
	{
		*hasCurrentFile = FALSE;
		return S_OK;
	}
}

IFACEMETHODIMP FontFileEnumerator::GetCurrentFontFile(OUT IDWriteFontFile** fontFile)
{
	//- フォントファイルを読み込む
	return m_Factory->CreateFontFileReference(
		m_FilePath[m_curFileIdx].c_str(), nullptr, fontFile);
}


/*
===================================================================

	フォントコレクション読み込み用

===================================================================
*/
FontCollectionLoader::FontCollectionLoader()
	:m_refCnt(0)
{
}

IFACEMETHODIMP FontCollectionLoader::QueryInterface(REFIID iid, void** ppvObject)
{
	if (iid == __uuidof(IUnknown) || iid == __uuidof(IDWriteFontCollectionLoader))
	{
		*ppvObject = this;
		AddRef();
		return S_OK;
	}
	else
	{
		*ppvObject = nullptr;
		return E_NOINTERFACE;
	}
}

IFACEMETHODIMP_(ULONG) FontCollectionLoader::AddRef()
{
	return InterlockedIncrement(&m_refCnt);
}

IFACEMETHODIMP_(ULONG) FontCollectionLoader::Release()
{
	ULONG newCount = InterlockedDecrement(&m_refCnt);
	if (newCount == 0){	delete this;}

	return newCount;
}

IFACEMETHODIMP FontCollectionLoader::CreateEnumeratorFromKey(
	IDWriteFactory* factory, void const* collectionKey, 
	UINT32 collectionKeySize, OUT IDWriteFontFileEnumerator** fontFileEnumerator)
{
	//- 読み込むフォントファイルのパスを渡す
	std::vector<std::wstring> fontFilePaths(
		std::begin(FontList::FontPath), std::end(FontList::FontPath));

	//- カスタムフォントファイル列挙子の作成
	*fontFileEnumerator = new (std::nothrow) FontFileEnumerator(factory, fontFilePaths);

	//- メモリ不足の場合はエラーを返す
	if (*fontFileEnumerator == nullptr) { return E_OUTOFMEMORY; }

	return S_OK;
}


/*
===================================================================

	DirectXWrite

===================================================================
*/

HRESULT DirectXWriteFont::Init(IDXGISwapChain* swapChain)
{
	HRESULT hr = S_OK;

	//- Direct2Dファクトリ情報の初期化
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, m_p2DFactory.GetAddressOf());
	if (FAILED(hr)) { return hr; }

	//- バックバッファの取得
	hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&m_pBackBuffer));
	if (FAILED(hr)) { return hr; }

	//- dpiの設定
	FLOAT dpiX;
	FLOAT dpiY;
	m_p2DFactory->GetDesktopDpi(&dpiX, &dpiY);

	//- レンダーターゲットの作成
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	//- サーフェスに描画するレンダーターゲットを作成
	hr = m_p2DFactory->CreateDxgiSurfaceRenderTarget(m_pBackBuffer.Get(), &props, m_pRednerTarget.GetAddressOf());
	if (FAILED(hr)) { return hr; }

	//- アンチエイリアシングモードの設定
	m_pRednerTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	//- IDWriteFactoryの作成
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(m_pWriteFactory.GetAddressOf()));
	if (FAILED(hr)) { return hr; }

	//- カスタムフォントコレクションローダー
	m_pFontCollectionLoader = new FontCollectionLoader();
	
	//- カスタムフォントコレクションローダーの作成
	hr = m_pWriteFactory->RegisterFontCollectionLoader(m_pFontCollectionLoader.Get());
	if (FAILED(hr)) { return hr; }

	//- フォントファイルの読み込み
	hr = Load();
	if (FAILED(hr)) { return hr; }

	//- フォントを設定
	hr = Set_Font(m_FontData);
	if (FAILED(hr)) { return hr; }

	return hr;
}

HRESULT DirectXWriteFont::Load()
{
	HRESULT result = S_OK;
	

	//- カスタムフォントコレクションの作成
	result = m_pWriteFactory->CreateCustomFontCollection(
		m_pFontCollectionLoader.Get(),
		m_pFileList.data(),
		m_pFileList.size(),
		&m_pFontCollection
	);
	if (FAILED(result)) { return result; }

	//- フォント名を取得
	result = Get_FontFamilyName(m_pFontCollection.Get());
	
	if (FAILED(result)) { return result; }

	return S_OK;
}

HRESULT DirectXWriteFont::Draw_String(
	std::string text,DirectX::XMFLOAT2 pos,D2D1_DRAW_TEXT_OPTIONS option)
{
	HRESULT result = S_OK;

	//- 文字列の変換
	std::wstring wstr = Str2Wstr(text.c_str());

	//- ターゲットサイズの取得
	D2D1_SIZE_F TargetSize = m_pRednerTarget->GetSize();

	//- テキストレイアウトを作成
	result = m_pWriteFactory->CreateTextLayout(
		wstr.c_str(), wstr.size(), m_pTextFormat.Get(), TargetSize.width,
		TargetSize.height, m_pTextLayout.GetAddressOf());
	if (FAILED(result)) { return result; }

	//- 描画位置の確定
	D2D1_POINT_2F pounts;
	pounts.x = pos.x;
	pounts.y = pos.y;

	//- 描画の開始
	m_pRednerTarget->BeginDraw();

	//- 描画処理
	m_pRednerTarget->DrawTextLayout(pounts, m_pTextLayout.Get(), m_pColorBrush.Get(), option);

	//- 描画の終了
	result = m_pRednerTarget->EndDraw();
	if (FAILED(result)) { return result; }

	return S_OK;
}


HRESULT DirectXWriteFont::Set_Font(FontData data)
{
	HRESULT result = S_OK;

	//- 設定をコピー
	m_FontData = data;

	result = m_pWriteFactory->CreateTextFormat
	(
		Get_FileNameOutExtension(m_FontData.wName.c_str()),
		m_pFontCollection.Get(),
		m_FontData.weight,
		m_FontData.style,
		m_FontData.stretch,
		m_FontData.size,
		m_FontData.localeName,
		m_pTextFormat.GetAddressOf()
	);
	if (FAILED(result)) { return result; }

	result = m_pTextFormat->SetTextAlignment(m_FontData.alignment);
	if (FAILED(result)) { return result; }

	result = m_pRednerTarget->CreateSolidColorBrush(m_FontData.color, m_pColorBrush.GetAddressOf());
	if (FAILED(result)) { return result; }
	
	return result;
}

std::wstring DirectXWriteFont::Get_FontName(int index)
{
	//- フォント名のリストが空だった場合
	if (m_NameList.empty()){	return nullptr;}

	//- リストのサイズを超えていた場合
	if (index >= static_cast<int>(m_NameList.size()))
	{	return m_NameList[0];	}
	return m_NameList[index];
}

HRESULT DirectXWriteFont::Get_FontFamilyName(IDWriteFontCollection* collection, const WCHAR* locale)
{
	HRESULT result = S_OK;

	//- フォントファミリー名一覧をリセット
	std::vector<std::wstring>().swap(m_NameList);
	//- フォントの数を取得
	UINT32 familyCount = collection->GetFontFamilyCount();
	for (UINT32 i = 0; i < familyCount; i++)
	{
		//- フォントファミリーの取得
		WRL::ComPtr <IDWriteFontFamily> fontFamily = nullptr;
		result = collection->GetFontFamily(i, fontFamily.GetAddressOf());
		if (FAILED(result)) { return result; }
		//- フォントファミリー名の一覧を取得
		WRL::ComPtr <IDWriteLocalizedStrings> familyNames = nullptr;
		result = fontFamily->GetFamilyNames(familyNames.GetAddressOf());
		if (FAILED(result)) { return result; }
		//- 指定されたロケールに対応するインデックスを検索
		UINT32 index = 0;
		BOOL exists = FALSE;
		result = familyNames->FindLocaleName(locale, &index, &exists);
		if (FAILED(result)) { return result; }
		//- 指定されたロケールが見つからなかった場合は、デフォルトのロケールを使用
		if (!exists)
		{
			result = familyNames->FindLocaleName(L"en-us", &index, &exists);
			if (FAILED(result)) { return result; }
		}
		//- フォントファミリー名の長さを取得
		UINT32 length = 0;
		result = familyNames->GetStringLength(index, &length);
		if (FAILED(result)) { return result; }
		//- フォントファミリー名の取得
		WCHAR* name = new WCHAR[length + 1];
		result = familyNames->GetString(index, name, length + 1);
		if (FAILED(result)) { return result; }
		//- フォントファミリー名を追加
		m_NameList.push_back(name);
		//- フォントファミリー名の破棄
		delete[] name;
	}
	return result;
}

HRESULT DirectXWriteFont::Get_AllFamilyFontName(IDWriteFontCollection* collection)
{
	HRESULT result = S_OK;

	//- フォントファミリー名一覧をリセット
	std::vector<std::wstring>().swap(m_NameList);
	//- フォントファミリーの数を取得
	UINT32 familyCount = collection->GetFontFamilyCount();

	for (UINT32 i = 0; i < familyCount; i++)
	{
		//- フォントファミリーの取得
		WRL::ComPtr <IDWriteFontFamily> fontFamily = nullptr;
		result = collection->GetFontFamily(i, fontFamily.GetAddressOf());
		if (FAILED(result)) { return result; }
		//- フォントファミリー名の一覧を取得
		WRL::ComPtr <IDWriteLocalizedStrings> familyNames = nullptr;
		result = fontFamily->GetFamilyNames(familyNames.GetAddressOf());
		if (FAILED(result)) { return result; }
		//- フォントファミリー名の数を取得
		UINT32 nameCount = familyNames->GetCount();

		//- フォントファミリー名の数だけ繰り返す
		for (UINT32 j = 0; j < nameCount; ++j)
		{
			//- フォントファミリー名の長さを取得
			UINT32 length = 0;
			result = familyNames->GetStringLength(j, &length);
			if (FAILED(result)) { return result; }
			//- フォントファミリー名の取得
			WCHAR* name = new WCHAR[length + 1];
			result = familyNames->GetString(j, name, length + 1);
			if (FAILED(result)) { return result; }
			//- フォントファミリー名を追加
			m_NameList.push_back(name);
			//- フォントファミリー名の破棄
			delete[] name;
		}
	}
	return result;
}

WCHAR* DirectXWriteFont::Get_FileNameOutExtension(const std::wstring& filePath)
{
	//- 末尾から検索してファイル名と拡張子の位置を取得
	size_t start = filePath.find_last_of(L"/\\") + 1;
	size_t end = filePath.find_last_of(L'.');
	//- ファイル名を取得
	std::wstring fileNameWithoutExtension = filePath.substr(start, end - start).c_str();
	// 新しいWCHAR配列を作成
	WCHAR* fileName = new WCHAR[fileNameWithoutExtension.length() + 1];
	//- 文字列をコピー
	wcscpy_s(fileName, fileNameWithoutExtension.length() + 1, fileNameWithoutExtension.c_str());
	//- ファイル名を返す
	return fileName;
}

std::wstring DirectXWriteFont::Str2Wstr(std::string str)
{
	//- SJIS → wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (wchar_t*)NULL, 0);
	//- バッファの取得
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];
	//- SJIS → wstring
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, cpUCS2, iBufferSize);
	//- stringの生成
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);
	//- バッファの破棄
	delete[] cpUCS2;
	//- 変換結果を返す
	return(oRet);
}
