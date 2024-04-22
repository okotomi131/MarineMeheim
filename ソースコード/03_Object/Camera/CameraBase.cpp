/*********************************************************************
 * @file   CameraBase.cpp
 * @brief  カメラベース
 *********************************************************************/
/*
==================================================

インクルード

==================================================
*/
#include "CameraBase.h"
#include "../../01_System/Window/WinStartUp.h"

/// <summary>
/// 初期化処理
/// </summary>
void CameraBase::Init()
{
	m_pos = DirectX::XMFLOAT3(0.0f, 5.0f, -10.0f);
	m_target = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_up = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
}

/// <summary>
/// 描画処理
/// </summary>
void CameraBase::Draw()
{
	//ビューマトリクス設定
	DirectX::XMStoreFloat4x4(&m_viewMatrix,
		DirectX::XMMatrixLookAtLH(
			DirectX::XMLoadFloat3(&m_pos),
			DirectX::XMLoadFloat3(&m_target),
			DirectX::XMLoadFloat3(&m_up)));

	DirectXRenderer::Write_View(&m_viewMatrix);

	//プロジェクションマトリクス設定
	DirectX::XMFLOAT4X4 projectionMatrix;
	DirectX::XMStoreFloat4x4(&projectionMatrix,
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(60),
			(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f)
	);

	DirectXRenderer::write_Projection(&projectionMatrix);
}
