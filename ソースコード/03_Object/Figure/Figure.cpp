/*********************************************************************
 * @file   Figure.cpp
 * @brief  モデルのみを表示する
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "Figure.h"

#include "../../02_Component/Shader/Shader.h"
#include "../../02_Component/Model/Model.h"

void Figure::Update(float deltatime)
{
	if (m_bRotate) { m_rot.y += 0.01f; }
}

void Figure::LoadModel(const char* filename)
{
	Add_Component<Shader>()->Load(
		"Assets/Shader/VS_Object.cso",
		"Assets/Shader/PS_Light.cso");
	Add_Component<Model>()->Load(filename);
}
