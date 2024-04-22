/*********************************************************************
 * @file   WeaponAssault.cpp
 * @brief  プレイヤーの武器：アサルト
 *********************************************************************/
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "WeaponAssault.h"
#include "../../../01_System/Save/DataSave.h"

void WeaponAssault::Init()
{
	m_weaponData.bulletData.damage = 1.75f;
	m_weaponData.bulletData.range  = 1500.0f;
	m_weaponData.bulletData.speed  = 100.0f;

	m_weaponData.bulletNum = 30;
	m_curBulletNum = m_weaponData.bulletNum;

	m_weaponData.reloadTime	= 0.5f;
	m_curReloadTime = 0.0f;

	m_weaponData.bulletSize	= 0.25f;
	m_weaponData.rate = 0.05f;
	m_weaponData.multiShotNum = 1;
	m_weaponData.SpreadAngle = { 1.0f,0.0f };

	WeaponBase::Init();
}

void WeaponAssault::Set_Parameter(const WeaponData& data)
{
	m_weaponData = data;
	m_curBulletNum = m_weaponData.bulletNum;
	m_curReloadTime = 0.0f;
}
