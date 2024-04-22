/*********************************************************************
 * @file   PlayerHPBar.cpp
 * @brief  プレイヤーの現在のHPを表示するUI
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "PlayerHPBar.h"
#include "../Player/Player.h"

#include "../../01_System/Window/WinStartUp.h"

#include "../../02_Component/Sprite/Sprite.h"
#include "../../02_Component/Shader/Shader.h"

#include "../../04_Scene/SceneBase.h"
#include "../../04_Scene/SceneController.h"

const static float HP_BAR_SIZE = 580.0f;
const static float HP_BAR_YELLOW = (HP_BAR_SIZE / 2.0f);
const static float HP_BAR_RED	 = (HP_BAR_SIZE / 4.0f);

void PlayerHPBar::Init()
{
	Add_Component<Shader>()->Load("Assets/Shader/VS_Color.cso","Assets/Shader/PS_Texture.cso");


	m_pos = { 0.0f,0.0f,0.0f };
	m_size = { 600.0f,70.0f,0.0f };
	m_maxHP = DataSave::Get_Data<float>("PlayerHP");
	const char* filename = "Assets/Texture/UI/HPBarBase.png";
	Sprite* sp = Add_Component<Sprite>();
	sp->Set_ComponentName("Base");
	sp->Init({m_pos.x,m_pos.y},{m_size.x,m_size.y}, filename);


	m_pos = { 10.0f,10.0f,0.0f };
	m_size = { HP_BAR_SIZE,15.0f,0.0f };
	m_initSize = { m_size.x,m_size.y };
	filename = "Assets/Texture/UI/HPBar.png";
	sp = Add_Component<Sprite>();
	sp->Set_ComponentName("HP");
	sp->Init({ m_pos.x,m_pos.y }, { m_size.x,m_size.y }, filename);

}

void PlayerHPBar::Update(float deltatime)
{
	MoveHPBar();

	//- HPバーのサイズが半分以下なら黄色
	Sprite* sp;
	std::vector<Sprite*> sps = Get_Components<Sprite>();
	for (auto& sprite : sps){
		if (sprite->Get_ComponentName() == "HP"){	sp = sprite;	break;	}
	}

	if      (m_size.x > HP_BAR_YELLOW)  {	sp->Set_Color({ 0.0f,1.0f,0.0f,1.0f }); }
	else if (m_size.x >= HP_BAR_RED)    {	sp->Set_Color({ 1.0f,1.0f,0.0f,1.0f });	}
	else 								{	sp->Set_Color({ 1.0f,0.0f,0.0f,1.0f });	}
}

void PlayerHPBar::Draw()
{
	SceneBase* scene = SceneController::Get_Scene();
	Player* player = scene->Get_Object<Player>();
	float	curHP = player->Get_Component<HPBase>()->Get_HpData().curHp;

	std::string HP = std::to_string((int)curHP) + "/" + std::to_string((int)m_maxHP);

	float addPosY = 10.0f;
	DirectX::XMFLOAT2 pos = { m_pos.x, m_pos.y + addPosY };
	TextDraw::Set_FontColor(D2D1::ColorF(D2D1::ColorF::LightYellow));
	TextDraw::Set_FontSize(30.0f);
	TextDraw::Set_FontType(2);
	TextDraw::DrawMessage(HP,pos);
}

void PlayerHPBar::MoveHPBar()
{
	Sprite* sp;
	std::vector<Sprite*> sps = Get_Components<Sprite>();
	for (auto& sprite : sps) {
		if (sprite->Get_ComponentName() == "HP") { sp = sprite;	break; }
	}

	SceneBase*  scene  = SceneController::Get_Scene();
	Player*		player = scene->Get_Object<Player>();
	float		curHP  = player->Get_Component<HPBase>()->Get_HpData().curHp;

	m_size.x = (curHP / m_maxHP) * m_initSize.x;
	sp->Set_Size({m_size.x,m_size.y});

}
