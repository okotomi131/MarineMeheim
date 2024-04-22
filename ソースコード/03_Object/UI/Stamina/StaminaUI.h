/*********************************************************************
 * @file   StaminaUI.h
 * @brief  �X�^�~�i��\������UI
 *********************************************************************/
#ifndef __STAMINA_UI_H__
#define __STAMINA_UI_H__
/*
==================================================

�C���N���[�h

==================================================
*/
#include "../../Object.h"

class StaminaUI : public Object
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
	void Update(float deltatime) override;

private:
	class Sprite* m_pNeedle;
	const char* m_pMeterFileName = nullptr;
	const char* m_pNeedleFileName = nullptr;
	float m_angle = 0.0f;
};

#endif // !__STAMINA_UI_H__

