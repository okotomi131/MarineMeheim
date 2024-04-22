/*********************************************************************
 * @file   EnemyBase.h
 * @brief  �G�̃x�[�X�N���X
 *********************************************************************/
#ifndef __ENEMY_BASE_H__
#define __ENEMY_BASE_H__

 /*
 ==================================================

 �C���N���[�h

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

	�񋓌^

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
		None,		//�Ȃ�
		Spawn,		//����
		Idle,		//�ҋ@
		Walk,		//�ړ�
		Tracking,	//�ǐ�
		Detour,		//�I��
		Avoidance,	//���
		Damage,		//��e
		Dead,		//���S
		Attack1,	//�U����ނP
		Attack2,	//�U����ނQ
		Attack3,	//�U����ނR
	};

	/**
	 * 	@brief �X�e�[�g�}�V���p�֐��|�C���^
	 */
	typedef void(EnemyBase::* pEnemyStateMachine)(float deltatime, E_STEP step);

	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �X�V����
	 * @param deltatime �f���^�^�C��
	 */
	void Update(float deltatime) override;

	/*
	==================================================

	�Z�b�^�[

	==================================================
	*/

	/**
	 * @brief �����ʒu��ݒ肷��
	 * @param pos �����ʒu
	 */
	inline void Set_SpawnPos(const DirectX::XMFLOAT3& pos) { m_SpawnPos = pos; }

protected:
	//- �X�e�[�g�֐�
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
	 * @brief ���ʃx�N�g���ƔC�ӂ̃x�N�g���̊p�x�����߂�
	 * @param vTarget �ڕW�̃x�N�g��
	 * @return 360�x�`���̊p�x
	 */
	float AngleFromFrontVector(DirectX::XMVECTOR vTarget);

	/**
	 * @brief �ڕW�̕����Ɍ����v�Z���s��
	 */
	void ToTargetRotation(DirectX::XMVECTOR vTo);

	/**
	 * @brief ���̃X�e�[�g��ݒ肷��
	 * @param state �X�e�[�g
	 * @param force �����I�ɃX�e�[�g��ύX���邩
	 * @return 
	 */
	inline bool ChangeState(E_ENEMY_STATE state, bool force = true)
	{
		if (!force && m_nextState != E_ENEMY_STATE::None) { return false; }
		m_nextState = state;
	}

	/**
	 * @brief �^�[�Q�b�g�܂ł̋������v�Z����
	 * �s�^�S���X�̒藝���g�p
	 * @param TargetPos �ڕW�̈ʒu
	 * @return ��������
	 */
	/**
	 * @brief �^�[�Q�b�g�܂ł̋������v�Z����
	 * �s�^�S���X�̒藝���g�p
	 * @param TargetPos �ڕW�̈ʒu
	 * @param xzDistance XZ���ʂ݂̂̋������v�Z���邩
	 * @return ����
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
	 * @brief �w�肵���I�u�W�F�N�g�܂ł̃x�N�g�������߂�
	 * @param target �ڕW�I�u�W�F�N�g
	 * @return �ڕW�x�N�g��
	 */
	inline DirectX::XMVECTOR Get_toTargetVector(Object* target)
	{
		DirectX::XMFLOAT3 targetPos = target->Get_Pos();
		DirectX::XMVECTOR vToTarget = DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&targetPos), DirectX::XMLoadFloat3(&m_pos));
		return vToTarget;
	}

	/**
	 * @brief �w�肵�����W�܂ł̃x�N�g�������߂�
	 * @param targetPos �ڕW�̍��W
	 * @return �ڕW�x�N�g��
	 */
	inline DirectX::XMVECTOR Get_toTargetVector(DirectX::XMFLOAT3 targetPos)
	{
		DirectX::XMVECTOR vToTarget = DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&targetPos), DirectX::XMLoadFloat3(&m_pos));
		return vToTarget;
	}

	/**
	 * @brief �ړ��ʂ��x�N�g������쐬����
	 * @param vToTarget �ڕW�x�N�g��
	 * @param Scale �x�N�g���̑傫��
	 * @return �ړ���
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
	 * @brief �����_���̒l�𐶐�����
	 * @param randomRange �o���l�͈̔�
	 * @param includeUpper �o���l�ɍő�l���܂߂邩
	 * @param sub �o���l��-X�`X�͈̔͂ɂ��邩
	 * @return �����_���l
	 */
	inline float GenerateRandom(float randomRange,bool includeUpper = false,bool sub = true)
	{
		float halfRange = 0.0f;
		//- �o���l�ɍő�l���܂߂�
		if (includeUpper){	randomRange += 1.0f; }
		//- �o���l��-X�`X�͈̔͂ɂ���
		if (sub){ halfRange = randomRange * 0.5f;}
		float random = static_cast<float>(rand() % static_cast<int>(randomRange)) - halfRange;
		return random;
	}


	std::map<E_ENEMY_STATE, pEnemyStateMachine> m_stateMap = {};	//�X�e�[�g�}�b�v
	E_ENEMY_STATE m_curState  = E_ENEMY_STATE::Spawn;//���݂̃X�e�[�g
	E_ENEMY_STATE m_nextState = E_ENEMY_STATE::None; //���̃X�e�[�g
	E_ENEMY_STATE m_oldState  = E_ENEMY_STATE::None; //�O�̃X�e�[�g

	DirectX::XMFLOAT3 m_SpawnPos  = {};	//�����ʒu
	DirectX::XMFLOAT3 m_TargetPos = {};	//�ڕW�n�_
	float m_StateCurTime	= 0.0f;		//�X�e�[�g�̌p������
	float m_NextChangeTime	= 0.0f;		//���̃X�e�[�g�ɕύX���鎞��
	float m_MoveSpeed		= 0.0f;		//�ړ����x

	class HPBase* m_pHP = nullptr;		//�̗�
	float m_oldHp		= 0.0f;			//�O�t���[���̗̑�
};

#endif // !__ENEMY_BASE_H__

