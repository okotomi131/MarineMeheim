/*********************************************************************
 * @file   Crosshair.cpp
 * @brief  �N���X�w�A
 *********************************************************************/

/*
==================================================

�C���N���[�h

==================================================
*/
#include "Crosshair.h"
#include "../../../01_System/Window/WinStartUp.h"
#include "../../../02_Component/Sprite/Sprite.h"
#include "../../../02_Component/Shader/Shader.h"

void Crosshair::Init()
{
	m_size = { 50.0f,50.0f,0.0f };
	m_pos = 
	{
		(SCREEN_WIDTH / 2.0f)  - (m_size.x / 2.0f),	//��_������Ȃ̂Œ��S�ɂ��邽�߂ɃT�C�Y�̔���������
		(SCREEN_HEIGHT / 2.0f) - (m_size.y / 2.0f),
		0.0f
	};

	Add_Component<Shader>()->Load("Assets/Shader/VS_Color.cso","Assets/Shader/PS_Texture.cso");
	Add_Component<Sprite>()->Init({m_pos.x  ,m_pos.y},{m_size.x ,m_size.y},"Assets/Texture/Crosshair.png");
}
