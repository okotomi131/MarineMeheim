/*********************************************************************
 * @file   AppControl.h
 * @brief  アプリケーション制御クラス
 *********************************************************************/

#ifndef __APPCONTROL_H__
#define __APPCONTROL_H__

/*
==================================================

インクルード

==================================================
*/
#include "../Window/WinStartUp.h"


class AppControl
{
public:
	/**
	 * @brief コンストラクタ
	 *
	 * ウィンドウ、シーンの初期化を呼び出す
	 *
	 * @param hinst インスタントハンドル(エントリーポイントから渡される
	 * @param cmd コマンドライン(上記と同じ
	 */
	AppControl(HINSTANCE hinst, int cmd);


	/**
	 * @brief デストラクタ
	 * ウィンドウ、シーンの終了処理を呼び出す
	 */
	~AppControl();

	/**
	 * @brief アプリケーションループ
	 * メッセージループとゲームループを行う
	 */
	void Update();

	/**
	 * @brief デバック用FPS表示
	 * @param diff フレームレート
	 */
	void DebugFPS(float diff);
private:
	DWORD		m_startTime;		//開始時間
	DWORD		m_executionTime;	//実行時間
};

#endif // !__APPCONTROL_H__
