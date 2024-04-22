/*********************************************************************
 * @file   Barrier.h
 * @brief  ステージの移動制限を行う
 *********************************************************************/

#ifndef __BARRIER_H__
#define __BARRIER_H__

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../Object.h"
#include "../../01_System/Texture/CreateTexture.h"


class Barrier : public Object
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief 終了処理
	 */
	void Uninit() override;

	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/**
	 * @brief 描画処理
	 */
	void Draw() override;
private:
	float m_DeltaTime = 0;
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_pTexture = nullptr;
	DirectX::XMFLOAT3 m_PlayerPos = { 0.0f, 0.0f, 0.0f };
};

#endif // !__BARRIER_H__
