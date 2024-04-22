/*********************************************************************
 * @file   Item_Heal.h
 * @brief  回復アイテム
 *********************************************************************/
#ifndef __ITEM_HEAL_H__
#define __ITEM_HEAL_H__
/*
==================================================

インクルード

==================================================
*/
#include "ItemBase.h"
class Item_Heal : public ItemBase
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
	 * @brief 回復量
	 * @return 
	 */
	float Get_Heal() { return m_healNum; }
private:
	float m_healNum = 20.0f;
};

#endif // !__ITEM_HEAL_H__


