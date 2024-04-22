/*********************************************************************
 * @file   CameraPlayer.cpp
 * @brief  �v���C���[��ǔ�����J����
 *********************************************************************/
/*
==================================================

�C���N���[�h

==================================================
*/
#include "CameraPlayer.h"
#include "../../01_System/Window/WinStartUp.h"
#include "../../01_System/Input/Input.h"
#include "../../03_Object/Player/Player.h"
/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltatime">�f���^�^�C��</param>
void CameraPlayer::Update(float deltatime)
{
	TrackTargetBack();
}

/// <summary>
/// �J�����̒����_���擾
/// </summary>
/// <returns>�����_</returns>
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

	//- look�̒l���x�N�g���ɂ��Đ��K��
	DirectX::XMVECTOR vLook = DirectX::XMLoadFloat3(&look);
	vLook = DirectX::XMVector3Normalize(vLook);
	DirectX::XMStoreFloat3(&look, vLook);

	return look;
}

/// <summary>
/// �v���C���[��ǔ�����
/// </summary>
void CameraPlayer::TrackTargetBack()
{
	float backposY = 15.0f;
	float toTargetHeight = {};
	float toTargetLengthXZ = {};
	DirectX::XMFLOAT3 target = {};

	float speed = m_moveDelay;

	//- ��Ƀv���C���[�̌��̈ʒu�ɐݒ�
	if (m_pTargetObj)
	{
		DirectX::XMVECTOR vPFoward = m_pTargetObj->Get_vForward();
		vPFoward = DirectX::XMVector3Normalize(vPFoward);

		m_pos.x = m_pTargetObj->Get_Pos().x - DirectX::XMVectorGetX(vPFoward) * m_distToTarget;
		m_pos.z = m_pTargetObj->Get_Pos().z - DirectX::XMVectorGetZ(vPFoward) * m_distToTarget;
		m_pos.y = m_pTargetObj->Get_Pos().y - DirectX::XMVectorGetY(vPFoward) + (m_pTargetObj->Get_Rot().x * backposY);
	}

	//- XZ���ʏ�ł̒����_����J�����̈ʒu�܂ł̃x�N�g�������߂�
	{
		m_vToTarget = DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&m_pos),
			DirectX::XMLoadFloat3(&m_target));

		toTargetHeight = DirectX::XMVectorGetY(m_vToTarget);
		m_vToTarget = DirectX::XMVectorSetY(m_vToTarget, 0.0f);//XZ���ʂɂ��邽��Y������0

		toTargetLengthXZ = DirectX::XMVectorGetX(DirectX::XMVector3Length(m_vToTarget));//XZ���ʏ�ł̋���

		m_vToTarget = DirectX::XMVector3Normalize(m_vToTarget);
	}

	//- �����_���X�V����
	{
		target = m_pTargetObj->Get_Pos();
		target.y += m_targetHeight;
	}

	//- �X�V���������_����J�����ʒu�܂ł�XZ���ʏ�x�N�g��
	{
		m_vPos = DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&m_pos),
			DirectX::XMLoadFloat3(&m_target));
		m_vPos = DirectX::XMVectorSetY(m_vPos, 0.0f);
		m_vPos = DirectX::XMVector3Normalize(m_vPos);
	}

	//- �J�����ʒu���X�V����
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
