/*********************************************************************
 * @file   WeaponClownFish.cpp
 * @brief  �N�}�m�~�̕���
 *********************************************************************/

/*
==================================================

�C���N���[�h

==================================================
*/
#include "WeaponClownFish.h"

void WeaponClownFish::Init()
{
	m_weaponData.bulletData.damage = 1.0f;
	m_weaponData.bulletData.range = 1000.0f;
	m_weaponData.bulletData.speed = 60.0f;

	m_weaponData.bulletNum = 2;
	m_curBulletNum = m_weaponData.bulletNum;

	m_weaponData.reloadTime = 0.5f;
	m_curReloadTime = 0.0f;

	m_weaponData.bulletSize = 0.25f;

	m_weaponData.rate = 0.2f;

	m_weaponData.multiShotNum = 1;

	m_weaponData.SpreadAngle = { 1.0f,0.0f };

#ifdef _DEBUG
	//- ���׌y���ׁ̈A�f�o�b�O���͒e�������炷
	m_weaponData.multiShotNum = 1;
	m_weaponData.SpreadAngle = { 1.0f,0.0f };
#endif // _DEBUG

	WeaponBase::Init();
}
