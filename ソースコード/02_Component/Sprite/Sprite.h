/*********************************************************************
 * @file   Sprite.h
 * @brief  �X�v���C�g�`��
 *********************************************************************/
#ifndef __SPRITE_H__
#define __SPRITE_H__
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */

#include "../Component.h"

/*
==================================================

�}�N���E�萔��`

==================================================
*/ 
const static int MAX_FILENAME(128);


class Sprite : public Component
{
public:
	using Component::Component;
	
	/**
	 * @brief ����������
	 * @param pos �������W
	 * @param size �����T�C�Y
	 * @param fileName �t�@�C����
	 */
	void Init(DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 size, const char* fileName);

	/**
	 * @brief �I������
	 */
	void Uninit() override;

	/**
	 * @brief �X�V����
	 * @param deltaTime
	 */
	void Update(float deltaTime) override;

	/**
	 * @brief �`�揈��
	 */
	void Draw()   override;


	/*
	==================================================

	�Z�b�^�[

	==================================================
	*/

	/**
	 * @brief ���W�ݒ�
	 * @param pos
	 */
	inline void Set_Pos(const DirectX::XMFLOAT2& pos)	{ m_pos  = pos; }

	/**
	 * @brief �T�C�Y�ݒ�
	 * @param size
	 */
	inline void Set_Size(const DirectX::XMFLOAT2& size) { m_size = size; }

	/**
	 * @brief ��]�ݒ�
	 * @param rot
	 */
	inline void Set_Rot(const float& rot) { m_rot  = rot; };

	/**
	 * @brief UV�������ݒ�
	 * @param x ���̕�����
	 * @param y �c�̕�����
	 */
	inline void Set_UvDivision(const int& x, int& y) { m_uvX  = x;  m_uvY = y; };

	/**
	 * @brief �A�j���[�V�������Ԑݒ�
	 * @param
	 */
	inline void Set_Time(const float& time)	{ m_animeTime = time; };

	/**
	 * @brief�@�J���[�̐ݒ�
	 * @param
	 */
	inline void Set_Color(const DirectX::XMFLOAT4& color) { m_material.diffuse = color; };

	/**
	 * @brief �}�e���A���̐ݒ�
	 * @param 
	 */
	inline void Set_Material(const MATERIAL& material)	{ m_material = material; };

	/**
	 * @brief �}�e���A���̐ݒ�
	 * @param
	 */
	inline void Set_bufferObject(const CONSTANT_BUFFE_OBJECT& object)	{m_bufferObject = object; };
	

	/*
	==================================================

	�Q�b�^�[

	==================================================
	*/

	/**
	 * @brief ���W�擾
	 * @return 
	 */
	DirectX::XMFLOAT2 Get_Pos()  const { return m_pos; }

	/**
	 * @brief �T�C�Y�擾
	 * @return 
	 */
	DirectX::XMFLOAT2 Get_Size() const { return m_size; }

	/**
	 * @brief �t�@�C�����擾
	 * @return 
	 */
	const char* Get_FileName() const { return m_fileName; }
private:

	/**
	* @brief ���_��]
	* @param vtxNum ���_��
	* @param pos ���_���W
	* @param vtx ���_�f�[�^
	*/
	void VertexRot(const int& vtxNum, DirectX::XMFLOAT2 pos[4],VERTEX3D vtx[4]);

	ID3D11Buffer*				m_pVertexBuffer = {};
	ID3D11ShaderResourceView*	m_pTexture = {};
	MATERIAL m_material = {};
	CONSTANT_BUFFE_OBJECT m_bufferObject = {};

	DirectX::XMFLOAT2 m_pos;
	DirectX::XMFLOAT2 m_size;
	float m_rot = 0.0f;

	int		m_animeCnt = 0;
	float	m_animeTime = -1.0f;
	int		m_uvX = 1;
	int		m_uvY = 1;
	float   m_curTime = 1.0f;
	const char* m_fileName = nullptr;

};


#endif // !__SPRITE_H__

