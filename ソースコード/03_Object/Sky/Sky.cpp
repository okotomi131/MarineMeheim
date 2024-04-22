/*********************************************************************
 * @file   Sky.cpp
 * @brief  スカイドームの実装
 *********************************************************************/

/*
===================================================================

インクルード

===================================================================
*/
#include "Sky.h"
#include "../../02_Component/Model/Model.h"
#include "../../02_Component/Shader/Shader.h"
#include "../../03_Object/Camera/CameraBase.h"
#include "../../04_Scene/SceneBase.h"
#include "../../04_Scene/SceneController.h"

void Sky::Init()
{
	Add_Component<Shader>()->Load(
		"Assets/Shader/VS_Color.cso",
		"Assets/Shader/PS_Texture.cso");

	Add_Component<Model>()->Load("Assets/Model/Object/Sky.obj");

	m_size = { 1000.0f, 1000.0f, 1000.0f };
}

void Sky::Update(float deltatime)
{
	SceneBase* scene = SceneController::Get_Scene();
	CameraBase* camera = scene->Get_BaseObject<CameraBase>();
	m_pos = camera->Get_Pos();
}
