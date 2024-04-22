/*********************************************************************
 * @file   Grass.h
 * @brief  草
 *********************************************************************/
#ifndef __GRASS_H__
#define __GRASS_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../Object.h"
class Grass : public Object
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
	float m_moveTime;
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_pTexture = nullptr;
	ID3D11ShaderResourceView* m_pDizaTex = nullptr;
	DirectX::XMFLOAT3 m_cameraPos = { 0.0f, 0.0f, 0.0f };
};

#endif // !__GRASS_H__
