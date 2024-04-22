/*********************************************************************
 * @file   Input.h
 * @brief  入力処理クラス
 *********************************************************************/

#ifndef __INPUT_H__
#define __INPUT_H__

 /*
 ===================================================================

 インクルード

 ===================================================================
 */
#include <Windows.h>
#include "../DirectX/DirectXRenderer.h"


class Input
{
public:
	/**
	 * @brief 初期化
	 */
	static void Init();

	/**
	* @brief 更新
	*/
	static void Update();

	/*
	===================================================================

	ゲッター

	===================================================================
	*/

	/**
	 * @brief キーが押されている間
	 * @param KeyCode キーコード
	 */
	inline static bool Get_KeyPress(BYTE KeyCode)
	{ return (m_KeyState[KeyCode] & 0x80); };

	/**
	 * @brief キーが押された瞬間
	 * @param KeyCode キーコード
	 */
	inline static bool Get_KeyTrigger(BYTE KeyCode)
	{ return (m_KeyState[KeyCode] & 0x80)  && !(m_OldKeyState[KeyCode] & 0x80); };

	/**
	 * @brief キーが離された瞬間
 	 * @param KeyCode キーコード
 	 */
	inline static bool Get_KeyRelease(BYTE KeyCode) 
	{ return !(m_KeyState[KeyCode] & 0x80) && (m_OldKeyState[KeyCode] & 0x80);  };
private:
	static BYTE m_OldKeyState[256]; //前フレームのキー
	static BYTE m_KeyState[256];	//現在のキー
};

#endif // !__INPUT_H__