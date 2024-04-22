/*********************************************************************
 * @file   StaminaUI.h
 * @brief  スタミナを表示するUI
 *********************************************************************/
#ifndef __STAMINA_UI_H__
#define __STAMINA_UI_H__
/*
==================================================

インクルード

==================================================
*/
#include "../../Object.h"

class StaminaUI : public Object
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief 更新処理
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

