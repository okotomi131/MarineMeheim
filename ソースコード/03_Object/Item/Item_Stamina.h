/*********************************************************************
 * @file   Item_Stamina.h
 * @brief  スタミナ回復アイテム
 *********************************************************************/
#ifndef __ITEM_STAMINA_H__
#define __ITEM_STAMINA_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "ItemBase.h"

class Item_Stamina : public ItemBase
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init()override;

	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	void Update(float deltatime)override;

	/**
	 * @brief スタミナ回復量
	 * @return 
	 */
	float Get_Stamina() { return m_staminaNum; }
private:
	float m_staminaNum = 20.0f;
};

#endif // !__ITEM_STAMINA_H__

