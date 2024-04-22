/*********************************************************************
 * @file   StaminaUI.cpp
 * @brief  スタミナを表示するUI
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "StaminaUI.h"
#include "../../Player/Player.h"
#include "../../../01_System/Window/WinStartUp.h"

#include "../../../02_Component/Sprite/Sprite.h"
#include "../../../02_Component/Shader/Shader.h"

#include "../../../04_Scene/SceneBase.h"
#include "../../../04_Scene/SceneController.h"

#include "../../../01_System/Input/Input.h"

void StaminaUI::Init()
{
	Add_Component<Shader>()->Load("Assets/Shader/VS_Color.cso","Assets/Shader/PS_Texture.cso");

	m_pMeterFileName  = "Assets/Texture/UI/StaminaGage.png";
	m_pNeedleFileName = "Assets/Texture/UI/StaminaNeedle.png";

	m_pos = { 1075.0f,520.0f,0.0f };
	m_size = { 200.0f,200.0f,0.0f };


	Sprite* sp = Add_Component<Sprite>();
	sp->Init({ m_pos.x,m_pos.y},{ m_size.x,m_size.y}, m_pMeterFileName);
	m_pNeedle = Add_Component<Sprite>();
	m_pNeedle->Init({ 1160.0f,580.0f }, { 20.0f,80.0f }, m_pNeedleFileName);
}

void StaminaUI::Update(float deltatime)
{
	SceneBase* scene = SceneController::Get_Scene();
	Player* player = scene->Get_Object<Player>();
	
	std::vector<Sprite*> sprites = Get_Components<Sprite>();
	for (Sprite* sp : sprites)
	{
		if (sp->Get_FileName() == m_pNeedleFileName)
		{
			float stamina = player->Get_Stamina();
			float maxStamina = player->Get_MaxStamina();
			float minAngle = -1.25f;
			float maxAngle =  2.75f;
			float angle = minAngle + (stamina / maxStamina) * (maxAngle - minAngle);

			//- 角度の計算
			sp->Set_Rot(angle);
		}
	}	
}
