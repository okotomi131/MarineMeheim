/*********************************************************************
 * @file   Effect.cpp
 * @brief  エフェクトを汎用的に生成する
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "Effect.h"

#include "../Camera/CameraBase.h"
#include "../Camera/CameraPlayer.h"
#include "../../02_Component/Shader/Shader.h"
#include "../../04_Scene/SceneBase.h"
#include "../../04_Scene/SceneController.h"


void Effect::Load(const char* filename)
{
	Add_Component<Shader>()->Load("Assets/Shader/VS_Color.cso","Assets/Shader/PS_Texture.cso");

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
		filename,
		&m_pTexture);
	assert(m_pTexture);
}

void Effect::Uninit()
{
	Release_and_Null<>(m_pVertexBuffer, "m_VertexBuffer");
	Release_and_Null<>(m_pTexture, "m_Texture");
}

void Effect::Update(float deltatime)
{
	m_curTime += deltatime;
	if (m_animeTime < 0.0f)
	{
		m_animeTime = -1.0f;
	}
	else if (m_curTime > m_animeTime)
	{
		m_animeCnt++;
		m_curTime = 0.0f;
	}
	//- アニメーション一周したら削除
	if (m_animeCnt >= m_uvX * m_uvY)
	{	Set_Destory();	}
}

void Effect::Draw()
{
	float x = (m_animeCnt % m_uvX) * (1.0f / m_uvX);
	float y = (m_animeCnt / m_uvX) * (1.0f / m_uvY);
	float addX = 1.0f / m_uvX;
	float addY = 1.0f / m_uvY;


	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	DirectXRenderer::Get_DeviceContext()->Map(m_pVertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX3D* vtx = (VERTEX3D*)msr.pData;

	DirectX::XMFLOAT3 pos[] =
	{
		{-1.0f, 1.0f, 0.0f},
		{ 1.0f, 1.0f, 0.0f},
		{-1.0f,-1.0f, 0.0f},
		{ 1.0f,-1.0f, 0.0f},
	};

	DirectX::XMFLOAT2 uv[] =
	{
		{x		 ,y		  },
		{x + addX,y		  },
		{x		 ,y + addY},
		{x + addX,y + addY},
	};

	for (int i = 0; i < 4; i++)
	{
		vtx[i].pos = pos[i];
		vtx[i].normal = { 0.0f, 1.0f, 0.0f };
		vtx[i].diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		vtx[i].uv = uv[i];
	}

	DirectXRenderer::Get_DeviceContext()->Unmap(m_pVertexBuffer, 0);

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
	invView._21 = view._12;
	invView._22 = view._22;
	invView._23 = view._32;
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
	DirectXRenderer::Write_Buffer<MATERIAL>("material", material);
	// テクスチャ設定
	DirectXRenderer::Get_DeviceContext()->PSSetShaderResources(0, 1, &m_pTexture);

	// プリミティブトポロジ設定
	DirectXRenderer::Get_DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	DirectXRenderer::Get_DeviceContext()->Draw(4, 0);
}
