/*********************************************************************
 * @file   EnemyScorpionFish.h
 * @brief  �G(�J�T�S)�A��{�I�ȓ���s���G
 *********************************************************************/
#ifndef __ENEMY_SCORPION_FISH_H_
#define __ENEMY_SCORPION_FISH_H_

#include "../EnemyBase.h"

class EnemyScorpionFish : public EnemyBase
{
public:
	static void Load();

	void Init() override;
	void Update(float deltatime) override;
	
protected:
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
	 * @brief �����_���Ɉړ�������肵�A�ړ����鏈��
	 * @param deltatime �f���^�^�C��
	 * @param step �X�e�[�g�̏����i�K
	 */
	void State_Walk(float deltatime, E_STEP step) override;

	/**
	 * @brief ��Q��������鏈��
	 * @param deltatime �f���^�^�C��
	 * @param step �X�e�[�g�̏����i�K
	 */
	void State_Detour(float deltatime, E_STEP step) override;

	/**
	 * @brief �ڕW��ǔ����鏈��
	 * @param deltatime �f���^�^�C��
	 * @param step �X�e�[�g�̏����i�K
	 */
	void State_Tracking(float deltatime, E_STEP step) override;

	/**
	 * @brief ����s�����s������
	 * @param deltatime �f���^�^�C��
	 * @param step �X�e�[�g�̏����i�K
	 */
	void State_Avoidance(float deltatime, E_STEP step) override;

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

	/**
	 * @brief �V���O���V���b�g
	 * @param deltatime �f���^�^�C��
	 * @param step �X�e�[�g�̏����i�K
	 */
	void State_Attack1(float deltatime, E_STEP step) override;


	void State_Attack2(float deltatime, E_STEP step) override;
	void State_Attack3(float deltatime, E_STEP step) override;


	/**
	 * @brief �v���C���[�܂ł̃x�N�g�������߂�
	 * @return �v���C���[�܂ł̃x�N�g��
	 */
	DirectX::XMVECTOR Get_toPlayerVector();
	
	/**
	 * @brief �v���C���[�����E���ɂ��邩�𔻒肷��
	 * @return ���E���ɂ����true
	 */
	bool CheckPlayerVisible();

	/**
	 * @brief �ڕW�n�_�܂ł̊Ԃɏ�Q�������邩�𔻒肷��
	 * @return ��Q���������true
	 */
	bool CheckDestinationObstacle();

	/**
	 * @brief ���s��Ԃ̈ړ�����
	 * @param deltatime �f���^�^�C��
	 */
	void MoveAtWaling(float deltatime);

	/**
	 * @brief �ڕW�̍��W�𐶐�����
	 */
	void CreateTargetPos();

	/**
	 * @brief �I�񂷂�ۂ̍��W�����肷��
	 * @param TargetPos ���X�ڎw���Ă������W
	 */
	void DecisionDetourPos(DirectX::XMFLOAT3 TargetPos);

	/*
	==================================================

	�萔

	==================================================
	*/
	const int	RANGE_DIRECTION_CHANGE = 3;	//�����]���̊Ԋu
	const float SPAWN_FREEZE_TIME = 0.5f;	//�������̍d������
	const float RANGE_IDLE_TIME = 1.0f;	//�ҋ@���̎��ԕ�
	const float RANGE_TARGET_POS = 10.0f;//�ڕW�n�_�͈̔�
	const float RANGE_TRAKING_TIME = 5.0f;	//�ǐՎ���
	const float PLAYER_TRACKING_BLUR = 25.0f;	//�v���C���[�ǔ��̃u����
	const float MIN_PLAYER_DISTANCE  = 15.0f;	//�v���C���[�Ƃ̍ő勗��
	const float MIN_OBSTACLE_DISTANCE = 10.0f;	//��Q���Ƃ̍ŏ�����
	const float RANDOM_MOVE_TIME = 2.0f;		//�����_���ړ��̎���
	const float RANDOM_TRAKING_IDLE_TIME = 1.0f;//�ǔ���Ԃ̎��̃����_���ҋ@����
	const float RANGE_TRACKING_TIME = 3.0f;		//�ǔ���Ԃ̎���
	const float MIN_WALK_APPROACH_DISTANCE = 0.5f;	//�����_���ړ��̍ŏ�����
	const float RANGE_AVOIDANCE_POS = 1.5f;	//������̖ڕW�n�_�͈̔�


	class Obstacle* m_pObstacle		= nullptr;
	class Player*   m_pPlayer		= nullptr;
	class WeaponBase* m_pWeapon = nullptr;
	std::vector<class Obstacle*> m_pObstacles = {};

	int	  m_DireChangeCnt   = 0;	//�����]���̎c���
	float m_PlayerDistance  = 0.0f;	//�v���C���[�܂ł̋���
	bool  m_bSearchObstacles	= false;
	bool  m_bTracking		= false;	//�ǐՒ���
	bool  m_bDetour			= false;	//�I�񒆂�
	DirectX::XMFLOAT3 m_AddPlayerPos = {};	//�ړ��ʂ̉��Z�l
	DirectX::XMFLOAT3 m_movement	 = {};	//�ړ���

};

#endif // !__ENEMY_SCORPION_FISH_H_
