/*********************************************************************
 * @file   Item_Heal.cpp
 * @brief  回復アイテム
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "Item_Heal.h"
#include "../Collider/Collider.h"

#include "../../02_Component/Shader/Shader.h"
#include "../../02_Component/Model/Model.h"
#include "../../02_Component/Sound/Sound.h"

#include "../../04_Scene/SceneController.h"
#include "../../04_Scene/SceneBase.h"

void Item_Heal::Init()
{
	Collider* coll = Add_Obj<Collider>();
	coll->Set_Tag("ItemHeal");
	m_size = { 0.5f,0.5f,0.5f };
	coll->Set_WorldMatrix(Get_WorldMatrix());
	coll->Set_wSize({2.5f,2.5f,2.5f});
	coll->Set_Pos({ 0.0f, 3.0f, 0.0f });

	Add_Component<Shader>()->Load(
		"Assets/Shader/VS_Object.cso",
		"Assets/Shader/PS_Light.cso");
	Add_Component<Model>()->Load("Assets/Model/Item/ItemHeal.obj");
}

void Item_Heal::Update(float deltatime)
{
	Get_Obj<Collider>()->Set_WorldMatrix(Get_WorldMatrix());
	MATERIAL mat = {};
	mat.diffuse = { 1.0f,1.0f,1.0f,1.0f };
	mat.ambient = { 1.0f,1.0f,1.0f,1.0f };
	mat.specular = { 1.0f,1.0f,1.0f,1.0f };
	DirectXRenderer::Write_Buffer<MATERIAL>("material", mat);

	ItemBase::Update(deltatime);
}
