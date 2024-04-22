/*********************************************************************
* @file   SceneStage1.cpp
* @brief  �X�e�[�W1
*********************************************************************/

/*
===================================================================

�C���N���[�h

===================================================================
*/
#include "SceneStage2.h"

#include "../../03_Object/Enemy/Scorpionfish/EnemyScorpionFish.h"
#include "../../03_Object/Enemy/GlobeFish/GlobeFish.h"
#include "../../03_Object/Enemy/Clownfish/Clownfish.h"

#include "../../03_Object/Obstacle/Obstacle.h"
#include "../../03_Object/Obstacle/Seaweed.h"
#include "../../03_Object/Obstacle/Barrier.h"

#include "../../03_Object/BGM/BGM.h"

void SceneStage2::Init()
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
	info.CreateNum = 3;
	info.minArea = { -20.0f,0.0f,50.0f };
	info.maxArea = { 20.0f,0.0f,100.0f };
	CreateEnemy<GlobeFish>(info);

	info.CreateNum = 10;
	info.minArea = { -20.0f,0.0f,-100.0f };
	info.maxArea = { 20.0f,0.0f,-50.0f };
	CreateEnemy<EnemyScorpionFish>(info);


	CreateBarrier(); //�X�e�[�W�����̕ǂ��쐬
	CreateSceneUI(); //UI���쐬
	m_Fade->FadeIn();//�t�F�[�h�C��
	BGM* bgm = Add_Object<BGM>();
	bgm->Register("Stage", "Assets/Sound/BGM/Battle.wav");
	bgm->Play("Stage");

}

void SceneStage2::Update(float deltatime)
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
