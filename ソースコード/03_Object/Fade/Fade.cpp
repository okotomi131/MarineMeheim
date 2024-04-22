/*********************************************************************
 * @file   Fade.cpp
 * @brief  フェード
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "Fade.h"

#include "../../01_System/Window/WinStartUp.h"

#include "../../02_Component/Sprite/Sprite.h"
#include "../../02_Component/Shader/Shader.h"


void Fade::Init()
{
	Add_Component<Shader>()->Load("Assets/Shader/VS_Color.cso","Assets/Shader/PS_Color.cso");

	Sprite* sp = Add_Component<Sprite>();
	sp->Init(
		{ 0.0f,0.0f },{ (float)SCREEN_WIDTH,(float)SCREEN_HEIGHT },
		"Assets/Texture/Fade.png");

	MATERIAL mat = {};
	mat.diffuse = { 0.0f,0.0f,0.0f,1.0f };
	sp->Set_Material(mat);
	
}


void Fade::Update(float deltatime)
{
	switch (m_state)
	{
	case E_FADE_STATE::Stop: m_alpha = 0.0f;	break;
	case E_FADE_STATE::In:	
		m_alpha -= m_speed;
		if (m_alpha < 0.0f) 
		{ 
			m_alpha = 0.0f;
			m_state = E_FADE_STATE::Stop;		
		}
		break; 

	case E_FADE_STATE::Out: 
		m_alpha += m_speed; 
		if (m_alpha > 1.0f) 
		{
			m_alpha = 1.0f; 
			m_state = E_FADE_STATE::Finish;
		}
		break;

	case E_FADE_STATE::Finish: m_alpha = 1.0f; break;
	}

	MATERIAL mat;
	mat.diffuse = { 0.0f,0.0f,0.0f,m_alpha };
	Get_Component<Sprite>()->Set_Material(mat);
}

Fade::E_FADE_STATE Fade::Get_State()
{
	return m_state; 
}
