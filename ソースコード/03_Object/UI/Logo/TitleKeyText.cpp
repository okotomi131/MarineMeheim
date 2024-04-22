#include "TitleKeyText.h"
#include "../../../01_System/Window/WinStartUp.h"
#include "../../../02_Component/Sprite/Sprite.h"
#include "../../../02_Component/Shader/Shader.h"
#include "../../../01_System/Input/Input.h"
#include "../../../01_System/Collison/CollisionController.h"

void TitleKeyText::Init()
{
	Add_Component<Shader>()->Load("Assets/Shader/VS_Color.cso","Assets/Shader/PS_Texture.cso");

	//m_size = { 600.0f,80.0f,0.0f };
	//m_pos = { SPRITE_CENTER_POS_X(m_size.x),500.0f,0.0f};
	m_size = { 100.0f,100.0f,0.0f };
	m_pos = { 0.0f,0.0f,0.0f };
	Add_Component<Sprite>()->Init(
		{ m_pos.x,m_pos.y },{ m_size.x,m_size.y },
		"Assets/Texture/UI/Unlock.png");

}

void TitleKeyText::Update(float deltatime)
{
	CollisionController::AABB aabb = {};
	Sprite* sp = Get_Component<Sprite>();
	DirectX::XMFLOAT2 pos = sp->Get_Pos();
	DirectX::XMFLOAT2 size = sp->Get_Size();
	aabb.min.x = pos.x;
	aabb.min.y = pos.y;
	aabb.max.x = pos.x + size.x;
	aabb.max.y = pos.y + size.y;
	POINT curPos;
	GetCursorPos(&curPos);
	ScreenToClient(GET_WIN.Get_WinhWnd(), &curPos);
	
	DirectX::XMFLOAT3 mousePos = 
	{
		static_cast<float>(curPos.x),
		static_cast<float>(curPos.y),
		0.0f
	};
	

	if (Input::Get_KeyTrigger('A'))
	{
		int a = 1;
	}
	if (CollisionController::AABBwithOverlapCursol(aabb, mousePos))
	{
		sp->Set_Color({0.5f,0.5f, 0.5f, 0.5f});
	}
	else
	{
		sp->Set_Color({ 1.0f,1.0f, 1.0f, 1.0f });
	}
	
}


