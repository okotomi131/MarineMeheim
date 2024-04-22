#include "TitleKeyTextBack.h"
#include "../../../01_System/Window/WinStartUp.h"
#include "../../../02_Component/Sprite/Sprite.h"
#include "../../../02_Component/Shader/Shader.h"

void TitleKeyTextBack::Init()
{
	Add_Component<Shader>()->Load(
		"Assets/Shader/VS_Color.cso",
		"Assets/Shader/PS_Texture.cso");

	m_size = { 600.0f,100.0f,0.0f };
	m_pos = { (float)SCREEN_WIDTH * 0.25f,490.0f,0.0f };
	Add_Component<Sprite>()->Init(
		{ m_pos.x,m_pos.y },
		{ m_size.x,m_size.y },
		"Assets/Texture/UI/PressKeyTextBack.png"
	);
}

void TitleKeyTextBack::Update(float deltatime)
{
	m_time += (deltatime * 2.0f);
	//- アルファ値を0.0f～1.0fの間のループ
	float alpha = (sin(m_time) + 1.0f);
	Get_Component<Sprite>()->Set_Color({ 1.0f,1.0f,1.0f,alpha });
}
