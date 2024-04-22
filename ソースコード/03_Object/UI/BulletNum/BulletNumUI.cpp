/*********************************************************************
 * @file   BulletNumUI.cpp
 * @brief  残弾数を表示するUI
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "BulletNumUI.h"

#include "../../../01_System/Window/WinStartUp.h"
#include "../../../01_System/Text/TextDraw.h"

#include "../../../02_Component/Sprite/Sprite.h"
#include "../../../02_Component/Shader/Shader.h"

#include "../../../03_Object/Weapon/WeaponBase.h"

#include "../../../04_Scene/SceneBase.h"
#include "../../../04_Scene/SceneController.h"

void BulletNumUI::Init()
{
	Add_Component<Shader>()->Load("Assets/Shader/VS_Color.cso","Assets/Shader/PS_Texture.cso");

	m_pBaseFileName   = "Assets/Texture/UI/Base.png";
	m_pCntBoxFileName = "Assets/Texture/UI/CntBox.png";
	m_pGageFileName   = "Assets/Texture/UI/Gage.png";

	//- UIのベース設定
	m_pos =  { 1100.0f,420.0f,0.0f };
	m_size = { 150.0f ,150.0f,0.0f };
	Sprite* sp = Add_Component<Sprite>();
	sp->Set_ComponentName("Base");
	sp->Init({m_pos.x,m_pos.y},{m_size.x,m_size.y}, m_pBaseFileName);
	//- UIの残弾表示部分設定
	m_pos =  { 1050.0f,470.0f,0.0f };
	m_size = { 100.0f,60.0f,0.0f };
	sp = Add_Component<Sprite>();
	sp->Set_ComponentName("CntBox");
	sp->Init({ m_pos.x,m_pos.y }, { m_size.x,m_size.y }, m_pCntBoxFileName);

	//- UIのゲージ部分設定
	Add_Component<Shader>()->Load("Assets/Shader/VS_Color.cso","Assets/Shader/PS_Gage.cso");
	m_pos = { 1160.0f,400.0f,0.0f };
	m_size = { 30.0f,115.0f,0.0f };
	sp = Add_Component<Sprite>();
	sp->Set_ComponentName("Gage");
	sp->Init({ m_pos.x,m_pos.y }, { m_size.x,m_size.y }, m_pGageFileName);
	sp->Set_Color({ 1.0f,1.0f,1.0f,1.0f });
	

	m_initSizeY = 230.0f;
}

void BulletNumUI::Update(float DeltaTime)
{
	SceneBase* scene = SceneController::Get_Scene();
	std::vector<Sprite*> sprites = Get_Components<Sprite>();
	Sprite* sp;
	for (auto& sprite : sprites)
	{
		if (sprite->Get_ComponentName() == "Gage")
		{	sp = sprite; break;	}
		if (sprite->Get_ComponentName() == "Base")
		{
			float rotSpeed = 0.15f;
			m_rot.z += DeltaTime + rotSpeed;
			sprite->Set_Rot(m_rot.z);
		}

	}
	
	if (m_pWeapon->Get_Reload())
	{
		float curTime = m_pWeapon->Get_CurReloadTime();
		float maxTime = m_pWeapon->Get_ReloadTime();
		float size = (curTime / maxTime) * m_initSizeY;
		size = (size / m_initSizeY);//0～1.0fにする
		CONSTANT_BUFFE_OBJECT obj = {};
		obj.scale = { size,size,size };
		sp->Set_bufferObject(obj);
	}
	else
	{
		CONSTANT_BUFFE_OBJECT obj = {};
		obj.scale = { 1.0f,1.0f,1.0f };
		sp->Set_bufferObject(obj);
	}
}

void BulletNumUI::Draw()
{
	//- リロード中ならリロード中の文字を表示
	if (m_pWeapon->Get_Reload())
	{
		//- リロード中の文字を表示
		std::string text = ":(";
		TextDraw::Set_FontColor(D2D1::ColorF(D2D1::ColorF::OrangeRed));
		TextDraw::Set_FontSize(30.0f);
		TextDraw::Set_FontType(2);
		TextDraw::DrawMessage(text, { 1065.0f,475.0f });
	}
	else
	{
		int curBulletNum = m_pWeapon->Get_CurBulletNum();
		std::string text = "Sample Text";

		//- 残弾数が10以下なら0埋め
		if (curBulletNum < 10){
			text = "0" + std::to_string(curBulletNum) + "/" + 
				std::to_string(m_pWeapon->Get_MaxBulletNum());
		}
		else{
			text = std::to_string(curBulletNum) + "/" + 
				std::to_string(m_pWeapon->Get_MaxBulletNum()); 
		}
		//- 残弾数を表示
		TextDraw::Set_FontColor(D2D1::ColorF(D2D1::ColorF::LightYellow));
		TextDraw::Set_FontSize(22.5f);
		TextDraw::Set_FontType(2);
		TextDraw::DrawMessage(text, { 1060.0f,480.0f });
	}
}
 