/*********************************************************************
 * @file   Spawner.h
 * @brief  スポナークラス
 *********************************************************************/
#ifndef __SPAWNER_H__
#define __SPAWNER_H__

/*
==================================================

インクルード

==================================================
*/
#include "../../Enemy/EnemyBase.h"

class EnemySpawner : public EnemyBase
{
public:
	/*
	==================================================

	列挙型

	==================================================
	*/
	//- 生成する敵の種類
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
	 * @brief 生成する敵の種類を設定する
	 * @param 生成する敵の種類
	 */
	inline void Set_SpawnType(E_ENEMY_TYPE type) { m_EnemyType = type; };

	/**
	 * @brief 生成する敵の種類を設定する
	 * 2種類の敵を同時に生成する場合に使用
	 * @param 生成する敵の種類
	 * @param 生成する敵の種類2
	 */
	inline void Set_SpawnType(E_ENEMY_TYPE type,E_ENEMY_TYPE type2) { m_EnemyType = type; m_EnemyType2 = type2; };
	
	/**
	 * @brief 敵を生成中であるか
	 * 生成中にしかダメージを受けないようにするために使用
	 * @return 生成フラグ
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

	const float ROTATION_TIME = 5.0f;   //回転時間
	const float ROTATION_FINISH_ANGLE = 180.0f; //回転終了角度

	float m_StartRotAngle = 0.0f; //回転開始角度
	float m_RotAngle = 0.0f; //回転角度
	float m_SpawnTime = 0.0f; //生成時間

	bool m_bSpawning = false; //生成中か
};

#endif // !__SPAWNER_H__


