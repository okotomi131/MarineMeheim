/*********************************************************************
 * @file   BulletNumUI.h
 * @brief  弾の残弾を表示するUI
 *********************************************************************/
#ifndef __BULLET_NUM_UI_H__
#define __BULLET_NUM_UI_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../../Object.h"

class BulletNumUI : public Object
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief 終了処理
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/**
	 * @brief 描画処理
	 */
	void Draw() override;

	/**
	 * @brief 所持武器を設定する
	 * @param weapon
	 */
	void Set_Weapon(class WeaponBase* weapon) { m_pWeapon = weapon; }
private:
	const float MAX_GAGE_SIZE_Y = 230.0f; //ゲージの最大サイズ
	
	const char* m_pBaseFileName   = nullptr;	//UIのベース
	const char* m_pCntBoxFileName = nullptr; //弾数表示枠
	const char* m_pGageFileName   = nullptr;	//弾ゲージ
	class WeaponBase* m_pWeapon = {};
	float m_initSizeY = 0.0f;
};
#endif // !__BULLET_NUM_UI_H__


