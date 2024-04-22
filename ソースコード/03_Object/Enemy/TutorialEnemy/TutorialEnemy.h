/*********************************************************************
 * @file   TutorialEnemy.h
 * @brief  チュートリアル用の敵
 *********************************************************************/
#ifndef __TUTORIAL_ENEMY_H__
#define __TUTORIAL_ENEMY_H__
/*
==================================================

インクルード

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

	ステート関数

	==================================================
	*/
	/**
	 * @brief 生成時の処理
	 * @param deltatime デルタタイム
	 * @param step ステートの処理段階
	 */
	void State_Spawn(float deltatime, E_STEP step) override;

	/*
	 * @brief 待機時の処理
	 * @param deltatime デルタタイム
	 * @param step ステートの処理段階
	 */
	void State_Idle(float deltatime, E_STEP step) override;

	/**
	 * @brief この敵は使用しない
	 * @param deltatime デルタタイム
	 * @param step ステートの処理段階
	 */
	void State_Walk(float deltatime, E_STEP step) override {};

	/**
	 * @brief この敵は使用しない
	 * @param deltatime デルタタイム
	 * @param step ステートの処理段階
	 */
	void State_Detour(float deltatime, E_STEP step) override {};

	/**
	 * @brief この敵は使用しない
	 * @param deltatime デルタタイム
	 * @param step ステートの処理段階
	 */
	void State_Tracking(float deltatime, E_STEP step) override {};

	/**
	 * @brief この敵は使用しない
	 * @param deltatime デルタタイム
	 * @param step ステートの処理段階
	 */
	void State_Avoidance(float deltatime, E_STEP step) override {};

	/**
	 * @brief ダメージを受けた時の処理
	 * @param deltatime デルタタイム
	 * @param step ステートの処理段階
	 */
	void State_Damage(float deltatime, E_STEP step) override;

	/**
	 * @brief 死亡時の処理
	 * @param deltatime デルタタイム
	 * @param step ステートの処理段階
	 */
	void State_Dead(float deltatime, E_STEP step) override;

	void State_Attack1(float deltatime, E_STEP step) override {};
	void State_Attack2(float deltatime, E_STEP step) override {};
	void State_Attack3(float deltatime, E_STEP step) override {};

	/*
	==================================================

	定数

	==================================================
	*/
	const float SPAWN_FREEZE_TIME = 0.5f;	//生成時の硬直時間
};

#endif // !__TUTORIAL_ENEMY_H__

