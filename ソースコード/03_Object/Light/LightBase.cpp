/*********************************************************************
 * @file   LightBase.cpp
 * @brief  ライトの基底クラス
 *********************************************************************/
#include "LightBase.h"
#include "../../01_System/Input/Input.h"
void LightBase::Init()
{
	m_light.enable = true;
	DirectX::XMVECTOR vDir = DirectX::XMVectorSet(-1.5f, -4.0f, 1.8f, 0.0f);
	DirectX::XMVector3Normalize(vDir);
	DirectX::XMStoreFloat4(&m_light.direction,vDir);
	m_light.ambient = m_ambient;
	m_light.diffuse = m_diffuse;
	DirectXRenderer::Write_Buffer<LIGHT>("light",m_light);
}
