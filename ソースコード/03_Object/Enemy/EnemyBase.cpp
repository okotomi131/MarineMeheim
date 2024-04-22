/*********************************************************************
 * @file   EnemyBase.cpp
 * @brief  敵のベースクラス
 *********************************************************************/

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "EnemyBase.h"

#include "../../01_System/Save/DataSave.h"
#include "../../01_System/Input/Input.h"
#include "../../02_Component/Model/Model.h"
#include "../../02_Component/HP/HPBase.h"

/*
===================================================================

定数・マクロ定義

===================================================================
*/
#define TWO_PI (2.0f * DirectX::XM_PI)

void EnemyBase::Init()
{
	//- ステートマップ作成
	m_stateMap.emplace(E_ENEMY_STATE::Spawn,&EnemyBase::State_Spawn);
	m_stateMap.emplace(E_ENEMY_STATE::Idle, &EnemyBase::State_Idle);
	m_stateMap.emplace(E_ENEMY_STATE::Walk, &EnemyBase::State_Walk);
	m_stateMap.emplace(E_ENEMY_STATE::Detour, &EnemyBase::State_Detour);
	m_stateMap.emplace(E_ENEMY_STATE::Tracking, &EnemyBase::State_Tracking);
	m_stateMap.emplace(E_ENEMY_STATE::Avoidance, &EnemyBase::State_Avoidance);
	m_stateMap.emplace(E_ENEMY_STATE::Damage, &EnemyBase::State_Damage);
	m_stateMap.emplace(E_ENEMY_STATE::Dead, &EnemyBase::State_Dead);
	m_stateMap.emplace(E_ENEMY_STATE::Attack1, &EnemyBase::State_Attack1);
	m_stateMap.emplace(E_ENEMY_STATE::Attack2, &EnemyBase::State_Attack2);
	m_stateMap.emplace(E_ENEMY_STATE::Attack3, &EnemyBase::State_Attack3);

	m_pHP = Add_Component<HPBase>();
	m_pHP->Set_MaxHP(100.0f);
}

void EnemyBase::Update(float deltatime)
{
	//- 次のステートが予約された
	if (m_nextState != E_ENEMY_STATE::None)
	{
		//- 現在のステートを終了
		if (m_stateMap.find(m_curState) != m_stateMap.end() && //m_curStateがキーとして存在するか
			m_stateMap[m_curState] != nullptr)
		{
			(this->*m_stateMap[m_curState])(deltatime, E_STEP::End);
		}
		//- 次のステートを開始
		if (m_stateMap.find(m_nextState) != m_stateMap.end() &&
			m_stateMap[m_nextState] != nullptr)
		{
			(this->*m_stateMap[m_nextState])(deltatime, E_STEP::Start);
		}

		m_oldState = m_curState;
		m_curState = m_nextState;
		m_nextState = E_ENEMY_STATE::None;
	}

	if (m_stateMap.find(m_curState) != m_stateMap.end() &&
		m_stateMap[m_curState] != nullptr)
	{
		(this->*m_stateMap[m_curState])(deltatime, E_STEP::Loop);
	}



/*
======================================================

--------------------デバック用--------------------

======================================================
*/

	if (Input::Get_KeyPress(VK_F1) && Input::Get_KeyPress('P'))
	{	
		Get_Component<HPBase>()->Set_MaxHP(1.0f);	}

}

float EnemyBase::AngleFromFrontVector(DirectX::XMVECTOR vTarget)
{
	DirectX::XMVECTOR vForward = Get_vForward();
	vForward = DirectX::XMVector3Normalize(vForward);
	vTarget  = DirectX::XMVector3Normalize(vTarget);
	float angle = 0.0f;
	//- ベクトル同士の角度を内積から求める
	DirectX::XMStoreFloat(&angle, DirectX::XMVector3Dot(vForward, vTarget));
	angle = std::max(-1.0f, std::min(1.0f, angle));//-nan(ind)を防ぐ為、-1.0f～1.0fの範囲に収める
	angle = acosf(angle);//度数→ラジアン
	/*
	内積は0~180度の範囲でしか計算できず、前後どちらにいるかがわからない
	外積を使用し、プレイヤーが前方にいるかを判定する
	*/
	DirectX::XMVECTOR vCross = DirectX::XMVector3Cross(vForward, vTarget);//垂直ベクトルを計算する
	DirectX::XMFLOAT3 cross;
	DirectX::XMStoreFloat3(&cross, vCross);
	/*
	垂直ベクトルのY成分が下向き(負)であれば、プレイヤーは左側にいる
	この場合は内積からの角度で前後の区別ができない為、360度の範囲に修正する
	*/
	if (cross.y < 0.0f)
	{	
		//πはラジアンで180度、360度範囲に修正する為ラジアン角を2πから引く
		angle = TWO_PI - angle;	
	}
	//- ラジアン→度数
	angle = DirectX::XMConvertToDegrees(angle);
	return angle;
}


void EnemyBase::ToTargetRotation(DirectX::XMVECTOR vTo)
{
	//- 目標までのベクトルを作成
	vTo = DirectX::XMVector3Normalize(vTo);
	//- 目標までのベクトルの長さを取得
	DirectX::XMFLOAT3 toDire;
	DirectX::XMStoreFloat3(&toDire, vTo);

	//- Y軸回転を行うため、XZの平面上でベクトルの先端座標から角度を計算する
	//  返却値は-π～π(-180~180)の範囲で返される
	//float tanAngle = atan2f(toPlayerDire.x, toPlayerDire.z);
	float tanAngle = atan2f(toDire.x, toDire.z);

	//- 現在の角度を上で求めた-π～πの範囲に修正する
	/*
	回転は0~2π以上の範囲で行われる可能性がある。これを-π～πの範囲に修正する
	①πを加算し元の範囲よりπ分シフトする
	※0~2π->π~3π
	②2πで割ることで余りを0,π,2πのどれかにする
	※3πを2πで割る余りはπ
	③πで減算し-π～πの範囲に修正する
	※π-π=0である為、-π～πの範囲
	*/
	float curAngle =
		fmodf(m_rot.y + DirectX::XM_PI, DirectX::XM_2PI) - DirectX::XM_PI;
	float diffAngle = tanAngle - curAngle;

	//- 最短で回転できる方向を探す
	if (diffAngle > DirectX::XM_PI)
	{
		//- πより多い値であれば、-πの範囲に修正する
		diffAngle -= DirectX::XM_2PI;
	}
	else if (diffAngle < -DirectX::XM_PI)
	{
		//- -π未満であれば、πの範囲に修正する
		diffAngle += DirectX::XM_2PI;
	}

	// 現在の角度に差を加える
	m_rot.y += diffAngle;
}

