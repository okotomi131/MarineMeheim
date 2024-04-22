/*********************************************************************
 * @file   EnemySpawner.cpp
 * @brief  �X�|�i�[
 *********************************************************************/

/*
==================================================

�C���N���[�h

==================================================
*/
#include "EnemySpawner.h"

#include "../../Collider/Collider.h"
#include "../../Weapon/EnemyWeapon/WeaponScorpion.h"
#include "../Scorpionfish/EnemyScorpionFish.h"
#include "../GlobeFish/GlobeFish.h"
#include "../Clownfish/Clownfish.h"

void EnemySpawner::Init()
{
	EnemyBase::Init();
	m_pHP->Set_MaxHP(35.0f);

	//- ���f���ݒ�
	{
		Add_Component<Shader>()->Load(
			"Assets/Shader/VS_Object.cso",
			"Assets/Shader/PS_Light.cso");
		Add_Component<Model>()->Load("Assets/Model/Enemy/Spawner.obj");
	}

	float size = 5.0f;
	m_size = { size,size,size };

	//- �R���C�_�[�ݒ�
	{
		Collider* coll = Add_Obj<Collider>();
		coll->Set_Tag("Spawner");
		coll->Set_WorldMatrix(Get_WorldMatrix());
		coll->Set_Pos({ 0.0f,1.0f,0.0f });
		coll->Set_wSize({ 1.0f,3.0f,1.0f });
	}

	ChangeState(E_ENEMY_STATE::Spawn);
}

void EnemySpawner::Update(float deltatime)
{	
	Get_Obj<Collider>()->Set_WorldMatrix(Get_WorldMatrix());
	/*
	�_���[�W���󂯂Ă�����������B
	*/
	if (m_pHP->Get_HpData().curHp <= 0.0f)
	{
		//- ���S����
		ChangeState(E_ENEMY_STATE::Dead);
	}

	EnemyBase::Update(deltatime);
}

void EnemySpawner::State_Spawn(float deltatime, E_STEP step)
{
	switch (step)
	{
	case EnemyBase::E_STEP::Start:m_pos = m_SpawnPos;	break;
	case EnemyBase::E_STEP::Loop:
		ChangeState(E_ENEMY_STATE::Attack1);
		break;
	case EnemyBase::E_STEP::End:
		break;
	}
}

void EnemySpawner::State_Idle(float deltatime, E_STEP step)
{
	switch (step)
	{
	case EnemyBase::E_STEP::Start:
		m_NextChangeTime = 5.0f;
		break;
	case EnemyBase::E_STEP::Loop:
		if (m_StateCurTime >= m_NextChangeTime)
		{
			m_StateCurTime = 0.0f;
			ChangeState(E_ENEMY_STATE::Attack1);
		}
		m_StateCurTime += deltatime;
		break;
	case EnemyBase::E_STEP::End:
		break;
	}
}

void EnemySpawner::State_Walk(float deltatime, E_STEP step)
{
	switch (step)
	{
	case EnemyBase::E_STEP::Start:
		break;
	case EnemyBase::E_STEP::Loop:
		break;
	case EnemyBase::E_STEP::End:
		break;
	}
}

void EnemySpawner::State_Tracking(float deltatime, E_STEP step)
{
	switch (step)
	{
	case EnemyBase::E_STEP::Start:
		break;
	case EnemyBase::E_STEP::Loop:
		break;
	case EnemyBase::E_STEP::End:
		break;
	}
}

void EnemySpawner::State_Avoidance(float deltatime, E_STEP step)
{
	switch (step)
	{
	case EnemyBase::E_STEP::Start:
		break;
	case EnemyBase::E_STEP::Loop:
		break;
	case EnemyBase::E_STEP::End:
		break;
	}
}

void EnemySpawner::State_Damage(float deltatime, E_STEP step)
{
	switch (step)
	{
	case EnemyBase::E_STEP::Start:
		break;
	case EnemyBase::E_STEP::Loop:
		break;
	case EnemyBase::E_STEP::End:
		break;
	}
}

void EnemySpawner::State_Dead(float deltatime, E_STEP step)
{
	switch (step)
	{
	case EnemyBase::E_STEP::Start:

		break;
	case EnemyBase::E_STEP::Loop:
	{
		float addsizeY = 0.1f;
		float diffsizeXZ = 0.1f;

		//- Y����L�΂�XZ�����k�߂�
		m_size.y += addsizeY;
		m_size.x -= diffsizeXZ;
		m_size.z -= diffsizeXZ;

		if (m_size.x < 0.0f || m_size.z < 0.0f)
		{
			m_size.x = 0.0f;
			m_size.z = 0.0f;
			Set_Destory();
			SceneBase* scene = SceneController::Get_Scene();
			//- �A�C�e���𐶐�
			int item = rand() % 3;
			if (item == 0)
			{
				Item_Stamina* stamina = scene->Add_Object<Item_Stamina>();
				stamina->Set_Pos(m_pos);
			}
			else if (item == 1)
			{
				Item_Heal* heal = scene->Add_Object<Item_Heal>();
				heal->Set_Pos(m_pos);
			}
		}
	}
		break;
	case EnemyBase::E_STEP::End:
		break;
	}
}

