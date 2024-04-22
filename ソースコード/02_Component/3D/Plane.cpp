/*********************************************************************
 * @file   Plane.cpp
 * @brief  板ポリゴンを描画するクラス
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "Plane.h"
#include "../../01_System/Texture/CreateTexture.h"

void Plane::Init(const char* filename)
{
	const int vtxNum = 4;
	float size = 0.5f;
	float uvNum = 2.0f;
	VERTEX3D vtx[vtxNum];

	DirectX::XMFLOAT3 pos[] =
	{
		{-size, 0.0f, size},
		{ size, 0.0f, size},
		{-size, 0.0f,-size},
		{ size, 0.0f,-size},
	};

	DirectX::XMFLOAT3 normal = { 0.0f, 1.0f, 0.0f };
	DirectX::XMFLOAT4 diff = { 1.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT2 uv[] =
	{
		{0.0f, 0.0f},
		{uvNum,0.0f},
		{0.0f, uvNum},
		{uvNum,uvNum},
	};

	for (int i = 0; i < vtxNum; i++)
	{
		vtx[i].pos	   = pos[i];
		vtx[i].normal  = { 0.0f, 1.0f, 0.0f };
		vtx[i].diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		vtx[i].uv	   = uv[i];
	}

	//- 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX3D) * vtxNum;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vtx;

	DirectXRenderer::Get_Device()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	CreateTextureFromFile(DirectXRenderer::Get_Device(),filename, &m_pTexture);

	assert(m_pTexture);
}

void Plane::Uninit()
{
	Release_and_Null<>(m_pVertexBuffer, "m_pVertexBuffer");
	Release_and_Null<>(m_pTexture, "m_pTexture");
}

void Plane::Draw()
{
	const int vtxNum = 4;
	//- 頂点バッファ設定
	UINT stride = sizeof(VERTEX3D);
	UINT offset = 0;
	DirectXRenderer::Get_DeviceContext()->IASetVertexBuffers(
		0, 1, &m_pVertexBuffer, &stride, &offset);

	//- マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	DirectXRenderer::Write_Buffer<MATERIAL>("material", material);

	//- テクスチャ設定
	DirectXRenderer::Get_DeviceContext()->PSSetShaderResources(0, 1, &m_pTexture);

	//- プリミティブトポロジ設定
	DirectXRenderer::Get_DeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//- 描画
	DirectXRenderer::Get_DeviceContext()->Draw(vtxNum, 0);
}

