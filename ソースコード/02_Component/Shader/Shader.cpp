/*********************************************************************
 * @file   Shader.cpp
 * @brief  シェーダー読み込み
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "Shader.h"
#include "../../01_System/DirectX/DirectXRenderer.h"

void Shader::Load(const char * vs, const char * ps)
{
	DirectXRenderer::CreateVertexShader(&m_pVertexShader, &m_pVertexLayout, vs);
	DirectXRenderer::CreatePixelShader(&m_pPixelShader,ps);
}

void Shader::Uninit()
{
	Release_and_Null<>(m_pPixelShader,"m_pPixelShader");
	Release_and_Null<>(m_pVertexLayout, "m_pVertexLayout");
	Release_and_Null<>(m_pVertexShader, "m_pVertexShader");
}

void Shader::Draw()
{
	DirectXRenderer::Get_DeviceContext()->IASetInputLayout(m_pVertexLayout);	
	DirectXRenderer::Get_DeviceContext()->VSSetShader(m_pVertexShader,nullptr,0);
	DirectXRenderer::Get_DeviceContext()->PSSetShader(m_pPixelShader, nullptr,0);
}
