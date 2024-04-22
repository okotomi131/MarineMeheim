/*********************************************************************
 * @file   HPBase.h
 * @brief  HP����
 *********************************************************************/

#ifndef _HP_BASE_H__
#define _HP_BASE_H__

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Component.h"

class HPBase : public Component
{
public:
	using Component::Component;

	/*
	==================================================

	�\����

	==================================================
	*/
	struct HpData
	{
		float curHp;
		float maxHp;
	};

	/**
	 * @brief �̗͂̃��Z�b�g���s��
	 */
	void ResetHP() { m_curHP = m_MaxHP; };

	/**
	 * @brief �̗͂̃_���[�W�������s��
	 */
	void Damage(float damage) { if (m_curHP > 0) { m_curHP -= damage; } };

	/**
	 * @brief ��
	 * @param heal �񕜗�
	 */
	void Heal(float heal);

	/*
	==================================================
	
	�Q�b�^�[�E�Z�b�^�[
	
	==================================================
	*/

	/**
	 * @brief �̗̓f�[�^�̎擾
	 * @return HpData �̗̓f�[�^
	 */
	HpData Get_HpData() { return { m_curHP,m_MaxHP }; };

	/**
	 * @brief �̗͂̐ݒ�
	 */
	void Set_MaxHP(float maxHp) { m_MaxHP = maxHp; m_curHP = m_MaxHP;};
protected:
	float m_curHP = 0.0f;
	float m_MaxHP = 10.0f;
};


#endif // !_HP_BASE_H__
