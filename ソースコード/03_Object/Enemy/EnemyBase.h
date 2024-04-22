/*********************************************************************
 * @file   EnemyBase.h
 * @brief  敵のベースクラス
 *********************************************************************/
#ifndef __ENEMY_BASE_H__
#define __ENEMY_BASE_H__

 /*
 ==================================================

 インクルード

 ==================================================
 */

#include "../Object.h"
#include "../Collider/Collider.h"
#include "../Item/Item_Heal.h" 
#include "../Item/Item_Stamina.h"
#include "../Bullet/Bullet.h"

#include "../../02_Component/Model/Model.h"
#include "../../02_Component/HP/HPBase.h"
#include "../../02_Component/Shader/Shader.h"

#include "../../04_Scene/SceneBase.h"
#include "../../04_Scene/SceneController.h"

class EnemyBase : public Object
{
public:
	/*
	===================================================================

	列挙型

	===================================================================
	*/
	enum class E_STEP
	{
		Start,
		Loop,
		End,
	};

	enum class E_ENEMY_STATE
	{
		None,		//なし
		Spawn,		//生成
		Idle,		//待機
		Walk,		//移動
		Tracking,	//追跡
		Detour,		//迂回
		Avoidance,	//回避
		Damage,		//被弾
		Dead,		//死亡
		Attack1,	//攻撃種類１
		Attack2,	//攻撃種類２
		Attack3,	//攻撃種類３
	};

	/**
	 * 	@brief ステートマシン用関数ポインタ
	 */
	typedef void(EnemyBase::* pEnemyStateMachine)(float deltatime, E_STEP step);

	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief 更新処理
	 * @param deltatime デルタタイム
	 */
	void Update(float deltatime) override;

	/*
	==================================================

	セッター

	==================================================
	*/

	/**
	 * @brief 生成位置を設定する
	 * @param pos 生成位置
	 */
	inline void Set_SpawnPos(const DirectX::XMFLOAT3& pos) { m_SpawnPos = pos; }

protected:
	//- ステート関数
	virtual void State_Spawn(float deltatime, E_STEP step) {};
	virtual void State_Idle(float deltatime, E_STEP step) {};
	virtual void State_Walk(float deltatime, E_STEP step) {};
	virtual void State_Detour(float deltatime, E_STEP step) {};
	virtual void State_Tracking(float deltatime, E_STEP step) {};
	virtual void State_Avoidance(float deltatime, E_STEP step) {};
	virtual void State_Damage(float deltatime, E_STEP step) {};
	virtual void State_Dead(float deltatime, E_STEP step) {};
	virtual void State_Attack1(float deltatime, E_STEP step) {};
	virtual void State_Attack2(float deltatime, E_STEP step) {};
	virtual void State_Attack3(float deltatime, E_STEP step) {};

	/**
	 * @brief 正面ベクトルと任意のベクトルの角度を求める
	 * @param vTarget 目標のベクトル
	 * @return 360度形式の角度
	 */
	float AngleFromFrontVector(DirectX::XMVECTOR vTarget);

	/**
	 * @brief 目標の方向に向く計算を行う
	 */
	void ToTargetRotation(DirectX::XMVECTOR vTo);

	/**
	 * @brief 次のステートを設定する
	 * @param state ステート
	 * @param force 強制的にステートを変更するか
	 * @return 
	 */
	inline bool ChangeState(E_ENEMY_STATE state, bool force = true)
	{
		if (!force && m_nextState != E_ENEMY_STATE::None) { return false; }
		m_nextState = state;
	}

