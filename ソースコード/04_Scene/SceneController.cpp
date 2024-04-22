/*********************************************************************
 * @file   SceneController.cpp
 * @brief  シーン管理を行う
 *********************************************************************/

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "SceneController.h"
#include "Title/SceneTitle.h"
#include "Select/SceneStageSelect.h"
#include "Stage/SceneTutorial.h"
#include "Stage/SceneStage1.h"
#include "Stage/SceneStage2.h"
#include "Stage/SceneStage3.h"
#include "Stage/SceneStage4.h"
#include "Stage/SceneStage5.h"
#include "Result/SceneResult.h"

#include "../01_System/DirectX/DirectXRenderer.h"
#include "../01_System/Input/Input.h"
#include "../01_System/Save/DataSave.h"
#include "../01_System/Collison/CollisionController.h"
#include "../01_System/Text/TextDraw.h"
#include "../01_System/Window/WinStartUp.h"

#include "../02_Component/Sound/Sound.h"

SceneBase* SceneController::m_pScene = {};
bool SceneController::m_bPause = false;
bool SceneController::m_bBaseUpdate = false;
bool SceneController::m_bOncePauseUpdate = false;


SceneController::E_SCENE_STATE SceneController::m_curState  = SceneController::E_SCENE_STATE::Title;
SceneController::E_SCENE_STATE SceneController::m_nextState = SceneController::E_SCENE_STATE::None;
SceneController::E_SCENE_STATE SceneController::m_oldState  = SceneController::E_SCENE_STATE::None;

static const float PAUSE_FONT_SIZE = 100.0f;
static const float PAUSE_FONT_POS_ADD_X = 60.0f;
static const float PAUSE_FONT_POS_ADD_Y = 200.0f;


void SceneController::Init()
{
	DirectXRenderer::Init();
	Sound::InitMaster();
	Input::Init();
	TextDraw::Init();
	DataSave::Load();
	Set_Scene<SceneTitle>();
}

void SceneController::Uninit()
{
	m_pScene->UninitBase();
	DataSave::Save();
	TextDraw::Uninit();
	Delete_and_Null<>(m_pScene, "m_pScene");
	Sound::UninitMaster();
	DirectXRenderer::Uninit();
}

void SceneController::Update(float deltatime)
{
	//- ステート切り替え予約がされているか
	if (m_nextState != E_SCENE_STATE::None){ ChangeScene();	}
	
	//- 更新処理
	Input::Update();
	
	//- ポーズの切り替え
	if (m_curState != E_SCENE_STATE::Title  && m_curState != E_SCENE_STATE::Result &&
		m_curState != E_SCENE_STATE::Select)
	{
		if(Input::Get_KeyTrigger(VK_ESCAPE)) 
		{ 
			m_bPause = !m_bPause;	
			m_bOncePauseUpdate = true;
		}
	}

	//- ゲームシーンのみ止める場合
	if (m_bBaseUpdate || m_bPause)
	{
		m_pScene->Update(deltatime);
	}
	//- 通常
	else if (!m_bPause)
	{
		//- シーンがシーンベースを基底クラスとしているか
		SceneStageBase* stageScene = dynamic_cast<SceneStageBase*>(m_pScene);
		//- 一度だけポーズを画面外に出すために更新
		if (stageScene && m_bOncePauseUpdate)
		{	
			m_bOncePauseUpdate = false;
			stageScene->UnPause(deltatime);
		}

		if(m_curState != E_SCENE_STATE::Title && m_curState != E_SCENE_STATE::Result && m_curState != E_SCENE_STATE::Select)
		{	CollisionController::Update(deltatime);	}
		m_pScene->UpdateBase(deltatime);
	}



/*
	デバック用シーン切り替え
*/

	if (Input::Get_KeyPress(VK_F3))
	{
		if (Input::Get_KeyTrigger('1'))
		{
			Set_SceneState(E_SCENE_STATE::Stage1);
		}
		else if (Input::Get_KeyTrigger('2'))
		{
			Set_SceneState(E_SCENE_STATE::Stage2);
		}
		else if (Input::Get_KeyTrigger('3'))
		{
			Set_SceneState(E_SCENE_STATE::Stage3);
		}
		else if (Input::Get_KeyTrigger('4'))
		{
			Set_SceneState(E_SCENE_STATE::Stage4);
		}
		else if (Input::Get_KeyTrigger('5'))
		{
			Set_SceneState(E_SCENE_STATE::Stage5);
		}
		else if (Input::Get_KeyTrigger('6'))
		{
			Set_SceneState(E_SCENE_STATE::Tutorial);
		}
		else if (Input::Get_KeyTrigger('0'))
		{
			Set_SceneState(E_SCENE_STATE::Title);
		}
		else if (Input::Get_KeyTrigger('9'))
		{
			Set_SceneState(E_SCENE_STATE::Select);
		}
		else if (Input::Get_KeyTrigger('8'))
		{
			Set_SceneState(E_SCENE_STATE::Result);
		}
	}
}

void SceneController::Draw()
{
	m_pScene->DrawBase();
}

void SceneController::Set_SceneState(E_SCENE_STATE state)
{
	if (m_nextState != E_SCENE_STATE::None) { return; }
	m_nextState = state;
}

void SceneController::ChangeScene()
{
	//- 予約されているシーンに変更
	switch (m_nextState)
	{
	case SceneController::Title		:Set_Scene<SceneTitle>();		break;
	case SceneController::Select	:Set_Scene<SceneStageSelect>();	break;
	case SceneController::Tutorial	:Set_Scene<SceneTutorial>();	break;
	case SceneController::Stage1	:Set_Scene<SceneStage1>();		break;
	case SceneController::Stage2	:Set_Scene<SceneStage2>();		break;
	case SceneController::Stage3	:Set_Scene<SceneStage3>();		break;
	case SceneController::Stage4	:Set_Scene<SceneStage4>();		break;
	case SceneController::Stage5	:Set_Scene<SceneStage5>();		break;
	case SceneController::Result	:Set_Scene<SceneResult>();		break;
	}

	//- ステート状態更新
	m_oldState = m_curState;
	m_curState = m_nextState;
	m_nextState = E_SCENE_STATE::None;
	
}




