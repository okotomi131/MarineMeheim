/*********************************************************************
 * @file   Field.cpp
 * @brief  床の実装
 *********************************************************************/

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "Field.h"
#include "../../02_Component/3D/Plane.h"
#include "../../02_Component/Shader/Shader.h"

void Field::Init()
{
	m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = DirectX::XMFLOAT3(700.0f, 1.0f, 700.0f);

	Add_Component<Shader>()->Load(
		"Assets/Shader/VS_Object.cso",
		"Assets/Shader/PS_Wave.cso");

	Add_Component<Plane>()->Init("Assets/Texture/Ground/Sand.jpg");
}
