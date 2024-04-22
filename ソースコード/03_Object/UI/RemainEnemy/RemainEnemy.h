/*********************************************************************
 * @file   RemainEnemy.h
 * @brief  敵の残数を表示するUIクラス
 *********************************************************************/
#ifndef __REMAIN_ENEMY_H__
#define __REMAIN_ENEMY_H__
/*
==================================================

インクルード

==================================================
*/
#include "../../Object.h"

class RemainEnemy : public Object
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init()override;

	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	void Update(float deltatime)override;

	/**
	 * @brief 描画処理
	 */
	void Draw()override;

	/**
	 * @brief アニメーション処理
	 */
	void StartAnime(float deltatime);	//開始アニメーション

	/**
	 * @brief 敵の残数を減らす
	 */
	void Set_EnemyMaxNum(int num) { m_enemyMaxNum = num; }	//敵の最大数を設定する

	/**
	 * @brief 敵の残数を減らす
	 */
	int Get_CurEnemyNum() { return m_curEnemyNum; }	//現在の敵の残数を取得する
private:


	const float MAX_START_ANIME_TIME = 1.0f;	//開始アニメーションの最大時間
	const float START_ANIME_FINISH_POS_X = 1050.0f;//開始アニメーション終了時のX座標
	const float START_ANIME_FINISH_POS_Y = -100.0f;//開始アニメーション終了時のY座標


	int m_curEnemyNum = 999;//敵の残数
	int m_enemyMaxNum;	//敵の最大数
	const char* m_backGroundFileName;	//背景のファイル名
	
	float m_curStartAnimeTime = {};	//開始アニメーションの時間

	DirectX::XMFLOAT2 m_CenterPos = {};	//中心座標
	DirectX::XMFLOAT2 m_initPos = {};	//座標

	class Sprite* m_sp = nullptr;	//スプライト

	float m_rotSpeed = 0.02f;	//回転速度
};

#endif // !__REMAIN_ENEMY_H__