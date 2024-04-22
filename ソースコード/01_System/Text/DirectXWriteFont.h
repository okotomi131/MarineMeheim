/*********************************************************************
 * @file   DirectXWriteFont.h
 * @brief  テキスト描画用のフォント読み込みを行う
 *********************************************************************/
#ifndef __DIRECTX_WRITE_FONT_H__
#define __DIRECTX_WRITE_FONT_H__

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../main.h"
#include "../DirectX/DirectXRenderer.h"

#include <d2d1.h>	//Direct2D
#include <DWrite.h> //DirectWrite
#include <wrl.h>	//ComPtr


#pragma comment(lib,"d2d1.lib")	 //Direct2D用
#pragma comment(lib,"Dwrite.lib")//DirectWrite用

using namespace Microsoft;

//- 保存場所設定
namespace FontList
{
	const std::wstring FontPath[] =
	{
		L"Assets/Fonts/DotGothic16-Regular.ttf",
		L"Assets/Fonts/07LogoTypeGothic-Condense.ttf",
		L"Assets/Fonts/MPLUS2.ttf",
	};
}

/*
==================================================

構造体

==================================================
*/
struct FontData
{
	std::wstring			wName;		//フォント名
	IDWriteFontCollection*	collection;	//コレクション
	DWRITE_FONT_WEIGHT		weight;		//太さ
	DWRITE_FONT_STYLE		style;		//スタイル
	DWRITE_FONT_STRETCH		stretch;	//幅
	float					size;		//サイズ
	WCHAR const*			localeName;	//ロケール名
	DWRITE_TEXT_ALIGNMENT	alignment;	//配置
	D2D1_COLOR_F			color;		//色

	//- デフォルト設定
	FontData()
	{
		wName		= L"";
		collection	= nullptr;
		weight		= DWRITE_FONT_WEIGHT_NORMAL;
		style		= DWRITE_FONT_STYLE_NORMAL;
		stretch		= DWRITE_FONT_STRETCH_NORMAL;
		size		= 20;
		localeName	= L"ja-jp";
		alignment	= DWRITE_TEXT_ALIGNMENT_LEADING;
		color		= D2D1::ColorF(D2D1::ColorF::White);
	}
};

/*
===================================================================

	フォント読み込み用クラス

===================================================================
*/
class FontFileEnumerator : public IDWriteFontFileEnumerator
{
public:
	/**
	 * @brief コンストラクタ
	 * @param factory  ファクトリー
	 * @param FilePath フォントファイルのパスS
	 */
	FontFileEnumerator(IDWriteFactory* factory, const std::vector<std::wstring>& FilePath);

	/**
	 * @brief デストラクタ
	 */
	~FontFileEnumerator();

	/**
	 * @brief インターフェースの取得
	 * @param iid インターフェースID
	 * @param ppvObject インターフェース
	 * @return  サポートされていればS_OK
	 */
	IFACEMETHODIMP QueryInterface(REFIID iid, void** ppvObject) override;

	/**
	 * @brief 参照カウントの増加
	 * @return 参照カウント数
	 */
	IFACEMETHODIMP_(ULONG) AddRef() override;

	/**
	 * @brief 参照カウントの減少
	 * @return 参照カウント数
	 */
	IFACEMETHODIMP_(ULONG) Release() override;

	/**
	 * @brief 次のフォントファイルに移動する
	 * @param hasCurrentFile 次のフォントファイルがあるか
	 * @return 成功すればS_OK
	 */
	IFACEMETHODIMP MoveNext(OUT BOOL* hasCurrentFile) override;

	/**
	 * @brief 現在のフォントファイルを取得する
	 * @param fontFile フォントファイル
	 * @return 
	 */
	IFACEMETHODIMP GetCurrentFontFile(OUT IDWriteFontFile** fontFile) override;
private:
	ULONG			m_refCnt = {};	//参照カウント
	IDWriteFactory* m_Factory = {}; //ファクトリー
	std::vector<std::wstring> m_FilePath = {};//フォントファイルのパス
	int	m_curFileIdx = {}; //現在のフォントファイルのインデックス
};

/*
===================================================================

	フォントコレクション読み込み用クラス

===================================================================
*/
class FontCollectionLoader : public IDWriteFontCollectionLoader
{
public:
	/**
	 * @brief コンストラクタ
	 */
	FontCollectionLoader();

	/**
	 * @brief インターフェースの取得
	 * @param iid インターフェースID
	 * @param ppvObject インターフェース
	 * @return  サポートされていればS_OK
	 */
	IFACEMETHODIMP QueryInterface(REFIID iid, void** ppvObject) override;

	/**
	 * @brief 参照カウントの増加
	 * @return 参照カウント数
	 */
	IFACEMETHODIMP_(ULONG) AddRef() override;

