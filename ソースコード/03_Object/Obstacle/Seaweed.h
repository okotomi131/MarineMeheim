/*********************************************************************
 * @file   Seaweed.h
 * @brief  海藻の処理
 *********************************************************************/
#ifndef __SEAWEED_H__
#define __SEAWEED_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../Object.h"
class Seaweed : public Object
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
	float m_moveTime = 0.0f;
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_pTexture = nullptr;
	ID3D11ShaderResourceView* m_pDizaTex = nullptr;
	DirectX::XMFLOAT3 m_cameraPos = { 0.0f, 0.0f, 0.0f };
};

#endif // !__SEAWEED_H__


