/*********************************************************************
 * @file   Barrier.h
 * @brief  �X�e�[�W�̈ړ��������s��
 *********************************************************************/

#ifndef __BARRIER_H__
#define __BARRIER_H__

 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "../Object.h"
#include "../../01_System/Texture/CreateTexture.h"


class Barrier : public Object
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
	float m_DeltaTime = 0;
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_pTexture = nullptr;
	DirectX::XMFLOAT3 m_PlayerPos = { 0.0f, 0.0f, 0.0f };
};

#endif // !__BARRIER_H__
