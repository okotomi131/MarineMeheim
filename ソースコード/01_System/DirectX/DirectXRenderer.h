/*********************************************************************
 * @file   DirectXRenderer.h
 * @brief  DirectX�̐���N���X
 * �萔�o�b�t�@�錾�A�V�F�[�_�[�̓ǂݍ��݂��s��
 *********************************************************************/

#ifndef __DIRECTX_RENDERER_H__
#define __DIRECTX_RENDERER_H__

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../main.h"
#include <typeindex>

/*
==================================================

�}�N���E�萔��`

==================================================
*/
static const int WAVE_MAX = 40;


/*
==================================================

�\����
 
==================================================
*/

//- 3D���_�p
struct VERTEX3D
{
	DirectX::XMFLOAT3 pos;		//���_���W
	DirectX::XMFLOAT3 normal;	//�@���x�N�g��
	DirectX::XMFLOAT4 diffuse;	//�f�B�t���[�Y�J���[
	DirectX::XMFLOAT2 uv;		//�e�N�X�`�����W
};

/*
==================================================

�\����(�萔�o�b�t�@�p)

==================================================
*/

//- �}�e���A���p
struct MATERIAL
{
	DirectX::XMFLOAT4	ambient;		//�A���r�G���g
	DirectX::XMFLOAT4	diffuse;		//�f�B�t���[�Y�J���[
	DirectX::XMFLOAT4	specular;		//�X�y�L�����J���[
	DirectX::XMFLOAT4	emission;		//�G�~�b�V�����J���[
	float				shininess;		//�X�l�[�N�l(����̋��x
	float 				dummy[3];		//�_�~�[
};

//- ���C�g�p
struct LIGHT
{
	BOOL enable;				//���C�g�L���t���O
	BOOL dummy[3];				
	DirectX::XMFLOAT4 direction;//����
	DirectX::XMFLOAT4 diffuse;  //�F
	DirectX::XMFLOAT4 ambient;  //����
};

//- ���ԗp
struct TIME
{
	float time;		//����
	float dummy[3];	//�_�~�[
};

//- �I�u�W�F�N�g�p
struct CONSTANT_BUFFE_OBJECT
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 scale;
	float dummy[2];
};

//- �g�p
struct WAVE
{
	DirectX::XMFLOAT2 direction;	// �g�̐i�s����
	float amplitude;				// �U��
	float lenght;					// �g��
};

struct WAVE_BUFFER
{
	WAVE wave[WAVE_MAX];
};

/*
==================================================

�񋓌^

==================================================
*/

//�}�g���b�N�X�p
enum class E_MATRIX_TYPE
{
	World,
	View,
	Proj,

	Max
};

//�萔�o�b�t�@�p
enum class E_CONSTANT_BUFFER_TYPE
{
	Material,
	Light,
	Time,
	Object,

	Max
};

class DirectXRenderer
{
public:
	/**
	 * @brief ����������
	 * DirectX�̏��������s��
	 */
	static void Init();

	/**
	 * @brief �I������
	 * DirectX�̏I���������s��
	 */
	static void Uninit();

	/**
	 * @brief �`��J�n����
	 */
	static void BeginDraw();

	/**
	 * @brief �`��I������
	 */
	static void EndDraw();


	/*
	==================================================

	�Z�b�^�[

	==================================================
	*/
	

	/**
	 * @brief �[�x�o�b�t�@�L���ݒ�
	 * @param enable �L���t���O
	 */
	inline static void Set_DepthEnable(bool enable) 
	{
		if (enable) 
		{ m_pDeviceContext->OMSetDepthStencilState(m_pDepthStateEnable, 0); }
		else
		{ m_pDeviceContext->OMSetDepthStencilState(m_pDepthStateDisable, 0); }
	};


	/**
	 * @brief �u�����h�X�e�[�g�̗L���ݒ�
	 * @param enable �L���t���O
	 */
	static void Set_ATCEnable(bool enable);
	
	/**
	 * @brief �J�����O���[�h�ݒ�
	 * @param mode �J�����O���[�h
	 */
	static void Set_CullingMode(D3D11_CULL_MODE mode);


	/*
	==================================================

	�Q�b�^�[

	==================================================
	*/

	/**
	 * @brief �f�o�C�X�擾
	 * @return �f�o�C�X�̃|�C���^
	 */
	inline static ID3D11Device* Get_Device()
	{return m_pDevice;};

	/**
	 * @brief �f�o�C�X�R���e�L�X�g�擾
	 * @return �f�o�C�X�R���e�L�X�g�̃|�C���^
	 */
	inline static ID3D11DeviceContext* Get_DeviceContext()
	{	return m_pDeviceContext;};

	/**
	 * @brief �X���b�v�`�F�C���擾
	 * @return �X���b�v�`�F�C���̃|�C���^
	 */
	inline static IDXGISwapChain* Get_SwapChain()
	{	return m_pSwapChain;};


