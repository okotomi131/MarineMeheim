/*********************************************************************
 * @file   Fade.h
 * @brief  フェード
 *********************************************************************/
#ifndef __FADE_H__
#define __FADE_H__

/*
==================================================

インクルード

==================================================
*/
#include "../Object.h"

class Fade : public Object
{
public:
	/*
	==================================================

	列挙体

	==================================================
	*/
	enum class E_FADE_STATE
	{
		Stop,
		In,
		Out,
		Finish,

		Max,
	};

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
	 * @brief フェードインの設定
	 */
	void FadeIn()  { m_alpha = 1.0f; m_state = E_FADE_STATE::In; };

	/**
	 * @brief フェードアウトの設定
	 */
	void FadeOut() { m_alpha = 0.0f; m_state = E_FADE_STATE::Out; };

	/**
	 * @brief 現在のフェードの状態を取得
	 * @return 
	 */
	E_FADE_STATE Get_State();

private:
	float m_alpha = 0.0f;
	float m_speed = 0.035f;
	E_FADE_STATE m_state = E_FADE_STATE::Stop;
};

#endif // !__FADE_H__

