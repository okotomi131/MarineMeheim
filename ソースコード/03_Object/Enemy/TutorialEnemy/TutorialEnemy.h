/*********************************************************************
 * @file   TutorialEnemy.h
 * @brief  �`���[�g���A���p�̓G
 *********************************************************************/
#ifndef __TUTORIAL_ENEMY_H__
#define __TUTORIAL_ENEMY_H__
/*
==================================================

�C���N���[�h

==================================================
*/
#include "../EnemyBase.h"

class TutorialEnemy : public EnemyBase
{
public:
	static void Load();
	void Init() override;
	void Update(float deltatime) override;
private:
	/*
	==================================================

	�X�e�[�g�֐�

	==================================================
	*/
	/**
	 * @brief �������̏���
	 * @param deltatime �f���^�^�C��
	 * @param step �X�e�[�g�̏����i�K
	 */
	void State_Spawn(float deltatime, E_STEP step) override;

	/*
	 * @brief �ҋ@���̏���
	 * @param deltatime �f���^�^�C��
	 * @param step �X�e�[�g�̏����i�K
	 */
	void State_Idle(float deltatime, E_STEP step) override;

	/**
	 * @brief ���̓G�͎g�p���Ȃ�
	 * @param deltatime �f���^�^�C��
	 * @param step �X�e�[�g�̏����i�K
	 */
	void State_Walk(float deltatime, E_STEP step) override {};

	/**
	 * @brief ���̓G�͎g�p���Ȃ�
	 * @param deltatime �f���^�^�C��
	 * @param step �X�e�[�g�̏����i�K
	 */
	void State_Detour(float deltatime, E_STEP step) override {};

	/**
	 * @brief ���̓G�͎g�p���Ȃ�
	 * @param deltatime �f���^�^�C��
	 * @param step �X�e�[�g�̏����i�K
	 */
	void State_Tracking(float deltatime, E_STEP step) override {};

	/**
	 * @brief ���̓G�͎g�p���Ȃ�
	 * @param deltatime �f���^�^�C��
	 * @param step �X�e�[�g�̏����i�K
	 */
	void State_Avoidance(float deltatime, E_STEP step) override {};

	/**
	 * @brief �_���[�W���󂯂����̏���
	 * @param deltatime �f���^�^�C��
	 * @param step �X�e�[�g�̏����i�K
	 */
	void State_Damage(float deltatime, E_STEP step) override;

	/**
	 * @brief ���S���̏���
	 * @param deltatime �f���^�^�C��
	 * @param step �X�e�[�g�̏����i�K
	 */
	void State_Dead(float deltatime, E_STEP step) override;

	void State_Attack1(float deltatime, E_STEP step) override {};
	void State_Attack2(float deltatime, E_STEP step) override {};
	void State_Attack3(float deltatime, E_STEP step) override {};

	/*
	==================================================

	�萔

	==================================================
	*/
	const float SPAWN_FREEZE_TIME = 0.5f;	//�������̍d������
};

#endif // !__TUTORIAL_ENEMY_H__

