/*********************************************************************
 * @file   Spawner.h
 * @brief  �X�|�i�[�N���X
 *********************************************************************/
#ifndef __SPAWNER_H__
#define __SPAWNER_H__

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../../Enemy/EnemyBase.h"

class EnemySpawner : public EnemyBase
{
public:
	/*
	==================================================

	�񋓌^

	==================================================
	*/
	//- ��������G�̎��
	enum class E_ENEMY_TYPE
	{
		None,
		ScorpionFish,
		GlobeFish,
		ClawnFish,
		
		Max
	};

	void Init();
	void Update(float deltatime) override;

	/**
	 * @brief ��������G�̎�ނ�ݒ肷��
	 * @param ��������G�̎��
	 */
	inline void Set_SpawnType(E_ENEMY_TYPE type) { m_EnemyType = type; };

	/**
	 * @brief ��������G�̎�ނ�ݒ肷��
	 * 2��ނ̓G�𓯎��ɐ�������ꍇ�Ɏg�p
	 * @param ��������G�̎��
	 * @param ��������G�̎��2
	 */
	inline void Set_SpawnType(E_ENEMY_TYPE type,E_ENEMY_TYPE type2) { m_EnemyType = type; m_EnemyType2 = type2; };
	
	/**
	 * @brief �G�𐶐����ł��邩
	 * �������ɂ����_���[�W���󂯂Ȃ��悤�ɂ��邽�߂Ɏg�p
	 * @return �����t���O
	 */
	bool Get_Spawning() const { return m_bSpawning; }
private:
	void State_Spawn(float deltatime, E_STEP step) override;
	void State_Idle(float deltatime, E_STEP step) override;
	void State_Walk(float deltatime, E_STEP step) override;
	void State_Tracking(float deltatime, E_STEP step) override;
	void State_Avoidance(float deltatime, E_STEP step) override;
	void State_Damage(float deltatime, E_STEP step) override;
	void State_Dead(float deltatime, E_STEP step) override;
	void State_Attack1(float deltatime, E_STEP step) override;
	void State_Attack2(float deltatime, E_STEP step) override;
	void State_Attack3(float deltatime, E_STEP step) override;

	E_ENEMY_TYPE m_EnemyType  = E_ENEMY_TYPE::None;
	E_ENEMY_TYPE m_EnemyType2 = E_ENEMY_TYPE::None;

	const float ROTATION_TIME = 5.0f;   //��]����
	const float ROTATION_FINISH_ANGLE = 180.0f; //��]�I���p�x

	float m_StartRotAngle = 0.0f; //��]�J�n�p�x
	float m_RotAngle = 0.0f; //��]�p�x
	float m_SpawnTime = 0.0f; //��������

	bool m_bSpawning = false; //��������
};

#endif // !__SPAWNER_H__