	/**
	 * @brief 参照カウントの減少
	 * @return 参照カウント数
	 */
	IFACEMETHODIMP_(ULONG) Release() override;

	/**
	 * @brief コレクションキーからフォントファイル列挙子を作成する
	 * @param factory ファクトリー
	 * @param collectionKey コレクションキー
	 * @param collectionKeySize コレクションキーのサイズ
	 * @param fontFileEnumerator フォントファイル列挙子
	 * @return 
	 */
	IFACEMETHODIMP CreateEnumeratorFromKey(IDWriteFactory* factory, void const* collectionKey,
		UINT32 collectionKeySize, OUT IDWriteFontFileEnumerator** fontFileEnumerator) override;
private:
	ULONG m_refCnt = {}; //参照カウント
};


/*
===================================================================

	DirectXWrite

===================================================================
*/
class DirectXWriteFont
{
public:

	/**
	 * @brief コンストラクタ
	 */
	DirectXWriteFont() = delete;

	/**
	 * @brief コンストラクタ
	 * @param data フォント設定
	 */
	DirectXWriteFont(FontData* data) { m_FontData = *data; } 

	/**
	 * @brief 初期化処理
	 * @param swapChain スワップチェイン
	 * @return 成功すればS_OK
	 */
	HRESULT Init(IDXGISwapChain* swapChain);

	/**
	 * @brief 読み込み処理
	 * @return 成功すればS_OK
	 */
	HRESULT Load();	

	/**
	 * @brief テキストの描画
	 * @param text 描画するテキスト
	 * @param pos  描画位置
	 * @param option 描画オプション
	 * @return 成功すればS_OK
	 */
	HRESULT Draw_String(std::string text, DirectX::XMFLOAT2 pos,D2D1_DRAW_TEXT_OPTIONS option);

	/**
	 * @brief フォントの設定
	 * @param data フォントデータ構造体
	 * @return 成功すればS_OK
	 */
	HRESULT Set_Font(FontData data);

	/**
	 * @brief フォント名の取得
	 * @param index フォント名リストの番号
	 * @return 番号に対応したリスト位置のフォント名
	 */
	std::wstring Get_FontName(int index);

	/**
	 * @brief 登録したフォント数の取得
	 * @return フォント数
	 */
	int Get_FontNum() { return (int)m_NameList.size();}

	/**
	 * @brief フォント名を取得しなおす
	 * @param collection フォントコレクション
	 * @param locale ロケール名
	 * @return 成功したらS_OK
	 */
	HRESULT Get_FontFamilyName(IDWriteFontCollection* collection,const WCHAR* locale = L"en-us");

	/**
	 * @brief 全てのフォント名を取得する
	 * @param collection フォントコレクション
	 * @return 成功したらS_OK
	 */
	HRESULT Get_AllFamilyFontName(IDWriteFontCollection* collection);

	/**
	 * @brief フォントコレクションの取得
	 * @return フォントコレクション
	 */
	WRL::ComPtr<IDWriteFontCollection> Get_FontCollection() { return m_pFontCollection; }
private:
	/**
	 * @brief フォントファイル名を取得
	 * @param filePath フォントファイルのパス
	 * @return 成功したらS_OK
	 */
	WCHAR* Get_FileNameOutExtension(const std::wstring& filePath);

	/**
	 * @brief string型からwstring型に変換
	 * @param str 変換する文字列
	 * @return 変換後の文字列
	 */
	std::wstring Str2Wstr(std::string str);

	WRL::ComPtr<IDWriteFontCollection>  m_pFontCollection		= nullptr;
	WRL::ComPtr<FontCollectionLoader>   m_pFontCollectionLoader = nullptr;


	WRL::ComPtr<ID2D1Factory>			m_p2DFactory		= nullptr;
	WRL::ComPtr<ID2D1RenderTarget>		m_pRednerTarget		= nullptr;
	WRL::ComPtr<ID2D1SolidColorBrush>	m_pColorBrush		= nullptr;
	WRL::ComPtr<IDWriteFactory>			m_pWriteFactory		= nullptr;
	WRL::ComPtr<IDWriteTextFormat>		m_pTextFormat		= nullptr;
	WRL::ComPtr<IDWriteTextLayout>		m_pTextLayout		= nullptr;
	WRL::ComPtr<IDXGISurface>			m_pBackBuffer		= nullptr;

	std::vector<WRL::ComPtr<IDWriteFontFile>> m_pFileList = {};
	std::vector<std::wstring> m_NameList = {};
	FontData  m_FontData = FontData();

};

/*
参考先リンク
https://islingtonsystem.hatenablog.jp/entry/DirectWrite_CustomFont_DirectX
*/

#endif // !__DIRECTX_WRITE_FONT_H__