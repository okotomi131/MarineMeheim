/*********************************************************************
 * @file   Object.cpp
 * @brief  ゲーム内オブジェクトの基底クラス
 *********************************************************************/
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "Object.h"

void Object::InitBase()
{
	m_pos  = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_rot  = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	Init();
}

void Object::UninitBase()
{
	Uninit();
	//- 自分のコンポーネントの解放
	for (Component* comp : m_component)
	{
		comp->Uninit();
		delete comp;
	}
	m_component.clear();
}

void Object::UpdateBase(float deltaTime)
{
	for (Component* comp : m_component)
	{ comp->Update(deltaTime); }
	Update(deltaTime);
}

void Object::DrawBase(DirectX::XMFLOAT4X4 parentmatrix)
{
	DirectX::XMFLOAT4X4 world;
	DirectX::XMMATRIX scale,rot,trans;
	scale	= DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z);
	rot		= DirectX::XMMatrixRotationRollPitchYaw(m_rot.x, m_rot.y, m_rot.z);
	trans	= DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMStoreFloat4x4(
		&world,scale * rot * trans * DirectX::XMLoadFloat4x4(&parentmatrix));

	for (Object* child : m_childObj) {
		child->DrawBase(world);
	}

	DirectXRenderer::Write_World(&world);

	for (Component* comp : m_component) {
		comp->Draw();
	}

	Draw();
}

bool Object::Destory()
{
	if (m_bDestroy)
	{
		UninitBase();
		delete this;
		return true;
	}
	return false;
}

/*
==================================================

ゲッター

==================================================
*/

DirectX::XMVECTOR Object::Get_vForward() const
{
	//正面ベクトルを計算する
	DirectX::XMFLOAT4X4 rot;
	DirectX::XMMATRIX matRot;
	matRot = DirectX::XMMatrixRotationRollPitchYaw(m_rot.x, m_rot.y, m_rot.z);
	DirectX::XMStoreFloat4x4(&rot, matRot);	//マトリックス型をFloat4x4型に変換
	//回転要素だけ取り出す
	DirectX::XMFLOAT3 Forward = { rot._31,rot._32,rot._33 };
	DirectX::XMVECTOR vForward = DirectX::XMLoadFloat3(&Forward);

	return vForward;
}

DirectX::XMVECTOR Object::Get_vUp() const
{
	DirectX::XMVECTOR vUp;
	//上ベクトルを計算
	DirectX::XMFLOAT4X4 rot;
	DirectX::XMMATRIX matRot;
	matRot = DirectX::XMMatrixRotationRollPitchYaw(m_rot.x, m_rot.y, m_rot.z);
	DirectX::XMStoreFloat4x4(&rot, matRot);	//マトリックス型をFloat4x4型に変換
	//上ベクトルに必要な情報だけ取り出す
	DirectX::XMFLOAT3 Up = { rot._21,rot._22,rot._23 };
	vUp = DirectX::XMLoadFloat3(&Up);
	DirectX::XMVector3Normalize(vUp);
	return vUp;
}

DirectX::XMVECTOR Object::Get_vDown() const
{
	DirectX::XMFLOAT3 down = {0.0f,-1.0f,0.0f };
	DirectX::XMVECTOR vDown = DirectX::XMLoadFloat3(&down);
	return vDown;
}

DirectX::XMFLOAT3 Object::Get_MinPoint() const
{
	DirectX::XMFLOAT3 point = {};
	point.x = m_pos.x - m_size.x * 0.5f;
	point.y = m_pos.y - m_size.y * 0.5f;
	point.z = m_pos.z - m_size.z * 0.5f;

	return point;
}

DirectX::XMFLOAT3 Object::Get_MaxPoint() const
{
	DirectX::XMFLOAT3 point = {};
	point.x = m_pos.x + m_size.x * 0.5f;
	point.y = m_pos.y + m_size.y * 0.5f;
	point.z = m_pos.z + m_size.z * 0.5f;

	return point;
}

DirectX::XMMATRIX Object::Get_WorldMatrix() const
{
	DirectX::XMMATRIX size = DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z);
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(m_rot.x, m_rot.y, m_rot.z);
	DirectX::XMMATRIX pos = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	return size * rot * pos;
}
