/*********************************************************************
 * @file   RemainEnemy.cpp
 * @brief  敵の残数を表示するUIクラス
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "RemainEnemy.h"

#include "../../../01_System/Window/WinStartUp.h"
#include "../../../01_System/Text/TextDraw.h"

#include "../../../02_Component/Sprite/Sprite.h"
#include "../../../02_Component/Shader/Shader.h"

#include "../../../04_Scene/SceneBase.h"
#include "../../../04_Scene/SceneController.h"

#include "../../Enemy/EnemyBase.h"

void RemainEnemy::Init()
{
	Add_Component<Shader>()->Load("Assets/Shader/VS_Color.cso","Assets/Shader/PS_Texture.cso");
	m_backGroundFileName = "Assets/Texture/UI/CountEnemy.png";

	m_size = { 270.0f,270.0f,0.0f };
	m_CenterPos =
	{
		SCREEN_WIDTH  * 0.5f - m_size.x * 0.5f,
		SCREEN_HEIGHT * 0.5f - m_size.y * 0.5f
	};

	m_pos = { START_ANIME_FINISH_POS_X,START_ANIME_FINISH_POS_Y,0.0f };

	Sprite* sp = Add_Component<Sprite>();
	sp->Init({ m_pos.x ,m_pos.y },{ m_size.x,m_size.y},m_backGroundFileName);
	m_initPos = { m_pos.x,m_pos.y };
}

void RemainEnemy::Update(float deltatime)
{
	SceneBase* scene = SceneController::Get_Scene();
	std::vector<EnemyBase*> enemys = scene->Get_BaseObjects<EnemyBase>();
	m_curEnemyNum = static_cast<int>(enemys.size());

	m_sp = Get_Component<Sprite>();

	m_rot.z += deltatime + m_rotSpeed;
	m_sp->Set_Rot(m_rot.z);

}

void RemainEnemy::Draw()
{
	float AddPosX = 80.0f;
	float AddPosY = 80.0f;

	SceneBase* scene = SceneController::Get_Scene();
	TextDraw::Set_FontSize(70.0f);
	TextDraw::Set_FontColor(D2D1::ColorF(D2D1::ColorF::OrangeRed));
	TextDraw::Set_FontType(2);
	if (m_curEnemyNum < 10)
	{
		std::string text = "0" + std::to_string(m_curEnemyNum);
		TextDraw::DrawMessage(text,{ m_pos.x + AddPosX,m_pos.y + AddPosY });
	}
	else
	{
		std::string text = std::to_string(m_curEnemyNum);
		TextDraw::DrawMessage(text, { m_pos.x + AddPosX,m_pos.y + AddPosY });
	}

	AddPosX = 110.0f;
	AddPosY = 170.0f;
	TextDraw::Set_FontSize(25.0f);
	TextDraw::Set_FontColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));
	TextDraw::Set_FontType(2);
	TextDraw::DrawMessage("敵残り",{ m_pos.x + AddPosX,m_pos.y + AddPosY });
}

void RemainEnemy::StartAnime(float deltatime)
{
	m_curStartAnimeTime += deltatime;
	if (m_curStartAnimeTime > MAX_START_ANIME_TIME)
	{	
		return;	
	}
	else
	{
		float t = m_curStartAnimeTime / MAX_START_ANIME_TIME;

		DirectX::XMFLOAT2 startPos = m_initPos;
		DirectX::XMFLOAT2 endPos = { START_ANIME_FINISH_POS_X, START_ANIME_FINISH_POS_Y };
		
		m_pos.x = startPos.x + t * (endPos.x - startPos.x);
		m_pos.y = startPos.y + t * (endPos.y - startPos.y);

		m_sp->Set_Pos({ m_pos.x, m_pos.y });
	}
	
}
