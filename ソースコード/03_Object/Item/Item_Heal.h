/*********************************************************************
 * @file   Item_Heal.h
 * @brief  �񕜃A�C�e��
 *********************************************************************/
#ifndef __ITEM_HEAL_H__
#define __ITEM_HEAL_H__
/*
==================================================

�C���N���[�h

==================================================
*/
#include "ItemBase.h"
class Item_Heal : public ItemBase
{
public:
	/**
	 * @brief ����������
	 */
	void Init()override;

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime)override;

	/**
	 * @brief �񕜗�
	 * @return 
	 */
	float Get_Heal() { return m_healNum; }
private:
	float m_healNum = 20.0f;
};

#endif // !__ITEM_HEAL_H__


