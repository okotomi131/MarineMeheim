/*********************************************************************
 * @file   Item_Stamina.cpp
 * @brief  スタミナ回復
 *********************************************************************/

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "Item_Stamina.h"
#include "../Collider/Collider.h"

#include "../../02_Component/Shader/Shader.h"
#include "../../02_Component/Model/Model.h"
#include "../../02_Component/Sound/Sound.h"

#include "../../04_Scene/SceneController.h"
#include "../../04_Scene/SceneBase.h"

void Item_Stamina::Init()
{
	Collider* coll = Add_Obj<Collider>();
	coll->Set_Tag("ItemStamina");
	m_size = { 0.5f,0.5f,0.5f };
	coll->Set_WorldMatrix(Get_WorldMatrix());
	coll->Set_wSize({ 2.5f,2.5f,2.5f });
	coll->Set_Pos({ 0.0f, 3.0f, 0.0f });

	Add_Component<Shader>()->Load(
		"Assets/Shader/VS_Object.cso",
		"Assets/Shader/PS_Light.cso");
	Add_Component<Model>()->Load("Assets/Model/Item/ItemStamina.obj");
}

void Item_Stamina::Update(float deltatime)
{
	Get_Obj<Collider>()->Set_WorldMatrix(Get_WorldMatrix());
	MATERIAL mat = {};
	mat.diffuse = { 1.0f,1.0f,1.0f,1.0f };
	mat.ambient = { 1.0f,1.0f,1.0f,1.0f };
	mat.specular = { 1.0f,1.0f,1.0f,1.0f };
	DirectXRenderer::Write_Buffer<MATERIAL>("material", mat);

	ItemBase::Update(deltatime);
}
