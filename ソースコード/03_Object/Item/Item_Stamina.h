/*********************************************************************
 * @file   Item_Stamina.h
 * @brief  �X�^�~�i�񕜃A�C�e��
 *********************************************************************/
#ifndef __ITEM_STAMINA_H__
#define __ITEM_STAMINA_H__
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "ItemBase.h"

class Item_Stamina : public ItemBase
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
	 * @brief �X�^�~�i�񕜗�
	 * @return 
	 */
	float Get_Stamina() { return m_staminaNum; }
private:
	float m_staminaNum = 20.0f;
};

#endif // !__ITEM_STAMINA_H__

