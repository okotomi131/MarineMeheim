/*********************************************************************
 * @file   TutorialEnemy.cpp
 * @brief  チュートリアル用の敵
 *********************************************************************/
/*
==================================================

インクルード

==================================================
*/
#include "TutorialEnemy.h"

void TutorialEnemy::Load()
{
	Model::Preload("Assets/Model/Enemy/Tutorial.obj");
}

void TutorialEnemy::Init()
{
	EnemyBase::Init();
	m_pHP->Set_MaxHP(20.0f);

	Add_Component<Shader>()->Load("Assets/Shader/VS_Object.cso","Assets/Shader/PS_Light.cso");
	Add_Component<Model>()->Load("Assets/Model/Enemy/Tutorial.obj");

	m_size = {3.0f,3.0f,3.0f };
	m_rot.y = DirectX::XMConvertToRadians(180.0f);

	//- コライダー設定
	Collider* coll = Add_Obj<Collider>();
	coll->Set_Tag("TutorialEnemy");
	coll->Set_Pos({ 0.0f,1.0f,0.0f });
	coll->Set_Size({ 3.0f,3.0f,3.0f });
	coll->Set_WorldMatrix(Get_WorldMatrix());

	//- ステート
	ChangeState(E_ENEMY_STATE::Spawn);

}

void TutorialEnemy::Update(float deltatime)
{
	Get_Obj<Collider>()->Set_WorldMatrix(Get_WorldMatrix());
	SceneBase* scene = SceneController::Get_Scene();

	if (m_pHP->Get_HpData().curHp <= 0.0f) { ChangeState(E_ENEMY_STATE::Dead); }
	m_oldHp = m_pHP->Get_HpData().curHp;

	EnemyBase::Update(deltatime);
}

void TutorialEnemy::State_Spawn(float deltatime, E_STEP step)
{
	switch (step)
	{
	case E_STEP::Start:	m_pos = m_SpawnPos;	break;
	case E_STEP::Loop:
		m_StateCurTime += deltatime;
		//- 生成後、一定時間硬直
		if (SPAWN_FREEZE_TIME < m_StateCurTime)
		{
			ChangeState(E_ENEMY_STATE::Idle);
			m_StateCurTime = 0.0f;
		}
		break;
	case E_STEP::End:break;
	}
}

void TutorialEnemy::State_Idle(float deltatime, E_STEP step)
{
}

void TutorialEnemy::State_Damage(float deltatime, E_STEP step)
{
	switch (step)
	{
	case E_STEP::Start: break;
	case E_STEP::Loop:
		if (m_pHP->Get_HpData().curHp <= 0.0f)
		{ ChangeState(E_ENEMY_STATE::Dead); }
		else
		{ ChangeState(E_ENEMY_STATE::Idle); }
		m_oldHp = m_pHP->Get_HpData().curHp;
		break;
	case E_STEP::End: break;
	}
}

void TutorialEnemy::State_Dead(float deltatime, E_STEP step)
{
	switch (step)
	{
	case E_STEP::Start: break;
	case E_STEP::Loop:
	{
		float addsizeY = 0.1f;
		float diffsizeXZ = 0.1f;
		//- Y軸を伸ばしXZ軸を縮める
		m_size.y += addsizeY;
		m_size.x -= diffsizeXZ;
		m_size.z -= diffsizeXZ;

		if (m_size.x < 0.0f || m_size.z < 0.0f)
		{
			m_size.x = 0.0f;
			m_size.z = 0.0f;
			Set_Destory();
			SceneBase* scene = SceneController::Get_Scene();
			//- アイテムを生成
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
	case E_STEP::End: break;
	}
}