	/*
	==================================================

	�萔�o�b�t�@��������

	==================================================
	*/


	/**
	 * @brief ���[���h�s��ݒ�
	 * @param world ���[���h�s��
	 */
	static void Write_World(DirectX::XMFLOAT4X4* world);

	/**
	 * @brief �r���[�s��ݒ�
	 * @param view �r���[�s��
	 */
	static void Write_View(DirectX::XMFLOAT4X4* view);

	/**
	 * @brief �v���W�F�N�V�����s��ݒ�
	 * @param proj �v���W�F�N�V�����s��
	 */
	static void write_Projection(DirectX::XMFLOAT4X4* proj);

	/**
	 * @brief 2D�p��WVP�ݒ���s��
	 */
	static void Write_WorldViewProjection2D();

	/**
	 * @brief �萔�o�b�t�@�̍쐬���s��
	 * @param BufferName �o�b�t�@��
	 * @param OnlySetVS ���_�V�F�[�_�[�݂̂ɓo�^���s����
	 */
	template<typename T>
	static void CreateConstantBuffer(std::string BufferName, bool OnlySetVS = false)
	{
		//- �萔�o�b�t�@�̍쐬
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = sizeof(T);
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = sizeof(float);

		ID3D11Buffer* buffer = nullptr;
		HRESULT hr = m_pDevice->CreateBuffer(&bufferDesc, nullptr, &buffer);
		if (FAILED(hr)) { Message::DebugLog("�萔�o�b�t�@�̍쐬�Ɏ��s"); return; }
		//- �o�b�t�@�̍X�V
		m_pDeviceContext->VSSetConstantBuffers(static_cast<UINT>(m_bufferTypeMap.size()), 1, &buffer);
		if (!OnlySetVS) { m_pDeviceContext->PSSetConstantBuffers(static_cast<UINT>(m_bufferTypeMap.size()), 1, &buffer); }

		//- �^�ƃo�b�t�@�Ɩ��O��o�^
		m_bufferTypeMap.insert(std::make_pair(BufferName,			//�o�b�t�@���̓o�^
			std::make_pair(std::type_index(typeid(T)), buffer)));	//�^�ƃo�b�t�@�̓o�^
	}

	/**
	 * @brief �萔�o�b�t�@�̏������݂��s��
	 * @param BufferName �o�b�t�@��
	 * @param data �������ރf�[�^
	 */
	template<typename T>
	static void Write_Buffer(std::string BufferName,T data)
	{
		//- �o�b�t�@�̎擾
		auto moldbuffer = m_bufferTypeMap.find(BufferName);
		ID3D11Buffer* buffer = moldbuffer->second.second;
		if(buffer == nullptr) { Message::DebugLog("�o�b�t�@��������܂���"); return; }
		//- �^����v���Ă��邩�m�F
		if (moldbuffer->second.first != std::type_index(typeid(data)))
		{ Message::DebugLog("�^����v���܂���"); return; }

		m_pDeviceContext->UpdateSubresource(buffer, 0, nullptr, &data, 0, 0);
	}

	/*
	==================================================

	�V�F�[�_�[

	==================================================
	*/

	/**
	 * @brief ���_�V�F�[�_�[�̍쐬���s��
	 * 
	 * @param vs ���_�V�F�[�_�[
	 * @param VertexLayout ���_���C�A�E�g
	 * @param FileName �V�F�[�_�t�@�C����
	 */
	static void CreateVertexShader(ID3D11VertexShader** vs, ID3D11InputLayout** VertexLayout, const char* FileName);

	/**
	 * @brief �s�N�Z���V�F�[�_�[�̍쐬���s��
	 * 
	 * @param ps �s�N�Z���V�F�[�_�[
	 * @param FileName �V�F�[�_�t�@�C����
	 */
	static void CreatePixelShader(ID3D11PixelShader** ps, const char* FileName);


private:

	static D3D_FEATURE_LEVEL        m_pFeatureLevel;
	static ID3D11Device*            m_pDevice;
	static ID3D11DeviceContext*     m_pDeviceContext;
	static IDXGISwapChain*          m_pSwapChain;
	static ID3D11RenderTargetView*  m_pRenderTargetView;
	static ID3D11DepthStencilView*  m_pDepthStencilView;
	static ID3D11DepthStencilState* m_pDepthStateEnable;
	static ID3D11DepthStencilState* m_pDepthStateDisable;
	static ID3D11BlendState*		m_pBlendState;
	static ID3D11BlendState*		m_pBlendStateATC;
	static std::unordered_map<std::string, std::pair<std::type_index, ID3D11Buffer*>> m_bufferTypeMap;
};

#endif // !__DIRECTX_RENDERER_H__