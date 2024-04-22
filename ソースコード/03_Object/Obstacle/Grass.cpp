/*********************************************************************
 * @file   Grass.cpp
 * @brief  草
 *********************************************************************/

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "Grass.h"

#include "../Camera/CameraBase.h"
#include "../Camera/CameraPlayer.h"
#include "../../02_Component/Shader/Shader.h"
#include "../../04_Scene/SceneBase.h"
#include "../../04_Scene/SceneController.h"

#include "../../01_System/Texture/CreateTexture.h"

void Grass::Init()
{
	Add_Component<Shader>()->Load("Assets/Shader/VS_AlphaDither.cso","Assets/Shader/PS_Rock.cso");

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
		"Assets/Texture/Ground/Grass.png",
		&m_pTexture);
	assert(m_pTexture);

}

void Grass::Uninit()
{
	Release_and_Null<>(m_pVertexBuffer, "m_VertexBuffer");
	Release_and_Null<>(m_pTexture, "m_Texture");
}

void Grass::Update(float deltatime)
{
	SceneBase* scene = SceneController::Get_Scene();
	CameraBase* camera = scene->Get_BaseObject<class CameraPlayer>();
	m_cameraPos = camera->Get_Pos();
	m_moveTime += deltatime;

}

void Grass::Draw()
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX3D);
	UINT offset = 0;
	DirectXRenderer::Get_DeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	DirectXRenderer::Write_Buffer<MATERIAL>("material", material);

	TIME time;
	ZeroMemory(&time, sizeof(time));
	time.time = m_moveTime;
	DirectXRenderer::Write_Buffer<TIME>("time", time);

	CONSTANT_BUFFE_OBJECT obj;
	obj.pos = m_cameraPos;
	DirectXRenderer::Write_Buffer<CONSTANT_BUFFE_OBJECT>("object", obj);

	// テクスチャ設定
	DirectXRenderer::Get_DeviceContext()->PSSetShaderResources(0, 1, &m_pTexture);
	DirectXRenderer::Get_DeviceContext()->PSSetShaderResources(1, 1, &m_pDizaTex);

	// プリミティブトポロジ設定
	DirectXRenderer::Get_DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	DirectXRenderer::Get_DeviceContext()->Draw(4, 0);

}
