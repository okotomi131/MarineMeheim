/*********************************************************************
 * @file   Collider.cpp
 * @brief  コライダー
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "Collider.h"
#include "../../02_Component/Shader/Shader.h"

void Collider::Set_wSize(const DirectX::XMFLOAT3& size)
{
	DirectX::XMVECTOR vSize   = DirectX::XMLoadFloat3(&size);
	DirectX::XMVECTOR vWScale = DirectX::XMVector3Transform(vSize, m_mWorld);
	DirectX::XMStoreFloat3(&m_size, vWScale);
}

DirectX::XMFLOAT3 const Collider::Get_wMinPoint() const
{
	DirectX::XMFLOAT3 localPos = m_pos;
	DirectX::XMMATRIX wMatrix = m_mWorld;
	DirectX::XMVECTOR vlocalPos = DirectX::XMLoadFloat3(&localPos);
	DirectX::XMVECTOR vWpos = DirectX::XMVector3Transform(vlocalPos, wMatrix);
	DirectX::XMStoreFloat3(&localPos, vWpos);

	DirectX::XMFLOAT3 point;
	point.x = localPos.x - m_size.x * 0.5f;
	point.y = localPos.y - m_size.y * 0.5f;
	point.z = localPos.z - m_size.z * 0.5f;

	return point;
}

DirectX::XMFLOAT3 const Collider::Get_wMaxPoint() const
{
	DirectX::XMFLOAT3 localPos = m_pos;
	DirectX::XMMATRIX wMatrix = m_mWorld;
	DirectX::XMVECTOR vlocalPos = DirectX::XMLoadFloat3(&localPos);
	DirectX::XMVECTOR vWpos = DirectX::XMVector3Transform(vlocalPos, wMatrix);
	DirectX::XMStoreFloat3(&localPos, vWpos);

	DirectX::XMFLOAT3 point;
	point.x = localPos.x + m_size.x * 0.5f;
	point.y = localPos.y + m_size.y * 0.5f;
	point.z = localPos.z + m_size.z * 0.5f;

	return point;
}

