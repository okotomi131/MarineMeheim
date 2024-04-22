/*********************************************************************
 * @file   SceneStage4.cpp
 * @brief  �X�e�[�W4
 *********************************************************************/

/*
==================================================

�C���N���[�h

==================================================
*/
#include "SceneStage4.h"

#include "../../03_Object/Enemy/Scorpionfish/EnemyScorpionFish.h"
#include "../../03_Object/Enemy/GlobeFish/GlobeFish.h"
#include "../../03_Object/Enemy/Clownfish/Clownfish.h"
#include "../../03_Object/Enemy/Spawner/EnemySpawner.h"

#include "../../03_Object/Obstacle/Obstacle.h"
#include "../../03_Object/Obstacle/Seaweed.h"
#include "../../03_Object/Obstacle/Barrier.h"

#include "../../03_Object/BGM/BGM.h"

void SceneStage4::Init()
{
	Bullet::Load();
	EnemyScorpionFish::Load();
	GlobeFish::Load();
	SceneStageBase::Init();
	CreatePlayer();
	CreateField();

	//- ��Q�����쐬
	SceneStageBase::CREATE_INFO info;
	//- �X�e�[�W�̉E�O���̏�Q��
	info.CreateNum = 5;
	info.minArea = { 5.0f,0.0f,-15.0f };
	info.maxArea = { 200.0f,0.0f,200.0f };
	info.minSize = 3.0f;
	info.maxSize = 4.0f;
	CreateCollisionObstacle(info, "Assets/Model/Object/Rock.obj");
	//- �X�e�[�W�̍��O���̏�Q��
	info.minArea = { -200.0f,0.0f,-15.0f };
	info.maxArea = { -5.0f  ,0.0f,200.0f };
	CreateCollisionObstacle(info, "Assets/Model/Object/Rock.obj");
	//- �X�e�[�W�̉E��둤�̏�Q��
	info.minArea = { 5.0f,0.0f,-200.0f };
	info.maxArea = { 200.0f,0.0f,15.0f };
	CreateCollisionObstacle(info, "Assets/Model/Object/Rock.obj");
	//- �X�e�[�W�̍���둤�̏�Q��
	info.minArea = { -200.0f,0.0f,-200.0f };
	info.maxArea = { -5.0f  ,0.0f,15.0f };
	CreateCollisionObstacle(info, "Assets/Model/Object/Rock.obj");

	info.CreateNum = 70;
	info.minArea = { -200.0f,0.0f,-200.0f };
	info.maxArea = { 200.0f,0.0f,200.0f };
	info.minSize = 10.0f;
	info.maxSize = 30.0f;
	CreateNotCollObstacle<Seaweed>(info, false, true);

	//- �G���쐬
	info.CreateNum = 20;
	info.minArea = { -20.0f,0.0f,40.0f };
	info.maxArea = { 20.0f,0.0f,60.0f };
	CreateEnemy<Clownfish>(info);

	EnemySpawner* spawner = Add_Object<EnemySpawner>();
	spawner->Set_SpawnPos({ 30.0f,40.0f,50.0f });
	spawner->Set_SpawnType(EnemySpawner::E_ENEMY_TYPE::GlobeFish);

	spawner = Add_Object<EnemySpawner>();
	spawner->Set_SpawnPos({ -30.0f,40.0f,50.0f });
	spawner->Set_SpawnType(EnemySpawner::E_ENEMY_TYPE::GlobeFish);

	CreateBarrier(); //�X�e�[�W�����̕ǂ��쐬
	CreateSceneUI(); //UI���쐬
	m_Fade->FadeIn();//�t�F�[�h�C��
	BGM* bgm = Add_Object<BGM>();
	bgm->Register("Stage", "Assets/Sound/BGM/Battle.wav");
	bgm->Play("Stage");
}

void SceneStage4::Update(float deltatime)
{
	if (SceneController::Get_Pause() && !m_bPlayerDead)
	{
		DoPause(deltatime);
		return;
	}
	else if (m_bPlayerDead)
	{
		GameOver(deltatime);
		return;
	}

	m_clearTime += deltatime;
	CheckEndSceneFlag(deltatime);
	MoveScene();
}
