/*********************************************************************
 * @file   GameOverPause.cpp
 * @brief  ゲームオーバー時のポーズ処理
 *********************************************************************/
/*
==================================================

インクルード

==================================================
*/
#include "GameOverPause.h"
#include "../Button/ButtonBase.h"
#include "../../../01_System/Input/Input.h"

void GameOverPause::Init()
{
	DirectX::XMFLOAT2 size = { 559.0f,300.0f };
	float subPosY = 200.0f;
	float addPosY = 120.0f;
	m_PausePos =
	{
		SPRITE_CENTER_POS_X(size.x),
		SPRITE_CENTER_POS_Y(size.y) - subPosY
	};
	//- ポーズ画像
	Sprite* sp = Add_Component<Sprite>();
	sp->Init({ 9999.9f,9999.9f }, size, "Assets/Texture/UI/GameOver.png");

	ButtonBase* button = Add_Obj<ButtonBase>();
	button->Load("Assets/Texture/UI/NewStart.png");
	button->Set_Name("NewStart");
	button->Set_Size({ 200.0f,100.0f });
	button->Set_Pos({ 9999.9f,9999.9f });
	m_pButtonList.push_back(button);
	m_buttonPos.push_back({ SPRITE_CENTER_POS_X(200.0f),SPRITE_CENTER_POS_Y(100.0f)});

	button = Add_Obj<ButtonBase>();
	button->Load("Assets/Texture/UI/ReTreatButton.png");
	button->Set_Name("ReTreat");
	button->Set_Size({ 200.0f,100.0f });
	button->Set_Pos({ 9999.9f,9999.9f });
	m_pButtonList.push_back(button);
	m_buttonPos.push_back({ SPRITE_CENTER_POS_X(200.0f),SPRITE_CENTER_POS_Y(100.0f) + addPosY });
}

void GameOverPause::Update(float deltatime)
{
	for (auto& button : m_pButtonList)
	{
		button->Update(deltatime);
		if (button->IsOverlap() && Input::Get_KeyTrigger(VK_LBUTTON))
		{
			//- シーンをはじめからやり直す
			if (button->Get_Name() == "NewStart")
			{
				AllFlagReset();
				m_bNewStart = true;
				break;

			}
			//- セレクトシーンに戻る
			else if (button->Get_Name() == "ReTreat")
			{
				AllFlagReset();
				m_bReTreat = true;
				break;
			}
		}
	}
}
