/*********************************************************************
 * @file   Obstacle.cpp
 * @brief  障害物オブジェクトを汎用的に作成する
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "Obstacle.h"

#include "../Collider/Collider.h"
#include "../Camera/CameraBase.h"
#include "../Camera/CameraPlayer.h"
#include "../../02_Component/Shader/Shader.h"
#include "../../02_Component/Model/Model.h"

#include "../../04_Scene/SceneBase.h"
#include "../../04_Scene/SceneController.h"

void Obstacle::Load(const char* fileName)
{
	{
		m_size = { 3.0f,3.0f,3.0 };

		Collider* coll = Add_Obj<Collider>();
		coll->Set_Tag(m_name);
		coll->Set_WorldMatrix(Get_WorldMatrix());
		coll->Set_wSize(m_size);
		coll->Set_Pos({ 0.0f,1.0f,0.0f });
	}

	Add_Component<Model>()->Load(fileName);
}

void Obstacle::Init()
{
	Add_Component<Shader>()->Load("Assets/Shader/VS_AlphaDither.cso", "Assets/Shader/PS_Rock.cso");
}

void Obstacle::Update(float deltatime)
{
	Get_Obj<Collider>()->Set_WorldMatrix(Get_WorldMatrix());

	SceneBase*  scene = SceneController::Get_Scene();
	CameraBase* camera = scene->Get_BaseObject<class CameraPlayer>();
	CONSTANT_BUFFE_OBJECT obj;
	obj.pos = camera->Get_Pos();
	DirectXRenderer::Write_Buffer<CONSTANT_BUFFE_OBJECT>("object", obj);

}

void Obstacle::Set_CollSize(float size)
{
	Get_Obj<Collider>()->Set_WorldMatrix(Get_WorldMatrix());
	Get_Obj<Collider>()->Set_wSize({ size ,size,size });
}
