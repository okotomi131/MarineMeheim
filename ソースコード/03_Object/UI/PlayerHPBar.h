/*********************************************************************
 * @file   PlayerHPBar.h
 * @brief  プレイヤーの現在のHPを表示するUI
 *********************************************************************/
#ifndef __PLAYER_HP_BAR_H__
#define __PLAYER_HP_BAR_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../Object.h"

class PlayerHPBar :public Object
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/**
	 * @brief 描画処理
	 */
	void Draw() override;

	/**
	 * @brief HPバーの増減
	 */
	void MoveHPBar();

	/**
	 * @brief 最大HPの設定
	 * @param maxhp
	 */
	void Set_MaxHP(float maxhp) { m_maxHP = maxhp; }
private:
	float m_maxHP;
	DirectX::XMFLOAT2 m_initSize;
};

#endif // !__PLAYER_HP_BAR_H__


