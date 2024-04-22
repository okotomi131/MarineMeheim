/*********************************************************************
 * @file   SceneResult.cpp
 * @brief  リザルトシーン
 *********************************************************************/

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "SceneResult.h"

#include "../../01_System/Input/Input.h"
#include "../../01_System/Window/WinStartUp.h"
#include "../../01_System/Text/TextDraw.h"
#include "../../01_System/Save/DataSave.h"

#include "../../03_Object/Image/ImageDrawer.h"
#include "../../03_Object/UI/Button/ButtonBase.h"
#include "../../03_Object/BGM/BGM.h"
#include "../../04_Scene/SceneController.h"

void SceneResult::Init()
{
	ImageDrawer* background = Add_Object<ImageDrawer>(0);
	background->Set_Name("Background");
	background->CreateImage("Assets/Texture/UI/BG.png", true);

	ButtonBase* nextButton = Add_Object<ButtonBase>();
	nextButton->Set_Name("NextButton");
	nextButton->Load("Assets/Texture/UI/NextButton.png");
	nextButton->Set_Size({ 200.0f,50.0f });
	float addPosY = 200.0f;
	nextButton->Set_Pos({ SPRITE_CENTER_POS_X(200.0f),SPRITE_CENTER_POS_Y(50.0f) + addPosY});


	BGM* bgm = Add_Object<BGM>();
	bgm->Register("Title", "Assets/Sound/BGM/Title.wav");
	bgm->Register("Wave", "Assets/Sound/BGM/Wave.wav");
	bgm->Play("Title");
	bgm->Play("Wave");

	m_Fade->FadeIn();
}

void SceneResult::CreateClearTime()
{
	int stageNum = SceneController::Get_OldState();
	stageNum -= SceneController::E_SCENE_STATE::Tutorial;
	std::string ClearTimeName = "ClearTimeStage" + std::to_string(stageNum);
	float ClearTime = DataSave::Get_Data<float>(ClearTimeName);

	m_stageNum = stageNum;
	m_clearTime = ClearTime;

	//- クリアタイムの小数点2以下まで表示
	//分秒ミリ秒に変換
	m_minute = m_clearTime / 60;
	m_second = m_clearTime - (m_minute * 60);
	m_millisecond = (m_clearTime - (m_minute * 60) - m_second) * 1000;
	//ミリ秒は2桁までにする
	m_millisecond = m_millisecond / 10;

	//表示(0埋めあり)
	m_strMinute = std::to_string(m_minute);
	m_strSecond = std::to_string(m_second);
	m_strMillisecond = std::to_string(m_millisecond);
	if (m_minute < 10) { m_strMinute = "0" + m_strMinute; }
	if (m_second < 10) { m_strSecond = "0" + m_strSecond; }
	if (m_millisecond < 10) { m_strMillisecond = "0" + m_strMillisecond; }
}

void SceneResult::Update(float deltatime)
{
	ButtonBase* nextButton = Get_Object<ButtonBase>("NextButton");


	if (m_Fade->Get_State() == Fade::E_FADE_STATE::Stop)
	{
		if (nextButton->IsOverlap() && Input::Get_KeyTrigger(VK_LBUTTON))
		{
			m_bNextScene = true;
			m_Fade->FadeOut();
		}
	}

	if (m_Fade->Get_State() == Fade::E_FADE_STATE::Finish)
	{ SceneController::Set_SceneState(SceneController::Select); }
}

void SceneResult::Draw()
{
	if (!m_bNextScene)
	{
		TextDraw::Set_FontType(2);
		TextDraw::Set_FontSize(100);
		TextDraw::Set_FontColor(D2D1::ColorF(D2D1::ColorF::DarkSlateGray));
		TextDraw::DrawMessage("クリアタイム", { 100.0f,100.0f });
		CreateClearTime();

		TextDraw::Set_FontColor(D2D1::ColorF(D2D1::ColorF::OrangeRed));
		TextDraw::DrawMessage(
			m_strMinute + ":" + m_strSecond + ":" + m_strMillisecond,
			{ 100.0f,200.0f });
	
		//- 一定時間区切りで評価を表示
		if (m_clearTime <= 120.0f)
		{
			TextDraw::Set_FontColor(D2D1::ColorF(D2D1::ColorF::Red));
			TextDraw::DrawMessage("A", { 100.0f,300.0f });
		}
		else if (m_clearTime <= 180.0f)
		{
			TextDraw::Set_FontColor(D2D1::ColorF(D2D1::ColorF::Orange));
			TextDraw::DrawMessage("B", { 100.0f,300.0f });
		}
		else if (m_clearTime <= 240.0f)
		{
			TextDraw::Set_FontColor(D2D1::ColorF(D2D1::ColorF::Blue));
			TextDraw::DrawMessage("C", { 100.0f,300.0f });
		}
		else
		{
			TextDraw::Set_FontColor(D2D1::ColorF(D2D1::ColorF::Black));
			TextDraw::DrawMessage("D", { 100.0f,300.0f });
		}
	}	
}
