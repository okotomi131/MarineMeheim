/*********************************************************************
 * @file   EnemyScorpionFish.h
 * @brief  敵(カサゴ)、基本的な動作行う敵
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
	 * @brief ランダムに移動先を決定し、移動する処理
	 * @param deltatime デルタタイム
	 * @param step ステートの処理段階
	 */
	void State_Walk(float deltatime, E_STEP step) override;

	/**
	 * @brief 障害物を避ける処理
	 * @param deltatime デルタタイム
	 * @param step ステートの処理段階
	 */
	void State_Detour(float deltatime, E_STEP step) override;

	/**
	 * @brief 目標を追尾する処理
	 * @param deltatime デルタタイム
	 * @param step ステートの処理段階
	 */
	void State_Tracking(float deltatime, E_STEP step) override;

	/**
	 * @brief 回避行動を行う処理
	 * @param deltatime デルタタイム
	 * @param step ステートの処理段階
	 */
	void State_Avoidance(float deltatime, E_STEP step) override;

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

	/**
	 * @brief シングルショット
	 * @param deltatime デルタタイム
	 * @param step ステートの処理段階
	 */
	void State_Attack1(float deltatime, E_STEP step) override;


	void State_Attack2(float deltatime, E_STEP step) override;
	void State_Attack3(float deltatime, E_STEP step) override;


	/**
	 * @brief プレイヤーまでのベクトルを求める
	 * @return プレイヤーまでのベクトル
	 */
	DirectX::XMVECTOR Get_toPlayerVector();
	
	/**
	 * @brief プレイヤーが視界内にいるかを判定する
	 * @return 視界内にいればtrue
	 */
	bool CheckPlayerVisible();

	/**
	 * @brief 目標地点までの間に障害物があるかを判定する
	 * @return 障害物があればtrue
	 */
	bool CheckDestinationObstacle();

	/**
	 * @brief 歩行状態の移動処理
	 * @param deltatime デルタタイム
	 */
	void MoveAtWaling(float deltatime);

	/**
	 * @brief 目標の座標を生成する
	 */
	void CreateTargetPos();

	/**
	 * @brief 迂回する際の座標を決定する
	 * @param TargetPos 元々目指していた座標
	 */
	void DecisionDetourPos(DirectX::XMFLOAT3 TargetPos);

	/*
	==================================================

	定数

	==================================================
	*/
	const int	RANGE_DIRECTION_CHANGE = 3;	//方向転換の間隔
	const float SPAWN_FREEZE_TIME = 0.5f;	//生成時の硬直時間
	const float RANGE_IDLE_TIME = 1.0f;	//待機時の時間幅
	const float RANGE_TARGET_POS = 10.0f;//目標地点の範囲
	const float RANGE_TRAKING_TIME = 5.0f;	//追跡時間
	const float PLAYER_TRACKING_BLUR = 25.0f;	//プレイヤー追尾のブレ幅
	const float MIN_PLAYER_DISTANCE  = 15.0f;	//プレイヤーとの最大距離
	const float MIN_OBSTACLE_DISTANCE = 10.0f;	//障害物との最小距離
	const float RANDOM_MOVE_TIME = 2.0f;		//ランダム移動の時間
	const float RANDOM_TRAKING_IDLE_TIME = 1.0f;//追尾状態の時のランダム待機時間
	const float RANGE_TRACKING_TIME = 3.0f;		//追尾状態の時間
	const float MIN_WALK_APPROACH_DISTANCE = 0.5f;	//ランダム移動の最小距離
	const float RANGE_AVOIDANCE_POS = 1.5f;	//回避時の目標地点の範囲


	class Obstacle* m_pObstacle		= nullptr;
	class Player*   m_pPlayer		= nullptr;
	class WeaponBase* m_pWeapon = nullptr;
	std::vector<class Obstacle*> m_pObstacles = {};

	int	  m_DireChangeCnt   = 0;	//方向転換の残り回数
	float m_PlayerDistance  = 0.0f;	//プレイヤーまでの距離
	bool  m_bSearchObstacles	= false;
	bool  m_bTracking		= false;	//追跡中か
	bool  m_bDetour			= false;	//迂回中か
	DirectX::XMFLOAT3 m_AddPlayerPos = {};	//移動量の加算値
	DirectX::XMFLOAT3 m_movement	 = {};	//移動量

};

#endif // !__ENEMY_SCORPION_FISH_H_
