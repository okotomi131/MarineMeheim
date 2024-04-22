/*
	SceneBase.cpp
	シーンベース
*/
#include "SceneBase.h"
#include "SceneController.h"

#include "../02_Component/Model/Model.h"
#include "../03_Object/Fade/Fade.h"

/// <summary>
/// 初期化
/// </summary>
void SceneBase::InitBase()
{
	m_Fade = Add_Object<Fade>(4);
	Init();
}

/// <summary>
/// 終了処理
/// </summary>
void SceneBase::UninitBase()
{
	for (auto& objs : m_Objects)
	{
		for(Object* obj : objs)
		{
			obj->UninitBase();
			Delete_and_Null<>(obj,"obj");
		}
		objs.clear();
	}

	Uninit();
	Model::UnloadAll();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltatime">描画処理</param>
void SceneBase::UpdateBase(float deltatime)
{
	for (auto& objs : m_Objects)
	{
		for (Object* obj : objs)
		{	obj->UpdateBase(deltatime);		}
		objs.remove_if([](Object* obj) {return obj->Destory(); });
	}

	Update(deltatime);
}

/// <summary>
/// 描画処理
/// </summary>
void SceneBase::DrawBase()
{
	DirectX::XMFLOAT4X4 matrix;
	DirectX::XMStoreFloat4x4(&matrix,
		DirectX::XMMatrixIdentity());

	for (auto& objs : m_Objects)
	{
		for(Object* obj : objs)
		{	obj->DrawBase(matrix);	}
	}

	Draw();
}

