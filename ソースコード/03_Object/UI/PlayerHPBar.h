/*********************************************************************
 * @file   PlayerHPBar.h
 * @brief  �v���C���[�̌��݂�HP��\������UI
 *********************************************************************/
#ifndef __PLAYER_HP_BAR_H__
#define __PLAYER_HP_BAR_H__
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "../Object.h"

class PlayerHPBar :public Object
{
public:
	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/**
	 * @brief �`�揈��
	 */
	void Draw() override;

	/**
	 * @brief HP�o�[�̑���
	 */
	void MoveHPBar();

	/**
	 * @brief �ő�HP�̐ݒ�
	 * @param maxhp
	 */
	void Set_MaxHP(float maxhp) { m_maxHP = maxhp; }
private:
	float m_maxHP;
	DirectX::XMFLOAT2 m_initSize;
};

#endif // !__PLAYER_HP_BAR_H__


