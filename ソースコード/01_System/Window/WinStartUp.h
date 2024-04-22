/*********************************************************************
 * @file   WinStartUp.h
 * @brief  ウィンドウの設定
 *********************************************************************/
#ifndef __WIN_START_UP_H__
#define __WIN_START_UP_H__
/*
==================================================

インクルード

==================================================
*/
#include <Windows.h>
#include "../main.h"

/*
==================================================

定数

==================================================
*/
static const LONG SCREEN_WIDTH  = 1280;		//ウィンドウサイズ
static const LONG SCREEN_HEIGHT = 720;
static const char*  MENU_NAME	 = "App";	//メニュー表
static const char*  CLASS_NAME	 = "マリンメヘイム";	//ウィンドウ名

#define GET_WIN WinStartUp::Get_Instance()

class WinStartUp
{
public:
	//- 構造体
	struct Float2
	{
		float x;
		float y;
	};

	//- シングルトン関連
	/**
	 * @brief インスタンス作成
	 * @param hInst
	 * @param cmd
	 */
	static void CreateInstance(HINSTANCE hInst, int cmd);

	/**
	 * @brief インスタンス削除
	 */
	static void DeleteInstance() { Delete_and_Null<>(m_spInstance, "m_spInstance"); }

	/**
	 * @brief インスタンス取得
	 * @return 
	 */
	static WinStartUp& Get_Instance() { return *m_spInstance; }

	/**
	 * @brief 初期化処理
	 * @return 
	 */
	HRESULT Init();

	/**
	 * @brief メッセージループ
	 * @return 
	 */
	bool	MsgLoop();

	/**
	 * @brief 終了処理
	 */
	void	Uninit();

	/*
	==================================================

	ゲッター

	==================================================
	*/
	/**
	 * @brief ウィンドウハンドル取得
	 * @return 
	 */
	HWND	Get_WinhWnd()	{ return m_hWnd; }

	/**
	 * @brief ホイールのカウント数を取得する
	 * 最小値から最大値の間でカウントを行う
	 * @param min 最小値設定
	 * @param max 最大値設定
	 * @param loop 値がループするかどうか
	 * @return カウント数
	 */
	inline int Get_HweelCnt(int min,int max,bool loop = false)	
	{
		m_oldWheelCnt = m_wheelCnt;
		if (loop)
		{
			if (m_wheelCnt < min) { m_wheelCnt = max; }
			if (m_wheelCnt > max) { m_wheelCnt = min; }
		}
		else
		{
			if (m_wheelCnt < min) { m_wheelCnt = min; }
			if (m_wheelCnt > max) { m_wheelCnt = max; }
		}
		return m_wheelCnt;
	}

	/**
	 * @brief 前フレームのホイールのカウント数を取得する
	 * @return 
	 */
	inline int Get_OldHweelCnt() { return m_oldWheelCnt; }

private:
	/**
	 * @brief コンストラクタ
	 * @param hInst
	 * @param cmd
	 */
	WinStartUp(HINSTANCE hInst, int cmd); //コンストラクタ

	/**
	 * @brief 
	 * 
	 * @param hWnd
	 * @param msg
	 * @param wParam
	 * @param lParam
	 * @return 
	 */
	static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


	static inline WinStartUp* m_spInstance;
	static POINT  m_OldMousePos;
	static POINT  m_CurMousePos;

	WNDCLASS	m_wc	  = {};
	HWND		m_hWnd	  = {};
	HINSTANCE	m_hInst	  = {};
	SIZE		m_winSize = {};
	MSG			m_msg	  = {};
	int			m_cmd	  = 0;

	int m_wheelCnt = 0;
	int m_oldWheelCnt = 0;
};



#endif // !__WIN_START_UP__
