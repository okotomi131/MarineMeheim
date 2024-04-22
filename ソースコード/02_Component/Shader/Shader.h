/*********************************************************************
 * @file   Shader.h
 * @brief  シェーダーの読み込み
 *********************************************************************/

#ifndef __SHADER_H__
#define __SHADER_H__

/*
==================================================

インクルード

==================================================
*/
#include "../Component.h"

class Shader : public Component
{
public:
	using Component::Component;

	/**
	 * @brief シェーダーの読み込み
	 * @param vs 頂点シェーダーファイル名
	 * @param ps ピクセルシェーダーファイル名
	 */
	void Load(const char* vs, const char* ps);

	/**
	 * @brief 終了処理
	 */
	void Uninit() override;

	/**
	 * @brief 描画処理
	 */
	void Draw() override;

private:
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader*	m_pPixelShader;
	ID3D11InputLayout*	m_pVertexLayout;
};


#endif // !__SHADER_H__


