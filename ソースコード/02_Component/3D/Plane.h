/*********************************************************************
 * @file   Plane.h
 * @brief  板ポリゴンを描画するコンポーネント
 *********************************************************************/
#ifndef __PLANE_H__
#define __PLANE_H__

/*
==================================================

インクルード

==================================================
*/
#include "../Component.h"

class Plane : public Component
{
public:
	using Component::Component;
	/**
	 * @brief 初期化処理
	 * @param fileName ファイル名
	 */
	void Init(const char* fileName);

	/**
	 * @brief 終了処理
	 */
	void Uninit() override;

	/**
	 * @brief 描画処理
	 */
	void Draw() override;

private:
	ID3D11Buffer*			  m_pVertexBuffer = {};
	ID3D11ShaderResourceView* m_pTexture = {};
	ID3D11ShaderResourceView* m_pCellTexture = {};
};

#endif // !__PLANE_H__

