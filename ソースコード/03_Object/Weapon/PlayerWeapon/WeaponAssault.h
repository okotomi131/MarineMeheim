/*********************************************************************
 * @file   WeaponAssault.h
 * @brief  プレイヤーの武器：アサルト
 *********************************************************************/
#ifndef __WEAPON_ASSAULT_H__
#define __WEAPON_ASSAULT_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../WeaponBase.h"

class WeaponAssault : public WeaponBase
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief 武器データの更新
	 * @param data
	 */
	void Set_Parameter(const WeaponData& data);

	/**
	 * @brief 現在の武器データ取得
	 * @return 
	 */
	WeaponData Get_Parameter() const { return m_weaponData; }
};

#endif // !__WEAPON_ASSAULT_H__


