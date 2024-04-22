/*********************************************************************
 * @file   Pause.cpp
 * @brief  ポーズ処理
 *********************************************************************/

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "Pause.h"
#include "../Button/ButtonBase.h"
#include "../../../01_System/Input/Input.h"

void Pause::Init()
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
	sp->Init({9999.9f,9999.9f}, size, "Assets/Texture/UI/PAUSE.png");

	//- 再開ボタン
	ButtonBase* button = Add_Obj<ButtonBase>();
	button->Load("Assets/Texture/UI/ReStartButton.png");
	button->Set_Name("ReStart");
	button->Set_Size({ 200.0f,100.0f });
	button->Set_Pos({9999.9f,9999.9f});
	m_pButtonList.push_back(button);
	m_buttonPos.push_back({ SPRITE_CENTER_POS_X(200.0f),SPRITE_CENTER_POS_Y(100.0f) });

	button = Add_Obj<ButtonBase>();
	button->Load("Assets/Texture/UI/NewStart.png");
	button->Set_Name("NewStart");
	button->Set_Size({ 200.0f,100.0f });
	button->Set_Pos({ 9999.9f,9999.9f });
	m_pButtonList.push_back(button);
	m_buttonPos.push_back({ SPRITE_CENTER_POS_X(200.0f),SPRITE_CENTER_POS_Y(100.0f) + addPosY });

	button = Add_Obj<ButtonBase>();
	button->Load("Assets/Texture/UI/ReTreatButton.png");
	button->Set_Name("ReTreat");
	button->Set_Size({ 200.0f,100.0f });
	button->Set_Pos({ 9999.9f,9999.9f });
	m_pButtonList.push_back(button);
	m_buttonPos.push_back({ SPRITE_CENTER_POS_X(200.0f),SPRITE_CENTER_POS_Y(100.0f) + (addPosY * 2.0f) });
}

void Pause::Update(float deltatime)
{
	for (auto& button : m_pButtonList)
	{
		button->Update(deltatime);
		if (button->IsOverlap() && Input::Get_KeyTrigger(VK_LBUTTON))
		{
			//- 何もせずにそのまま進行させる
			if (button->Get_Name() == "ReStart")
			{
				AllFlagReset();
				m_bRestart = true;
				break; 
			}
			//- シーンをはじめからやり直す
			else if (button->Get_Name() == "NewStart")
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

void Pause::DrawPause()
{
	//- ポーズの表示を画面内に移動
	Get_Component<Sprite>()->Set_Pos(m_PausePos);
	for(int i = 0; i < m_pButtonList.size(); i++)
	{	m_pButtonList[i]->Set_Pos(m_buttonPos[i]); }
}

void Pause::UnDrawPause()
{
	//- ポーズの表示を画面外に移動
	Get_Component<Sprite>()->Set_Pos({9999.9f,9999.9f});
	for (auto& button : m_pButtonList)
	{	button->Set_Pos({ 9999.9f,9999.9f }); }
}
