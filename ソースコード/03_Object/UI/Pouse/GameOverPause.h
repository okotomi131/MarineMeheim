/*********************************************************************
 * @file   GameOverPause.h
 * @brief  ゲームオーバー時のポーズ画面
 *********************************************************************/
#ifndef __GAMEOVER_PAUSE_H__
#define __GAMEOVER_PAUSE_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "Pause.h"
class GameOverPause : public Pause
{
public:
	void Init() override;
	void Update(float deltatime) override;
	void AllFlagReset()override { m_bNewStart = false; m_bReTreat = false; }
};

#endif // !__GAMEOVER_PAUSE_H__


