/*********************************************************************
 * @file   SceneStage3.cpp
 * @brief  ステージ3
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "SceneStage3.h"

#include "../../03_Object/Enemy/Scorpionfish/EnemyScorpionFish.h"
#include "../../03_Object/Enemy/GlobeFish/GlobeFish.h"
#include "../../03_Object/Enemy/Clownfish/Clownfish.h"
#include "../../03_Object/Enemy/Spawner/EnemySpawner.h"

#include "../../03_Object/Obstacle/Obstacle.h"
#include "../../03_Object/Obstacle/Seaweed.h"
#include "../../03_Object/Obstacle/Barrier.h"

#include "../../03_Object/BGM/BGM.h"

void SceneStage3::Init()
{
	Bullet::Load();
	EnemyScorpionFish::Load();
	GlobeFish::Load();
	SceneStageBase::Init();
	CreatePlayer();
	CreateField();

	//- 障害物を作成
	SceneStageBase::CREATE_INFO info;
	//- ステージの右前側の障害物
	info.CreateNum = 5;
	info.minArea = { 5.0f,0.0f,-15.0f };
	info.maxArea = { 200.0f,0.0f,200.0f };
	info.minSize = 3.0f;
	info.maxSize = 4.0f;
	CreateCollisionObstacle(info, "Assets/Model/Object/Rock.obj");
	//- ステージの左前側の障害物
	info.minArea = { -200.0f,0.0f,-15.0f };
	info.maxArea = { -5.0f  ,0.0f,200.0f };
	CreateCollisionObstacle(info, "Assets/Model/Object/Rock.obj");
	//- ステージの右後ろ側の障害物
	info.minArea = { 5.0f,0.0f,-200.0f };
	info.maxArea = { 200.0f,0.0f,15.0f };
	CreateCollisionObstacle(info, "Assets/Model/Object/Rock.obj");
	//- ステージの左後ろ側の障害物
	info.minArea = { -200.0f,0.0f,-200.0f };
	info.maxArea = { -5.0f  ,0.0f,15.0f };
	CreateCollisionObstacle(info, "Assets/Model/Object/Rock.obj");

	info.CreateNum = 70;
	info.minArea = { -200.0f,0.0f,-200.0f };
	info.maxArea = { 200.0f,0.0f,200.0f };
	info.minSize = 10.0f;
	info.maxSize = 30.0f;
	CreateNotCollObstacle<Seaweed>(info, false, true);

	//- 敵を作成
	info.CreateNum = 3;
	info.minArea = { -10.0f,0.0f,40.0f };
	info.maxArea = { 10.0f,0.0f,60.0f };
	CreateEnemy<GlobeFish>(info);

	info.CreateNum = 3;
	info.minArea = { -10.0f,0.0f,50.0f };
	info.maxArea = {  10.0f,0.0f,60.0f };
	CreateEnemy<EnemyScorpionFish>(info);

	EnemySpawner* spawner = Add_Object<EnemySpawner>();
	spawner->Set_SpawnPos({ 0.0f,40.0f,30.0f });
	spawner->Set_SpawnType(EnemySpawner::E_ENEMY_TYPE::ScorpionFish);
	
	CreateBarrier(); //ステージ制限の壁を作成
	CreateSceneUI(); //UIを作成
	m_Fade->FadeIn();//フェードイン
	BGM* bgm = Add_Object<BGM>();
	bgm->Register("Stage", "Assets/Sound/BGM/Battle.wav");
	bgm->Play("Stage");
}

void SceneStage3::Update(float deltatime)
{
	if (SceneController::Get_Pause())
	{
		DoPause(deltatime);
		return;
	}

	m_clearTime += deltatime;
	CheckEndSceneFlag(deltatime);
	MoveScene();
}
