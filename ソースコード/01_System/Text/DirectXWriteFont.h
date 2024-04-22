/*********************************************************************
 * @file   DirectXWriteFont.h
 * @brief  �e�L�X�g�`��p�̃t�H���g�ǂݍ��݂��s��
 *********************************************************************/
#ifndef __DIRECTX_WRITE_FONT_H__
#define __DIRECTX_WRITE_FONT_H__

 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "../main.h"
#include "../DirectX/DirectXRenderer.h"

#include <d2d1.h>	//Direct2D
#include <DWrite.h> //DirectWrite
#include <wrl.h>	//ComPtr


#pragma comment(lib,"d2d1.lib")	 //Direct2D�p
#pragma comment(lib,"Dwrite.lib")//DirectWrite�p

using namespace Microsoft;

//- �ۑ��ꏊ�ݒ�
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

�\����

==================================================
*/
struct FontData
{
	std::wstring			wName;		//�t�H���g��
	IDWriteFontCollection*	collection;	//�R���N�V����
	DWRITE_FONT_WEIGHT		weight;		//����
	DWRITE_FONT_STYLE		style;		//�X�^�C��
	DWRITE_FONT_STRETCH		stretch;	//��
	float					size;		//�T�C�Y
	WCHAR const*			localeName;	//���P�[����
	DWRITE_TEXT_ALIGNMENT	alignment;	//�z�u
	D2D1_COLOR_F			color;		//�F

	//- �f�t�H���g�ݒ�
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

	�t�H���g�ǂݍ��ݗp�N���X

===================================================================
*/
class FontFileEnumerator : public IDWriteFontFileEnumerator
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param factory  �t�@�N�g���[
	 * @param FilePath �t�H���g�t�@�C���̃p�XS
	 */
	FontFileEnumerator(IDWriteFactory* factory, const std::vector<std::wstring>& FilePath);

	/**
	 * @brief �f�X�g���N�^
	 */
	~FontFileEnumerator();

	/**
	 * @brief �C���^�[�t�F�[�X�̎擾
	 * @param iid �C���^�[�t�F�[�XID
	 * @param ppvObject �C���^�[�t�F�[�X
	 * @return  �T�|�[�g����Ă����S_OK
	 */
	IFACEMETHODIMP QueryInterface(REFIID iid, void** ppvObject) override;

	/**
	 * @brief �Q�ƃJ�E���g�̑���
	 * @return �Q�ƃJ�E���g��
	 */
	IFACEMETHODIMP_(ULONG) AddRef() override;

	/**
	 * @brief �Q�ƃJ�E���g�̌���
	 * @return �Q�ƃJ�E���g��
	 */
	IFACEMETHODIMP_(ULONG) Release() override;

	/**
	 * @brief ���̃t�H���g�t�@�C���Ɉړ�����
	 * @param hasCurrentFile ���̃t�H���g�t�@�C�������邩
	 * @return ���������S_OK
	 */
	IFACEMETHODIMP MoveNext(OUT BOOL* hasCurrentFile) override;

	/**
	 * @brief ���݂̃t�H���g�t�@�C�����擾����
	 * @param fontFile �t�H���g�t�@�C��
	 * @return 
	 */
	IFACEMETHODIMP GetCurrentFontFile(OUT IDWriteFontFile** fontFile) override;
private:
	ULONG			m_refCnt = {};	//�Q�ƃJ�E���g
	IDWriteFactory* m_Factory = {}; //�t�@�N�g���[
	std::vector<std::wstring> m_FilePath = {};//�t�H���g�t�@�C���̃p�X
	int	m_curFileIdx = {}; //���݂̃t�H���g�t�@�C���̃C���f�b�N�X
};

/*
===================================================================

	�t�H���g�R���N�V�����ǂݍ��ݗp�N���X

===================================================================
*/
class FontCollectionLoader : public IDWriteFontCollectionLoader
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	FontCollectionLoader();

	/**
	 * @brief �C���^�[�t�F�[�X�̎擾
	 * @param iid �C���^�[�t�F�[�XID
	 * @param ppvObject �C���^�[�t�F�[�X
	 * @return  �T�|�[�g����Ă����S_OK
	 */
	IFACEMETHODIMP QueryInterface(REFIID iid, void** ppvObject) override;

