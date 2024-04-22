/*********************************************************************
 * @file   WeaponGlobeFish.h
 * @brief  フグの武器
 *********************************************************************/
#ifndef __WEAPON_GLOBE_FISH_H__
#define __WEAPON_GLOBE_FISH_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../WeaponBase.h"
class WeaponGlobeFish : public WeaponBase
{
	/**
	 * @brief 初期化処理
	 */
	void Init() override;
};

#endif // !__WEAPON_GLOBE_FISH_H__


