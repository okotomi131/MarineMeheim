/*********************************************************************
 * @file   WeaponScorpion.h
 * @brief  スコーピオンの武器
 *********************************************************************/
#ifndef __WEAPON_SCORPION_H__
#define __WEAPON_SCORPION_H__
/*
==================================================

インクルード

==================================================
*/
#include "../WeaponBase.h"

class WeaponScorpion : public WeaponBase
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init() override;
};

#endif // !__WEAPON_SCORPION_H__


