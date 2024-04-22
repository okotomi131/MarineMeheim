/*********************************************************************
 * @file   SceneTutorial.cpp
 * @brief  チュートリアル
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "SceneTutorial.h"
#include "../../01_System/Input/Input.h"
#include "../../03_Object/Enemy/TutorialEnemy/TutorialEnemy.h"
#include "../../03_Object/Obstacle/Seaweed.h"
#include "../../03_Object/UI/TutorialMessage/TutorialMessage.h"
#include "../../03_Object/UI/Button/ButtonBase.h"
#include "../../03_Object/BGM/BGM.h"

void SceneTutorial::Init()
{
	Bullet::Load();
	TutorialEnemy::Load();
	SceneStageBase::Init();
	CreatePlayer();
	CreateField();

	SceneStageBase::CREATE_INFO info;
	info.CreateNum = 70;
	info.minArea = { -200.0f,0.0f,-200.0f };
	info.maxArea = { 200.0f,0.0f,200.0f };
	info.minSize = 10.0f;
	info.maxSize = 30.0f;
	CreateNotCollObstacle<Seaweed>(info, false, true);

	//- 敵の制作
	int enemyNum = 3;
	for (int i = 0; i < enemyNum; i++)
	{
		int posNum = i - 1;
		float pos = posNum * 5.0f;
		TutorialEnemy* enemy = Add_Object<TutorialEnemy>();
		enemy->Set_SpawnPos({ pos,0.0f,0.0f });
	}

	ButtonBase* button = Add_Object<ButtonBase>(3);
	button->Load("Assets/Texture/UI/MiniNextButton.png");
	button->Set_Name("Next");
	button->Set_Size({ 100.0f,100.0f });
	button->Set_Pos({ 1000.0f,SPRITE_CENTER_POS_Y(100.0f) });
	m_pButtonList.push_back(button);
	button = Add_Object<ButtonBase>(3);
	button->Load("Assets/Texture/UI/MiniBackButton.png");
	button->Set_Name("Back");
	button->Set_Size({ 100.0f,100.0f });
	button->Set_Pos({ 200.0f,SPRITE_CENTER_POS_Y(100.0f) });
	m_pButtonList.push_back(button);


	CreateBarrier(); //ステージ制限の壁を作成
	CreateSceneUI(); //UIを作成

	Add_Object<TutorialMessage>(3);

	BGM* bgm = Add_Object<BGM>();
	bgm->Register("Stage", "Assets/Sound/BGM/Battle.wav");
	bgm->Play("Stage");
	m_Fade->FadeIn();//フェードイン
}

void SceneTutorial::Update(float deltatime)
{
	if (SceneController::Get_Pause())
	{
		DoPause(deltatime);
		return;
	}


	//- チュートリアルが終了するまでゲームの更新を止める
	if (!Get_Object<TutorialMessage>()->Get_IsEnd() && 
		m_Fade->Get_State() == Fade::E_FADE_STATE::Stop)
	{ DrawTutorial(deltatime); }
	else
	{
		SceneController::Set_BaseUpdatePause(false);
		m_clearTime += deltatime;
		CheckEndSceneFlag(deltatime);
		MoveScene();
	}
}

void SceneTutorial::DrawTutorial(float deltatime)
{
	SceneController::Set_BaseUpdatePause(true);
	Get_Object<TutorialMessage>()->Set_CurDrawMessage(m_tutorialStep);
	Get_Object<TutorialMessage>()->Update(deltatime);
	bool isEnd = Get_Object<TutorialMessage>()->Get_IsEnd();

	for (ButtonBase* button : m_pButtonList)
	{
		//- チュートリアルが終了したらボタンを非表示にする
		if (isEnd) { button->OutScreen(); continue; }
		
		button->Update(deltatime);

		if (button->IsOverlap() && Input::Get_KeyTrigger(VK_LBUTTON))
		{
			//- チュートリアルのステップを進める
			if (button->Get_Name() == "Next") { m_tutorialStep++; }
			else if (button->Get_Name() == "Back") {m_tutorialStep--;}

			if (m_tutorialStep < 0) { m_tutorialStep = 0; }
		}
	}
}
