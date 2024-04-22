/*********************************************************************
 * @file   WeaponGlobeFish.cpp
 * @brief  �t�O�̕���
 *********************************************************************/
 /*
 ==================================================

 �C���N���[�h

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
	//- ���׌y���ׁ̈A�f�o�b�O���͒e�������炷
	m_weaponData.multiShotNum = 1;
	m_weaponData.SpreadAngle = { 1.0f,0.0f };
#endif // _DEBUG

	WeaponBase::Init();
}
