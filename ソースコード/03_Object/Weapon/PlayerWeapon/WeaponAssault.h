/*********************************************************************
 * @file   WeaponAssault.h
 * @brief  �v���C���[�̕���F�A�T���g
 *********************************************************************/
#ifndef __WEAPON_ASSAULT_H__
#define __WEAPON_ASSAULT_H__
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "../WeaponBase.h"

class WeaponAssault : public WeaponBase
{
public:
	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief ����f�[�^�̍X�V
	 * @param data
	 */
	void Set_Parameter(const WeaponData& data);

	/**
	 * @brief ���݂̕���f�[�^�擾
	 * @return 
	 */
	WeaponData Get_Parameter() const { return m_weaponData; }
};

#endif // !__WEAPON_ASSAULT_H__


