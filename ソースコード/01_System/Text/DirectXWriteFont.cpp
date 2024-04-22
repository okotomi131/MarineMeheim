/*********************************************************************
 * @file   DirectXWriteFont.cpp
 * @brief  �e�L�X�g�`��p�̃t�H���g�ǂݍ���
 *********************************************************************/
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "DirectXWriteFont.h"

/*
===================================================================

	�t�H���g�ǂݍ���

===================================================================
*/

FontFileEnumerator::FontFileEnumerator(
	IDWriteFactory* factory, const std::vector<std::wstring>& FilePath)
	:m_refCnt(0), m_Factory(factory), m_FilePath(FilePath), m_curFileIdx(-1)
{
	//- �t�@�N�g���[�̎Q�ƃJ�E���g�𑝂₷
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
	//- �t�H���g�t�@�C����ǂݍ���
	return m_Factory->CreateFontFileReference(
		m_FilePath[m_curFileIdx].c_str(), nullptr, fontFile);
}


/*
===================================================================

	�t�H���g�R���N�V�����ǂݍ��ݗp

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
	//- �ǂݍ��ރt�H���g�t�@�C���̃p�X��n��
	std::vector<std::wstring> fontFilePaths(
		std::begin(FontList::FontPath), std::end(FontList::FontPath));

	//- �J�X�^���t�H���g�t�@�C���񋓎q�̍쐬
	*fontFileEnumerator = new (std::nothrow) FontFileEnumerator(factory, fontFilePaths);

	//- �������s���̏ꍇ�̓G���[��Ԃ�
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

	//- Direct2D�t�@�N�g�����̏�����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, m_p2DFactory.GetAddressOf());
	if (FAILED(hr)) { return hr; }

	//- �o�b�N�o�b�t�@�̎擾
	hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&m_pBackBuffer));
	if (FAILED(hr)) { return hr; }

	//- dpi�̐ݒ�
	FLOAT dpiX;
	FLOAT dpiY;
	m_p2DFactory->GetDesktopDpi(&dpiX, &dpiY);

	//- �����_�[�^�[�Q�b�g�̍쐬
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	//- �T�[�t�F�X�ɕ`�悷�郌���_�[�^�[�Q�b�g���쐬
	hr = m_p2DFactory->CreateDxgiSurfaceRenderTarget(m_pBackBuffer.Get(), &props, m_pRednerTarget.GetAddressOf());
	if (FAILED(hr)) { return hr; }

	//- �A���`�G�C���A�V���O���[�h�̐ݒ�
	m_pRednerTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	//- IDWriteFactory�̍쐬
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(m_pWriteFactory.GetAddressOf()));
	if (FAILED(hr)) { return hr; }

	//- �J�X�^���t�H���g�R���N�V�������[�_�[
	m_pFontCollectionLoader = new FontCollectionLoader();
	
	//- �J�X�^���t�H���g�R���N�V�������[�_�[�̍쐬
	hr = m_pWriteFactory->RegisterFontCollectionLoader(m_pFontCollectionLoader.Get());
	if (FAILED(hr)) { return hr; }

	//- �t�H���g�t�@�C���̓ǂݍ���
	hr = Load();
	if (FAILED(hr)) { return hr; }

	//- �t�H���g��ݒ�
	hr = Set_Font(m_FontData);
	if (FAILED(hr)) { return hr; }

	return hr;
}

HRESULT DirectXWriteFont::Load()
{
	HRESULT result = S_OK;
	

	//- �J�X�^���t�H���g�R���N�V�����̍쐬
	result = m_pWriteFactory->CreateCustomFontCollection(
		m_pFontCollectionLoader.Get(),
		m_pFileList.data(),
		m_pFileList.size(),
		&m_pFontCollection
	);
	if (FAILED(result)) { return result; }

	//- �t�H���g�����擾
	result = Get_FontFamilyName(m_pFontCollection.Get());
	
	if (FAILED(result)) { return result; }

	return S_OK;
}

HRESULT DirectXWriteFont::Draw_String(
	std::string text,DirectX::XMFLOAT2 pos,D2D1_DRAW_TEXT_OPTIONS option)
{
	HRESULT result = S_OK;

	//- ������̕ϊ�
	std::wstring wstr = Str2Wstr(text.c_str());

	//- �^�[�Q�b�g�T�C�Y�̎擾
	D2D1_SIZE_F TargetSize = m_pRednerTarget->GetSize();

	//- �e�L�X�g���C�A�E�g���쐬
	result = m_pWriteFactory->CreateTextLayout(
		wstr.c_str(), wstr.size(), m_pTextFormat.Get(), TargetSize.width,
		TargetSize.height, m_pTextLayout.GetAddressOf());
	if (FAILED(result)) { return result; }

	//- �`��ʒu�̊m��
	D2D1_POINT_2F pounts;
	pounts.x = pos.x;
	pounts.y = pos.y;

	//- �`��̊J�n
	m_pRednerTarget->BeginDraw();

	//- �`�揈��
	m_pRednerTarget->DrawTextLayout(pounts, m_pTextLayout.Get(), m_pColorBrush.Get(), option);

	//- �`��̏I��
	result = m_pRednerTarget->EndDraw();
	if (FAILED(result)) { return result; }

	return S_OK;
}


HRESULT DirectXWriteFont::Set_Font(FontData data)
{
	HRESULT result = S_OK;

	//- �ݒ���R�s�[
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
	//- �t�H���g���̃��X�g���󂾂����ꍇ
	if (m_NameList.empty()){	return nullptr;}

	//- ���X�g�̃T�C�Y�𒴂��Ă����ꍇ
	if (index >= static_cast<int>(m_NameList.size()))
	{	return m_NameList[0];	}
	return m_NameList[index];
}

HRESULT DirectXWriteFont::Get_FontFamilyName(IDWriteFontCollection* collection, const WCHAR* locale)
{
	HRESULT result = S_OK;

	//- �t�H���g�t�@�~���[���ꗗ�����Z�b�g
	std::vector<std::wstring>().swap(m_NameList);
	//- �t�H���g�̐����擾
	UINT32 familyCount = collection->GetFontFamilyCount();
	for (UINT32 i = 0; i < familyCount; i++)
	{
		//- �t�H���g�t�@�~���[�̎擾
		WRL::ComPtr <IDWriteFontFamily> fontFamily = nullptr;
		result = collection->GetFontFamily(i, fontFamily.GetAddressOf());
		if (FAILED(result)) { return result; }
		//- �t�H���g�t�@�~���[���̈ꗗ���擾
		WRL::ComPtr <IDWriteLocalizedStrings> familyNames = nullptr;
		result = fontFamily->GetFamilyNames(familyNames.GetAddressOf());
		if (FAILED(result)) { return result; }
		//- �w�肳�ꂽ���P�[���ɑΉ�����C���f�b�N�X������
		UINT32 index = 0;
		BOOL exists = FALSE;
		result = familyNames->FindLocaleName(locale, &index, &exists);
		if (FAILED(result)) { return result; }
		//- �w�肳�ꂽ���P�[����������Ȃ������ꍇ�́A�f�t�H���g�̃��P�[�����g�p
		if (!exists)
		{
			result = familyNames->FindLocaleName(L"en-us", &index, &exists);
			if (FAILED(result)) { return result; }
		}
		//- �t�H���g�t�@�~���[���̒������擾
		UINT32 length = 0;
		result = familyNames->GetStringLength(index, &length);
		if (FAILED(result)) { return result; }
		//- �t�H���g�t�@�~���[���̎擾
		WCHAR* name = new WCHAR[length + 1];
		result = familyNames->GetString(index, name, length + 1);
		if (FAILED(result)) { return result; }
		//- �t�H���g�t�@�~���[����ǉ�
		m_NameList.push_back(name);
		//- �t�H���g�t�@�~���[���̔j��
		delete[] name;
	}
	return result;
}

HRESULT DirectXWriteFont::Get_AllFamilyFontName(IDWriteFontCollection* collection)
{
	HRESULT result = S_OK;

	//- �t�H���g�t�@�~���[���ꗗ�����Z�b�g
	std::vector<std::wstring>().swap(m_NameList);
	//- �t�H���g�t�@�~���[�̐����擾
	UINT32 familyCount = collection->GetFontFamilyCount();

	for (UINT32 i = 0; i < familyCount; i++)
	{
		//- �t�H���g�t�@�~���[�̎擾
		WRL::ComPtr <IDWriteFontFamily> fontFamily = nullptr;
		result = collection->GetFontFamily(i, fontFamily.GetAddressOf());
		if (FAILED(result)) { return result; }
		//- �t�H���g�t�@�~���[���̈ꗗ���擾
		WRL::ComPtr <IDWriteLocalizedStrings> familyNames = nullptr;
		result = fontFamily->GetFamilyNames(familyNames.GetAddressOf());
		if (FAILED(result)) { return result; }
		//- �t�H���g�t�@�~���[���̐����擾
		UINT32 nameCount = familyNames->GetCount();

		//- �t�H���g�t�@�~���[���̐������J��Ԃ�
		for (UINT32 j = 0; j < nameCount; ++j)
		{
			//- �t�H���g�t�@�~���[���̒������擾
			UINT32 length = 0;
			result = familyNames->GetStringLength(j, &length);
			if (FAILED(result)) { return result; }
			//- �t�H���g�t�@�~���[���̎擾
			WCHAR* name = new WCHAR[length + 1];
			result = familyNames->GetString(j, name, length + 1);
			if (FAILED(result)) { return result; }
			//- �t�H���g�t�@�~���[����ǉ�
			m_NameList.push_back(name);
			//- �t�H���g�t�@�~���[���̔j��
			delete[] name;
		}
	}
	return result;
}

WCHAR* DirectXWriteFont::Get_FileNameOutExtension(const std::wstring& filePath)
{
	//- �������猟�����ăt�@�C�����Ɗg���q�̈ʒu���擾
	size_t start = filePath.find_last_of(L"/\\") + 1;
	size_t end = filePath.find_last_of(L'.');
	//- �t�@�C�������擾
	std::wstring fileNameWithoutExtension = filePath.substr(start, end - start).c_str();
	// �V����WCHAR�z����쐬
	WCHAR* fileName = new WCHAR[fileNameWithoutExtension.length() + 1];
	//- ��������R�s�[
	wcscpy_s(fileName, fileNameWithoutExtension.length() + 1, fileNameWithoutExtension.c_str());
	//- �t�@�C������Ԃ�
	return fileName;
}

std::wstring DirectXWriteFont::Str2Wstr(std::string str)
{
	//- SJIS �� wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (wchar_t*)NULL, 0);
	//- �o�b�t�@�̎擾
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];
	//- SJIS �� wstring
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, cpUCS2, iBufferSize);
	//- string�̐���
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);
	//- �o�b�t�@�̔j��
	delete[] cpUCS2;
	//- �ϊ����ʂ�Ԃ�
	return(oRet);
}
