/*********************************************************************
 * @file   WeaponScorpion.cpp
 * @brief  スコーピオンの武器
 *********************************************************************/
/*
==================================================

インクルード

==================================================
*/
#include "WeaponScorpion.h"

void WeaponScorpion::Init()
{
	m_weaponData.bulletData.damage = 2.0f;
	m_weaponData.bulletData.range = 1000.0f;
	m_weaponData.bulletData.speed = 40.0f;

	m_weaponData.bulletNum = 2;
	m_curBulletNum = m_weaponData.bulletNum;

	m_weaponData.reloadTime = 0.5f;
	m_curReloadTime = 0.0f;

	m_weaponData.bulletSize = 0.35f;

	m_weaponData.rate = 0.2f;

	m_weaponData.multiShotNum = 3;

	m_weaponData.SpreadAngle = { 1.0f,0.0f };

#ifdef _DEBUG
	//- 負荷軽減の為、デバッグ時は弾数を減らす
	m_weaponData.multiShotNum = 1;
	m_weaponData.SpreadAngle = { 1.0f,0.0f };
#endif // _DEBUG

	WeaponBase::Init();
}
