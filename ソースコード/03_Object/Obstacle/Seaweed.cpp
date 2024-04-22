/*********************************************************************
 * @file   Seaweed.cpp
 * @brief  海藻
 *********************************************************************/
 /*
 ==================================================

 インクルード

 ==================================================
 */

#include "Seaweed.h"

#include "../Camera/CameraBase.h"
#include "../Camera/CameraPlayer.h"
#include "../../02_Component/Shader/Shader.h"
#include "../../04_Scene/SceneBase.h"
#include "../../04_Scene/SceneController.h"

#include "../../01_System/Texture/CreateTexture.h"

void Seaweed::Init()
{
	Add_Component<Shader>()->Load(
		"Assets/Shader/VS_AlphaDither.cso",
		"Assets/Shader/PS_Seaweed.cso");
	const int vtxNum = 4;
	VERTEX3D vtx[vtxNum];

	DirectX::XMFLOAT3 pos[] =
	{
		{-1.0f, 1.0f, 0.0f},
		{ 1.0f, 1.0f, 0.0f},
		{-1.0f,-1.0f, 0.0f},
		{ 1.0f,-1.0f, 0.0f},
	};

	DirectX::XMFLOAT2 uv[] =
	{ {0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

	for (int i = 0; i < vtxNum; i++)
	{
		vtx[i].pos = pos[i];
		vtx[i].normal = { 0.0f, 1.0f, 0.0f };
		vtx[i].diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		vtx[i].uv = uv[i];
	}

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vtx;

	DirectXRenderer::Get_Device()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);


	// テクスチャ読み込み
	CreateTextureFromFile(DirectXRenderer::Get_Device(),
		"Assets/Texture/Diza.png",
		&m_pDizaTex);
	assert(m_pDizaTex);

	CreateTextureFromFile(DirectXRenderer::Get_Device(),
		"Assets/Texture/Seaweed.png",
		&m_pTexture);
	assert(m_pTexture);

}

void Seaweed::Uninit()
{
	Release_and_Null<>(m_pVertexBuffer, "m_VertexBuffer");
	Release_and_Null<>(m_pTexture, "m_Texture");
}

void Seaweed::Update(float deltatime)
{
	SceneBase* scene = SceneController::Get_Scene();
	CameraBase* camera = scene->Get_BaseObject<class CameraPlayer>();
	m_cameraPos = camera->Get_Pos();
	m_moveTime += deltatime;

}

void Seaweed::Draw()
{
	// カメラのビューマトリクス取得
	SceneBase* scene = SceneController::Get_Scene();
	CameraPlayer* camera = scene->Get_Object<CameraPlayer>();
	DirectX::XMFLOAT4X4 view = camera->Get_ViewMatrix();

	// ビューの逆行列 (転置行列)
	DirectX::XMFLOAT4X4 invView;
	invView._11 = view._11;
	invView._12 = view._21;
	invView._13 = view._31;
	invView._14 = 0.0f;
	invView._21 = 0.0f;
	invView._22 = 1.0f;
	invView._23 = 0.0f;
	invView._24 = 0.0f;
	invView._31 = view._13;
	invView._32 = view._23;
	invView._33 = view._33;
	invView._34 = 0.0f;
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;
	invView._44 = 1.0f;

	// ワールドマトリクス設定
	DirectX::XMFLOAT4X4 world;
	DirectX::XMMATRIX scale, trans;
	scale = DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z);
	trans = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMStoreFloat4x4(&world, scale * DirectX::XMLoadFloat4x4(&invView) * trans);
	DirectXRenderer::Write_World(&world);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX3D);
	UINT offset = 0;
	DirectXRenderer::Get_DeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//material.textureEnable = true;
	//DirectXRenderer::Write_Material(material);
	DirectXRenderer::Write_Buffer<MATERIAL>("material", material);

	TIME time;
	ZeroMemory(&time, sizeof(time));
	time.time = m_moveTime;
	//DirectXRenderer::Write_Time(time);
	DirectXRenderer::Write_Buffer<TIME>("time", time);

	CONSTANT_BUFFE_OBJECT obj;
	obj.pos = m_cameraPos;
	//DirectXRenderer::Write_Object(obj);
	DirectXRenderer::Write_Buffer<CONSTANT_BUFFE_OBJECT>("object", obj);

	// テクスチャ設定
	DirectXRenderer::Get_DeviceContext()->PSSetShaderResources(0, 1, &m_pTexture);
	DirectXRenderer::Get_DeviceContext()->PSSetShaderResources(1, 1, &m_pDizaTex);
	
	// プリミティブトポロジ設定
	DirectXRenderer::Get_DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//DirectXRenderer::Set_ATCEnable(true);
	// ポリゴン描画
	DirectXRenderer::Get_DeviceContext()->Draw(4, 0);
	//DirectXRenderer::Set_ATCEnable(false);
}
