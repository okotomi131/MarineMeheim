/*********************************************************************
 * @file   Pause.h
 * @brief  ポーズ処理
 *********************************************************************/
#ifndef __PAUSE_H__
#define __PAUSE_H__
/*
==================================================

インクルード

==================================================
*/

#include "../../Object.h"
#include "../../../02_Component/Sprite/Sprite.h"

class Pause : public Object
{
public:
	/**
	 * @brief 初期化処理
	 */
	virtual void Init() override;

	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	virtual void Update(float deltatime)override;

	/**
	 * @brief 画面内に描画
	 */
	virtual void DrawPause();

	/**
	 * @brief 画面外に描画
	 */
	virtual void UnDrawPause();

	/**
	 * @brief 再開フラグを取得
	 * @return 再開ボタンが押されたらtrue
	 */
	bool Get_Restart() { return m_bRestart; }

	/**
	 * @brief やりなおしフラグを取得
	 * @return やりなおしボタンが押されたらtrue
	 */
	bool Get_NewStart() { return m_bNewStart; }

	/**
	 * @brief 撤退フラグを取得
	 * @return 撤退ボタンが押されたらtrue
	 */
	bool Get_ReTreat() { return m_bReTreat; }

	/**
	 * @brief 全てのフラグをリセット
	 * 各フラグはそれぞれ同時にtrueになることはない
	 */
	virtual void AllFlagReset() { m_bRestart = false; m_bNewStart = false; m_bReTreat = false; }
protected:
	bool m_bNewStart = false;
	bool m_bReTreat = false;

	DirectX::XMFLOAT2 m_PausePos = { 0.0f,0.0f };
	std::vector<DirectX::XMFLOAT2> m_buttonPos;
	std::vector<class ButtonBase*> m_pButtonList;
private:
	bool m_bRestart = false;
};

#endif // !__PUSE_H__
