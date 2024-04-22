/*********************************************************************
 * @file   SceneTitle.cpp
 * @brief  タイトルシーン
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "SceneTitle.h"

#include "../../01_System/Input/Input.h"

#include "../../03_Object/UI/Button/ButtonBase.h"
#include "../../03_Object/Image/ImageDrawer.h"
#include "../../03_Object/BGM/BGM.h"
#include "../../04_Scene/SceneController.h"

void SceneTitle::Init()
{
	ImageDrawer* background = Add_Object<ImageDrawer>(0);
	background->Set_Name("Background");
	background->CreateImage("Assets/Texture/UI/TitleBG.png",true);

	for(int i = 0; i < 5; i++)
	{
		ImageDrawer* fish = Add_Object<ImageDrawer>(0);
		fish->Set_Name("Fish");
		fish->CreateImage("Assets/Texture/UI/Fish.png");
		fish->Set_Size({ 50.0f,30.0f });
		fish->Set_Pos({ -300.0f + (i * 70.0f),20.0f });
	}

	float size = 400.0f;
	ImageDrawer* logoBase = Add_Object<ImageDrawer>(0);
	logoBase->Set_Name("LogoBase");
	logoBase->CreateImage("Assets/Texture/UI/LogoBase.png");
	logoBase->Set_Size({ size,size });
	logoBase->Set_Pos({	SPRITE_CENTER_POS_X(size),SPRITE_CENTER_POS_Y(size) });

	size = 140.0f;
	ImageDrawer* logo = Add_Object<ImageDrawer>(0);
	logo->Set_Name("Logo");
	logo->CreateImage("Assets/Texture/UI/Logo.png");
	logo->Set_Size({ size,size });
	logo->Set_Pos({ SPRITE_CENTER_POS_X(size),SPRITE_CENTER_POS_Y(size) });


	ButtonBase* startButton = Add_Object<ButtonBase>();
	startButton->Set_Name("StartButton");
	//- ステージ1をクリア済なら続きからボタンに差し替え
	if (DataSave::Get_Data<int>("ClearStageNum") >= 1)
	{	startButton->Load("Assets/Texture/UI/StartSuccess.png");	}
	else
	{	startButton->Load("Assets/Texture/UI/StartFirst.png");	}
	startButton->Set_Size({200.0f,50.0f});
	startButton->Set_Pos({ SPRITE_CENTER_POS_X(200.0f),560.0f});

	ButtonBase* exitButton = Add_Object<ButtonBase>();
	exitButton->Set_Name("ExitButton");
	exitButton->Load("Assets/Texture/UI/EndButton.png");
	exitButton->Set_Size({ 200.0f,50.0f });
	exitButton->Set_Pos({ SPRITE_CENTER_POS_X(200.0f),620.0f });

	BGM* bgm = Add_Object<BGM>();
	bgm->Register("Title", "Assets/Sound/BGM/Title.wav");
	bgm->Register("Wave", "Assets/Sound/BGM/Wave.wav");
	bgm->Play("Title");
	bgm->Play("Wave");


	m_Fade->FadeIn();
}


void SceneTitle::Update(float deltatime)
{
	//- ロゴ
	ImageDrawer* logoBase = Get_Object<ImageDrawer>("LogoBase");
	float rot = logoBase->Get_Rot().z;
	rot += deltatime * 0.5f;
	logoBase->Set_Rot({ logoBase->Get_Rot().x,logoBase->Get_Rot().y,rot });
	logoBase->Set_RotZ(logoBase->Get_Rot().z);

	//- 魚を動かす
	float waveHeight = 0.3f;
	float waveSpeed = 0.01f;
	float defaultY = 30.0f;
	float MoveSpeed = 3.5f;
	DirectX::XMFLOAT2 pos;
	std::vector<ImageDrawer*> fishList = Get_Objects<ImageDrawer>("Fish");
	for (ImageDrawer* fish : fishList)
	{
		pos = fish->Get_Component<Sprite>()->Get_Pos();
		pos.x -= MoveSpeed;
		pos.y += sinf(pos.x * waveSpeed) * waveHeight;
		fish->Set_Pos(pos);

		float screenRange = 100.0f;
		if (pos.x < -(SCREEN_WIDTH + screenRange))
		{
			pos.x = SCREEN_WIDTH + screenRange;
			fish->Set_Pos(pos);
		}
	}
	
	//- 次のシーンへ
	MoveScene();
}

void SceneTitle::MoveScene()
{

	//- ボタン
	ButtonBase* startButton = Get_Object<ButtonBase>("StartButton");
	ButtonBase* exitButton = Get_Object<ButtonBase>("ExitButton");

	if (m_Fade->Get_State() == Fade::E_FADE_STATE::Stop)
	{
		//- 開始
		if (startButton->IsOverlap())
		{
			//- 一回だけ鳴らす
			if (!startButton->Get_OnceSound())
			{
				startButton->Play_Sound("select");
				startButton->Set_OnceSound(true);
				exitButton->Set_OnceSound(false);
			}

			if (Input::Get_KeyTrigger(VK_LBUTTON))
			{
				startButton->Play_Sound("push");
				m_Fade->FadeOut();
			}
		}
		//- 終了
		else if (exitButton->IsOverlap())
		{
			//- 一回だけ鳴らす
			if (!exitButton->Get_OnceSound())
			{
				exitButton->Play_Sound("select");
				exitButton->Set_OnceSound(true);
				startButton->Set_OnceSound(false);
			}
			if (Input::Get_KeyTrigger(VK_LBUTTON))
			{
				exitButton->Play_Sound("push");
				PostQuitMessage(0);
			}
		}
	}

	if (m_Fade->Get_State() == Fade::E_FADE_STATE::Finish)
	{
		SceneController::Set_SceneState(SceneController::Select);
	}

	if (Input::Get_KeyPress(VK_F1) && Input::Get_KeyTrigger(VK_DOWN))
	{
		SceneController::Set_SceneState(SceneController::Stage1);
	}
}
