/*********************************************************************
 * @file   CameraPlayer.cpp
 * @brief  プレイヤーを追尾するカメラ
 *********************************************************************/
/*
==================================================

インクルード

==================================================
*/
#include "CameraPlayer.h"
#include "../../01_System/Window/WinStartUp.h"
#include "../../01_System/Input/Input.h"
#include "../../03_Object/Player/Player.h"
/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltatime">デルタタイム</param>
void CameraPlayer::Update(float deltatime)
{
	TrackTargetBack();
}

/// <summary>
/// カメラの注視点を取得
/// </summary>
/// <returns>注視点</returns>
DirectX::XMFLOAT3 CameraPlayer::Get_LookPoint()
{
	DirectX::XMFLOAT3 look = {};
	float toTargetHeight = 5.5f;
	
	DirectX::XMFLOAT3 targetPos = m_pTargetObj->Get_Pos();

	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
	DirectX::XMVECTOR vTarget = DirectX::XMLoadFloat3(&targetPos);
	
	DirectX::XMVECTOR vToCamera = DirectX::XMVectorSubtract(vTarget,vPos);
	DirectX::XMVector3Normalize(vToCamera);

	DirectX::XMStoreFloat3(&look, vToCamera);
	look.y += toTargetHeight;

	//- lookの値をベクトルにして正規化
	DirectX::XMVECTOR vLook = DirectX::XMLoadFloat3(&look);
	vLook = DirectX::XMVector3Normalize(vLook);
	DirectX::XMStoreFloat3(&look, vLook);

	return look;
}

/// <summary>
/// プレイヤーを追尾する
/// </summary>
void CameraPlayer::TrackTargetBack()
{
	float backposY = 15.0f;
	float toTargetHeight = {};
	float toTargetLengthXZ = {};
	DirectX::XMFLOAT3 target = {};

	float speed = m_moveDelay;

	//- 常にプレイヤーの後ろの位置に設定
	if (m_pTargetObj)
	{
		DirectX::XMVECTOR vPFoward = m_pTargetObj->Get_vForward();
		vPFoward = DirectX::XMVector3Normalize(vPFoward);

		m_pos.x = m_pTargetObj->Get_Pos().x - DirectX::XMVectorGetX(vPFoward) * m_distToTarget;
		m_pos.z = m_pTargetObj->Get_Pos().z - DirectX::XMVectorGetZ(vPFoward) * m_distToTarget;
		m_pos.y = m_pTargetObj->Get_Pos().y - DirectX::XMVectorGetY(vPFoward) + (m_pTargetObj->Get_Rot().x * backposY);
	}

	//- XZ平面上での注視点からカメラの位置までのベクトルを求める
	{
		m_vToTarget = DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&m_pos),
			DirectX::XMLoadFloat3(&m_target));

		toTargetHeight = DirectX::XMVectorGetY(m_vToTarget);
		m_vToTarget = DirectX::XMVectorSetY(m_vToTarget, 0.0f);//XZ平面にするためY成分を0

		toTargetLengthXZ = DirectX::XMVectorGetX(DirectX::XMVector3Length(m_vToTarget));//XZ平面上での距離

		m_vToTarget = DirectX::XMVector3Normalize(m_vToTarget);
	}

	//- 注視点を更新する
	{
		target = m_pTargetObj->Get_Pos();
		target.y += m_targetHeight;
	}

	//- 更新した注視点からカメラ位置までのXZ平面上ベクトル
	{
		m_vPos = DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&m_pos),
			DirectX::XMLoadFloat3(&m_target));
		m_vPos = DirectX::XMVectorSetY(m_vPos, 0.0f);
		m_vPos = DirectX::XMVector3Normalize(m_vPos);
	}

	//- カメラ位置を更新する
	{
		m_vPos = DirectX::XMVectorScale(m_vPos, speed);
		m_vToTarget = DirectX::XMVectorScale(m_vToTarget, 1.0f - speed);
		DirectX::XMVECTOR vNewPos = DirectX::XMVectorAdd(m_vPos, m_vToTarget);
		vNewPos = DirectX::XMVector3Normalize(vNewPos);
		vNewPos = DirectX::XMVectorScale(vNewPos, toTargetLengthXZ);
		vNewPos = DirectX::XMVectorSetY(vNewPos, toTargetHeight);

		DirectX::XMFLOAT3 fNewPos;
		DirectX::XMStoreFloat3(&fNewPos, vNewPos);
		m_pos.x = target.x + fNewPos.x;
		m_pos.y = target.y + fNewPos.y;
		m_pos.z = target.z + fNewPos.z;
		if (Input::Get_KeyPress(VK_F2) && Input::Get_KeyPress('P'))
		{
			m_pos.x -= m_pos.x;
			m_pos.z -= m_pos.z;
		}
		m_target = target;
	}


}