	/**
	 * @brief �Q�ƃJ�E���g�̑���
	 * @return �Q�ƃJ�E���g��
	 */
	IFACEMETHODIMP_(ULONG) AddRef() override;

	/**
	 * @brief �Q�ƃJ�E���g�̌���
	 * @return �Q�ƃJ�E���g��
	 */
	IFACEMETHODIMP_(ULONG) Release() override;

	/**
	 * @brief �R���N�V�����L�[����t�H���g�t�@�C���񋓎q���쐬����
	 * @param factory �t�@�N�g���[
	 * @param collectionKey �R���N�V�����L�[
	 * @param collectionKeySize �R���N�V�����L�[�̃T�C�Y
	 * @param fontFileEnumerator �t�H���g�t�@�C���񋓎q
	 * @return 
	 */
	IFACEMETHODIMP CreateEnumeratorFromKey(IDWriteFactory* factory, void const* collectionKey,
		UINT32 collectionKeySize, OUT IDWriteFontFileEnumerator** fontFileEnumerator) override;
private:
	ULONG m_refCnt = {}; //�Q�ƃJ�E���g
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
	 * @brief �R���X�g���N�^
	 */
	DirectXWriteFont() = delete;

	/**
	 * @brief �R���X�g���N�^
	 * @param data �t�H���g�ݒ�
	 */
	DirectXWriteFont(FontData* data) { m_FontData = *data; } 

	/**
	 * @brief ����������
	 * @param swapChain �X���b�v�`�F�C��
	 * @return ���������S_OK
	 */
	HRESULT Init(IDXGISwapChain* swapChain);

	/**
	 * @brief �ǂݍ��ݏ���
	 * @return ���������S_OK
	 */
	HRESULT Load();	

	/**
	 * @brief �e�L�X�g�̕`��
	 * @param text �`�悷��e�L�X�g
	 * @param pos  �`��ʒu
	 * @param option �`��I�v�V����
	 * @return ���������S_OK
	 */
	HRESULT Draw_String(std::string text, DirectX::XMFLOAT2 pos,D2D1_DRAW_TEXT_OPTIONS option);

	/**
	 * @brief �t�H���g�̐ݒ�
	 * @param data �t�H���g�f�[�^�\����
	 * @return ���������S_OK
	 */
	HRESULT Set_Font(FontData data);

	/**
	 * @brief �t�H���g���̎擾
	 * @param index �t�H���g�����X�g�̔ԍ�
	 * @return �ԍ��ɑΉ��������X�g�ʒu�̃t�H���g��
	 */
	std::wstring Get_FontName(int index);

	/**
	 * @brief �o�^�����t�H���g���̎擾
	 * @return �t�H���g��
	 */
	int Get_FontNum() { return (int)m_NameList.size();}

	/**
	 * @brief �t�H���g�����擾���Ȃ���
	 * @param collection �t�H���g�R���N�V����
	 * @param locale ���P�[����
	 * @return ����������S_OK
	 */
	HRESULT Get_FontFamilyName(IDWriteFontCollection* collection,const WCHAR* locale = L"en-us");

	/**
	 * @brief �S�Ẵt�H���g�����擾����
	 * @param collection �t�H���g�R���N�V����
	 * @return ����������S_OK
	 */
	HRESULT Get_AllFamilyFontName(IDWriteFontCollection* collection);

	/**
	 * @brief �t�H���g�R���N�V�����̎擾
	 * @return �t�H���g�R���N�V����
	 */
	WRL::ComPtr<IDWriteFontCollection> Get_FontCollection() { return m_pFontCollection; }
private:
	/**
	 * @brief �t�H���g�t�@�C�������擾
	 * @param filePath �t�H���g�t�@�C���̃p�X
	 * @return ����������S_OK
	 */
	WCHAR* Get_FileNameOutExtension(const std::wstring& filePath);

	/**
	 * @brief string�^����wstring�^�ɕϊ�
	 * @param str �ϊ����镶����
	 * @return �ϊ���̕�����
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
�Q�l�惊���N
https://islingtonsystem.hatenablog.jp/entry/DirectWrite_CustomFont_DirectX
*/

#endif // !__DIRECTX_WRITE_FONT_H__