void EnemySpawner::State_Attack1(float deltatime, E_STEP step)
{
	switch (step)
	{
	case EnemyBase::E_STEP::Start:
		m_RotAngle = ROTATION_FINISH_ANGLE / ROTATION_TIME;
		m_RotAngle = DirectX::XMConvertToRadians(m_RotAngle);
		m_StartRotAngle = m_rot.z;
		break;
	case EnemyBase::E_STEP::Loop:
		if (m_rot.z <= DirectX::XMConvertToRadians(ROTATION_FINISH_ANGLE) + m_StartRotAngle)
		{
			m_rot.z += m_RotAngle * deltatime;
		}
		else
		{
			m_bSpawning ?
				ChangeState(E_ENEMY_STATE::Idle) :
				ChangeState(E_ENEMY_STATE::Attack2);
		}

		break;
	case EnemyBase::E_STEP::End:
		break;
	}
}

void EnemySpawner::State_Attack2(float deltatime, E_STEP step)
{
	switch (step)
	{
	case EnemyBase::E_STEP::Start:
	{
		m_NextChangeTime = 20.0f;
		m_bSpawning = true;

		//- �V�[���ɓG��50�̈ȏア��ꍇ�͐������Ȃ�
		SceneBase* scene = SceneController::Get_Scene();
		std::vector<EnemyBase*> enemys = scene->Get_BaseObjects<EnemyBase>();
		int enemyNum = static_cast<int>(enemys.size());
		if (enemyNum >= 50)
		{
			m_StateCurTime = 0.0f;
			ChangeState(E_ENEMY_STATE::Idle);
		}
	}
		break;
	case EnemyBase::E_STEP::Loop:
	{
		float SpawnInterval = 2.0f;
		if (m_SpawnTime > SpawnInterval)
		{
			//- ���Ԋu�œG�𐶐�
			SceneBase* scene = SceneController::Get_Scene();
			EnemyScorpionFish* enemy;
			//- �w�肳�ꂽ�G�̎�ނɂ���Đ�������G��ς���
			switch (m_EnemyType)
			{
			case EnemySpawner::E_ENEMY_TYPE::ScorpionFish:
				enemy = scene->Add_Object<EnemyScorpionFish>();
				
				break;
			case EnemySpawner::E_ENEMY_TYPE::GlobeFish:
				enemy = scene->Add_Object<GlobeFish>();
				break;
			case EnemySpawner::E_ENEMY_TYPE::ClawnFish:
				enemy = scene->Add_Object<Clownfish>();
				break;
			default:
				enemy = scene->Add_Object<EnemyScorpionFish>();
				break;
			}
			enemy->Set_SpawnPos({ m_SpawnPos.x, 0.0f, m_SpawnPos.z });

			switch (m_EnemyType2)
			{
			case EnemySpawner::E_ENEMY_TYPE::None: break;
			case EnemySpawner::E_ENEMY_TYPE::ScorpionFish:
				enemy = scene->Add_Object<EnemyScorpionFish>();
				break;
			case EnemySpawner::E_ENEMY_TYPE::GlobeFish:
				enemy = scene->Add_Object<GlobeFish>();
				break;
			case EnemySpawner::E_ENEMY_TYPE::ClawnFish:
				enemy = scene->Add_Object<Clownfish>();
				break;
			default:
				enemy = scene->Add_Object<EnemyScorpionFish>();
				break;
			}
			enemy->Set_SpawnPos({ m_SpawnPos.x, 0.0f, m_SpawnPos.z });
			m_SpawnTime = 0.0f;
		}

		if (m_StateCurTime >= m_NextChangeTime)
		{
			m_StateCurTime = 0.0f;
			ChangeState(E_ENEMY_STATE::Idle);
		}

		m_StateCurTime += deltatime;
		m_SpawnTime += deltatime;
	}
		break;
	case EnemyBase::E_STEP::End:
		break;
	}
}

void EnemySpawner::State_Attack3(float deltatime, E_STEP step)
{
	switch (step)
	{
	case EnemyBase::E_STEP::Start:
		break;
	case EnemyBase::E_STEP::Loop:
		break;
	case EnemyBase::E_STEP::End:
		break;
	}
}
