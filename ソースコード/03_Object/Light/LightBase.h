/*********************************************************************
 * @file   LightBase.h
 * @brief  ���C�g�̊��N���X
 *********************************************************************/
#ifndef __LIGHT_BASE_H__
#define __LIGHT_BASE_H__

 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "../Object.h"

class LightBase : public Object
{
public:
	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	//void Update(float deltatime) override;

	/**
	 * @brief ���C�g�̕�����ݒ�
	 * @param direction
	 */
	void Set_LightDirection(DirectX::XMFLOAT4 direction) { m_direction = direction; }
private:

	float m_curTime = 0.0f;
	LIGHT m_light = {};

	DirectX::XMFLOAT4 m_direction = {};
	DirectX::XMFLOAT4 m_ambient = { 0.5f,0.5f,0.5f,1.0f};
	DirectX::XMFLOAT4 m_diffuse = { 0.9f,0.9f,1.0f,1.0f };
};

#endif // !__LIGHT_BASE_H__

