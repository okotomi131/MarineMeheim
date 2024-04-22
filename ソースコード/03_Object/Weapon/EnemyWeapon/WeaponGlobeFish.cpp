/*********************************************************************
 * @file   WeaponGlobeFish.cpp
 * @brief  フグの武器
 *********************************************************************/
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "WeaponGlobeFish.h"

void WeaponGlobeFish::Init()
{
	m_weaponData.bulletData.damage = 5.0f;
	m_weaponData.bulletData.range = 1000.0f;
	m_weaponData.bulletData.speed = 20.0f;

	m_weaponData.bulletNum = 1;
	m_curBulletNum = m_weaponData.bulletNum;

	m_weaponData.reloadTime = 1.0f;
	m_curReloadTime = 0.0f;

	m_weaponData.bulletSize = 0.65f;

	m_weaponData.rate = 0.5f;

	m_weaponData.multiShotNum = 5;

	m_weaponData.SpreadAngle = { 1.0f,0.0f };

#ifdef _DEBUG
	//- 負荷軽減の為、デバッグ時は弾数を減らす
	m_weaponData.multiShotNum = 1;
	m_weaponData.SpreadAngle = { 1.0f,0.0f };
#endif // _DEBUG

	WeaponBase::Init();
}
