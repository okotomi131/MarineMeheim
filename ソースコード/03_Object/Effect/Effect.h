/*********************************************************************
 * @file   Effect.h
 * @brief  エフェクトを汎用的に生成する
 *********************************************************************/
#ifndef __EFFECT_H__
#define __EFFECT_H__
/*
==================================================

インクルード

==================================================
*/
#include "../Object.h"
#include "../../01_System/Texture/CreateTexture.h"

class Effect : public Object
{
public:
	/**
	 * @brief ファイル読み込み
	 * @param filename
	 */
	void Load(const char* filename);

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

	/*
	==================================================

	セッター

	==================================================
	*/
	/**
	 * @birief アニメーションの分割数を設定する
	 */
	void Set_UvDivision(int x, int y) { m_uvX = x; m_uvY = y; };

	/**
	 * @brief アニメーションの再生時間を設定する
	 */
	void Set_PlayTime(float time)	  { m_animeTime = time; };

private:
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_pTexture = nullptr;

	int		m_animeCnt = 0;
	float	m_animeTime = -1.0f;
	int		m_uvX = 1;
	int		m_uvY = 1;
	float   m_curTime = 1.0f;
};

#endif // !__EFFECT_H__


