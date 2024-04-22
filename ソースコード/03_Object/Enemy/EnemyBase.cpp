/*********************************************************************
 * @file   EnemyBase.cpp
 * @brief  �G�̃x�[�X�N���X
 *********************************************************************/

 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "EnemyBase.h"

#include "../../01_System/Save/DataSave.h"
#include "../../01_System/Input/Input.h"
#include "../../02_Component/Model/Model.h"
#include "../../02_Component/HP/HPBase.h"

/*
===================================================================

�萔�E�}�N����`

===================================================================
*/
#define TWO_PI (2.0f * DirectX::XM_PI)

void EnemyBase::Init()
{
	//- �X�e�[�g�}�b�v�쐬
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
	//- ���̃X�e�[�g���\�񂳂ꂽ
	if (m_nextState != E_ENEMY_STATE::None)
	{
		//- ���݂̃X�e�[�g���I��
		if (m_stateMap.find(m_curState) != m_stateMap.end() && //m_curState���L�[�Ƃ��đ��݂��邩
			m_stateMap[m_curState] != nullptr)
		{
			(this->*m_stateMap[m_curState])(deltatime, E_STEP::End);
		}
		//- ���̃X�e�[�g���J�n
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

--------------------�f�o�b�N�p--------------------

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
	//- �x�N�g�����m�̊p�x����ς��狁�߂�
	DirectX::XMStoreFloat(&angle, DirectX::XMVector3Dot(vForward, vTarget));
	angle = std::max(-1.0f, std::min(1.0f, angle));//-nan(ind)��h���ׁA-1.0f�`1.0f�͈̔͂Ɏ��߂�
	angle = acosf(angle);//�x�������W�A��
	/*
	���ς�0~180�x�͈̔͂ł����v�Z�ł����A�O��ǂ���ɂ��邩���킩��Ȃ�
	�O�ς��g�p���A�v���C���[���O���ɂ��邩�𔻒肷��
	*/
	DirectX::XMVECTOR vCross = DirectX::XMVector3Cross(vForward, vTarget);//�����x�N�g�����v�Z����
	DirectX::XMFLOAT3 cross;
	DirectX::XMStoreFloat3(&cross, vCross);
	/*
	�����x�N�g����Y������������(��)�ł���΁A�v���C���[�͍����ɂ���
	���̏ꍇ�͓��ς���̊p�x�őO��̋�ʂ��ł��Ȃ��ׁA360�x�͈̔͂ɏC������
	*/
	if (cross.y < 0.0f)
	{	
		//�΂̓��W�A����180�x�A360�x�͈͂ɏC������׃��W�A���p��2�΂������
		angle = TWO_PI - angle;	
	}
	//- ���W�A�����x��
	angle = DirectX::XMConvertToDegrees(angle);
	return angle;
}


void EnemyBase::ToTargetRotation(DirectX::XMVECTOR vTo)
{
	//- �ڕW�܂ł̃x�N�g�����쐬
	vTo = DirectX::XMVector3Normalize(vTo);
	//- �ڕW�܂ł̃x�N�g���̒������擾
	DirectX::XMFLOAT3 toDire;
	DirectX::XMStoreFloat3(&toDire, vTo);

	//- Y����]���s�����߁AXZ�̕��ʏ�Ńx�N�g���̐�[���W����p�x���v�Z����
	//  �ԋp�l��-�΁`��(-180~180)�͈̔͂ŕԂ����
	//float tanAngle = atan2f(toPlayerDire.x, toPlayerDire.z);
	float tanAngle = atan2f(toDire.x, toDire.z);

	//- ���݂̊p�x����ŋ��߂�-�΁`�΂͈̔͂ɏC������
	/*
	��]��0~2�Έȏ�͈̔͂ōs����\��������B�����-�΁`�΂͈̔͂ɏC������
	�@�΂����Z�����͈̔͂��Ε��V�t�g����
	��0~2��->��~3��
	�A2�΂Ŋ��邱�Ƃŗ]���0,��,2�΂̂ǂꂩ�ɂ���
	��3�΂�2�΂Ŋ���]��̓�
	�B�΂Ō��Z��-�΁`�΂͈̔͂ɏC������
	����-��=0�ł���ׁA-�΁`�΂͈̔�
	*/
	float curAngle =
		fmodf(m_rot.y + DirectX::XM_PI, DirectX::XM_2PI) - DirectX::XM_PI;
	float diffAngle = tanAngle - curAngle;

	//- �ŒZ�ŉ�]�ł��������T��
	if (diffAngle > DirectX::XM_PI)
	{
		//- �΂�葽���l�ł���΁A-�΂͈̔͂ɏC������
		diffAngle -= DirectX::XM_2PI;
	}
	else if (diffAngle < -DirectX::XM_PI)
	{
		//- -�Ζ����ł���΁A�΂͈̔͂ɏC������
		diffAngle += DirectX::XM_2PI;
	}

	// ���݂̊p�x�ɍ���������
	m_rot.y += diffAngle;
}

