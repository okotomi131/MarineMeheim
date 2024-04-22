/*********************************************************************
 * @file   Seaweed.h
 * @brief  �C���̏���
 *********************************************************************/
#ifndef __SEAWEED_H__
#define __SEAWEED_H__
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "../Object.h"
class Seaweed : public Object
{
public:
	/**
	 * @brief ����������
	 */
	void Init() override;
	/**
	 * @brief �I������
	 */
	void Uninit() override;

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/**
	 * @brief �`�揈��
	 */
	void Draw() override;
private:
	float m_moveTime = 0.0f;
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_pTexture = nullptr;
	ID3D11ShaderResourceView* m_pDizaTex = nullptr;
	DirectX::XMFLOAT3 m_cameraPos = { 0.0f, 0.0f, 0.0f };
};

#endif // !__SEAWEED_H__


