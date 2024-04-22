/*********************************************************************
 * @file   Sprite.cpp
 * @brief  スプライト描画
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "Sprite.h"
#include "../../01_System/Texture/CreateTexture.h"

void Sprite::Init(DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 size, const char* fileName)
{
	const int vtxNum = 4;	//頂点数
	VERTEX3D vtx[vtxNum];	//頂点データ
	m_fileName = fileName;
	m_pos = pos;
	m_size = size;

	DirectX::XMFLOAT2 Pos[] = //座標
	{
		{ pos.x			 ,pos.y },
		{ pos.x + size.x ,pos.y },
		{ pos.x		     ,pos.y + size.y},
		{ pos.x + size.x ,pos.y + size.y},
	};

	DirectX::XMFLOAT2 Uv[] =	//UV座標
	{ {0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} };

	for (int i = 0; i < vtxNum;i++)
	{
		vtx[i].pos	   = { Pos[i].x,Pos[i].y,0.0f };
		vtx[i].normal  = { 0.0f,0.0f,0.0f };
		vtx[i].diffuse = { 1.0f,1.0,1.0f,1.0f };
		vtx[i].uv	   = Uv[i];
	}

	//- 頂点バッファの作成
	D3D11_BUFFER_DESC desc = {};
	desc.Usage		= D3D11_USAGE_DEFAULT;
	desc.ByteWidth	= sizeof(VERTEX3D) * 4;
	desc.BindFlags	= D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = vtx;

	DirectXRenderer::Get_Device()->CreateBuffer(
		&desc, &data, &m_pVertexBuffer);
	if(m_fileName)
	{ 
		CreateTextureFromFile(
			DirectXRenderer::Get_Device(), m_fileName, &m_pTexture);
		assert(m_pTexture);
	}
	else
	{	m_pTexture = nullptr;	}

	m_material.diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
}

/// <summary>
/// 終了処理
/// </summary>
void Sprite::Uninit()
{
	Release_and_Null<>(m_pVertexBuffer,"m_pVertexBuffer");
	Release_and_Null<>(m_pTexture,"m_pTexture");
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltatime">デルタタイム</param>
void Sprite::Update(float deltatime)
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
}

/// <summary>
/// 描画処理
/// </summary>
void Sprite::Draw()
{

	float x = m_animeCnt % m_uvX * 1.0f / m_uvX;
	float y = m_animeCnt / m_uvX * 1.0f / m_uvY;
	float addX = 1.0f / m_uvX;
	float addY = 1.0f / m_uvY;

	const int vtxNum = 4;	//頂点数
	VERTEX3D vtx[vtxNum];	//頂点データ

	DirectX::XMFLOAT2 pos[] =
	{
		{ m_pos.x			 ,m_pos.y },
		{ m_pos.x + m_size.x ,m_pos.y },
		{ m_pos.x		     ,m_pos.y + m_size.y},
		{ m_pos.x + m_size.x ,m_pos.y + m_size.y},
	};

	DirectX::XMFLOAT2 uv[] =
	{
		{x		 ,y		  },
		{x + addX,y		  },
		{x		 ,y + addY},
		{x + addX,y + addY},
	};

	for (int i = 0; i < vtxNum; i++)
	{
		vtx[i].pos = { pos[i].x,pos[i].y,0.0f };
		vtx[i].normal = { 0.0f,0.0f,0.0f };
		vtx[i].diffuse = { 1.0f,1.0,1.0f,1.0f };
		vtx[i].uv = uv[i];
	}

	VertexRot(vtxNum, pos, vtx);

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(VERTEX3D) * 4;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = vtx;

	DirectXRenderer::Get_Device()->CreateBuffer(
		&desc, &data, &m_pVertexBuffer);

	DirectXRenderer::Write_WorldViewProjection2D();
	UINT stride = sizeof(VERTEX3D);
	UINT offset = 0;
	DirectXRenderer::Get_DeviceContext()->IASetVertexBuffers(
		0, 1, &m_pVertexBuffer, &stride, &offset);
	DirectXRenderer::Get_DeviceContext()->PSSetShaderResources(
		0, 1, &m_pTexture);
	DirectXRenderer::Get_DeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//定数バッファの書き込み
	DirectXRenderer::Write_Buffer<MATERIAL>("material", m_material);
	DirectXRenderer::Write_Buffer<CONSTANT_BUFFE_OBJECT>("object", m_bufferObject);
	
	DirectXRenderer::Set_DepthEnable(false);
	DirectXRenderer::Get_DeviceContext()->Draw(4, 0);
	DirectXRenderer::Set_DepthEnable(true);
}

void Sprite::VertexRot(const int& vtxNum, DirectX::XMFLOAT2  pos[4], VERTEX3D  vtx[4])
{
	//- 中心座標を求める
	DirectX::XMFLOAT2 center =
	{
		m_pos.x + m_size.x * 0.5f,
		m_pos.y + m_size.y * 0.5f
	};

	//- 回転行列を求める
	DirectX::XMMATRIX mRot =
		DirectX::XMMatrixRotationZ(m_rot);

	for (int i = 0; i < vtxNum; i++)
	{
		//- 中心座標を原点に移動
		DirectX::XMFLOAT3 centerPos =
		{
			pos[i].x - center.x,
			pos[i].y - center.y,
			0.0f
		};

		// 回転行列を適用
		DirectX::XMVECTOR posVec =
			DirectX::XMLoadFloat3(&centerPos);
		posVec = DirectX::XMVector3Transform(posVec, mRot);

		// 新しい座標を頂点データに反映
		DirectX::XMStoreFloat3(&centerPos, posVec);
		vtx[i].pos =
		{
			centerPos.x + center.x,
			centerPos.y + center.y,
			0.0f
		};
	}
}

