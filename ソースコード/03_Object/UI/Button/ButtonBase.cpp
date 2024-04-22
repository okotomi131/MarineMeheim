/*********************************************************************
 * @file   ButtonBase.cpp
 * @brief  ボタンを作成する
 *********************************************************************/
/*
==================================================

インクルード

==================================================
*/
#include "ButtonBase.h"
#include "../../../01_System/Window/WinStartUp.h"
#include "../../../02_Component/Sprite/Sprite.h"
#include "../../../02_Component/Shader/Shader.h"
#include "../../../01_System/Input/Input.h"
#include "../../../01_System/Collison/CollisionController.h"

void ButtonBase::Load(const char* path)
{
	DirectX::XMFLOAT2 pos = { 100.0f,100.0f };
	DirectX::XMFLOAT2 size = { 100.0f,100.0f };
	m_pSprite = Add_Component<Sprite>();
	m_pSprite->Init(pos, size, path);
}

void ButtonBase::Init()
{
	Add_Component<Shader>()->Load("Assets/Shader/VS_Color.cso", "Assets/Shader/PS_Texture.cso");

	Add_Sound("Assets/Sound/SE/UI/PushButton2.wav", "push");
	Add_Sound("Assets/Sound/SE/UI/PushButton.wav", "select");
}

void ButtonBase::Update(float deltatime)
{
	if (m_bOverlap)
	{
		Sprite* sp = Get_Component<Sprite>();
		sp->Set_Color({ 1.0f,0.5f,0.0f,1.0f });
	}
	else
	{
		Sprite* sp = Get_Component<Sprite>();
		sp->Set_Color({ 1.0f,1.0f,1.0f,1.0f });
	}
}

bool ButtonBase::IsOverlap(bool force)
{
	//- 強制的に選択状態とする
	if (force) 
	{
		m_bOverlap = true;
		return m_bOverlap;
	}

	//- カーソルが自分の範囲内にあるか
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
		{ static_cast<float>(curPos.x),static_cast<float>(curPos.y),0.0f };

	m_bOverlap = CollisionController::AABBwithOverlapCursol(aabb, mousePos);

	return m_bOverlap;
}