	/**
	 * @brief ターゲットまでの距離を計算する
	 * ピタゴラスの定理を使用
	 * @param TargetPos 目標の位置
	 * @return 直線距離
	 */
	/**
	 * @brief ターゲットまでの距離を計算する
	 * ピタゴラスの定理を使用
	 * @param TargetPos 目標の位置
	 * @param xzDistance XZ平面のみの距離を計算するか
	 * @return 距離
	 */
	inline float DistanceToTarget(DirectX::XMFLOAT3 TargetPos,bool xzDistance = false)
	{
		float dist;
		if (xzDistance)
		{
			dist = sqrtf(
				(TargetPos.x - m_pos.x) * (TargetPos.x - m_pos.x) +
				(TargetPos.z - m_pos.z) * (TargetPos.z - m_pos.z));
		}
		else
		{
			dist = sqrtf(
				(TargetPos.x - m_pos.x) * (TargetPos.x - m_pos.x) +
				(TargetPos.y - m_pos.y) * (TargetPos.y - m_pos.y) +
				(TargetPos.z - m_pos.z) * (TargetPos.z - m_pos.z));
		}
		return dist;
	}

	/**
	 * @brief 指定したオブジェクトまでのベクトルを求める
	 * @param target 目標オブジェクト
	 * @return 目標ベクトル
	 */
	inline DirectX::XMVECTOR Get_toTargetVector(Object* target)
	{
		DirectX::XMFLOAT3 targetPos = target->Get_Pos();
		DirectX::XMVECTOR vToTarget = DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&targetPos), DirectX::XMLoadFloat3(&m_pos));
		return vToTarget;
	}

	/**
	 * @brief 指定した座標までのベクトルを求める
	 * @param targetPos 目標の座標
	 * @return 目標ベクトル
	 */
	inline DirectX::XMVECTOR Get_toTargetVector(DirectX::XMFLOAT3 targetPos)
	{
		DirectX::XMVECTOR vToTarget = DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&targetPos), DirectX::XMLoadFloat3(&m_pos));
		return vToTarget;
	}

	/**
	 * @brief 移動量をベクトルから作成する
	 * @param vToTarget 目標ベクトル
	 * @param Scale ベクトルの大きさ
	 * @return 移動量
	 */
	inline DirectX::XMFLOAT3 CreateMovement(DirectX::XMVECTOR vToTarget, float Scale = 1.0f)
	{
		vToTarget = DirectX::XMVector3Normalize(vToTarget);
		vToTarget = DirectX::XMVectorScale(vToTarget, Scale);
		DirectX::XMFLOAT3 movment = {};
		DirectX::XMStoreFloat3(&movment, vToTarget);
		return movment;
	}

	/**
	 * @brief ランダムの値を生成する
	 * @param randomRange 出現値の範囲
	 * @param includeUpper 出現値に最大値を含めるか
	 * @param sub 出現値を-X～Xの範囲にするか
	 * @return ランダム値
	 */
	inline float GenerateRandom(float randomRange,bool includeUpper = false,bool sub = true)
	{
		float halfRange = 0.0f;
		//- 出現値に最大値を含める
		if (includeUpper){	randomRange += 1.0f; }
		//- 出現値を-X～Xの範囲にする
		if (sub){ halfRange = randomRange * 0.5f;}
		float random = static_cast<float>(rand() % static_cast<int>(randomRange)) - halfRange;
		return random;
	}


	std::map<E_ENEMY_STATE, pEnemyStateMachine> m_stateMap = {};	//ステートマップ
	E_ENEMY_STATE m_curState  = E_ENEMY_STATE::Spawn;//現在のステート
	E_ENEMY_STATE m_nextState = E_ENEMY_STATE::None; //次のステート
	E_ENEMY_STATE m_oldState  = E_ENEMY_STATE::None; //前のステート

	DirectX::XMFLOAT3 m_SpawnPos  = {};	//生成位置
	DirectX::XMFLOAT3 m_TargetPos = {};	//目標地点
	float m_StateCurTime	= 0.0f;		//ステートの継続時間
	float m_NextChangeTime	= 0.0f;		//次のステートに変更する時間
	float m_MoveSpeed		= 0.0f;		//移動速度

	class HPBase* m_pHP = nullptr;		//体力
	float m_oldHp		= 0.0f;			//前フレームの体力
};

#endif // !__ENEMY_BASE_H__

