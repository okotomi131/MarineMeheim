/*********************************************************************
 * @file   SceneResult.h
 * @brief  リザルトシーン
 *********************************************************************/
#ifndef __SCENE_RESULT_H__
#define __SCENE_RESULT_H__

/*
==================================================

インクルード

==================================================
*/
#include "../SceneBase.h"
class SceneResult : public SceneBase
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	void CreateClearTime();

	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/**
	 * @brief 描画処理
	 */
	void Draw() override;
private:

	bool m_bNextScene = false;
	int m_stageNum = 0;
	float m_clearTime = 0.0f;
	int m_minute = 0;
	int m_second = 0;
	int m_millisecond = 0;
	std::string m_stageName = "";
	std::string m_strMinute = "";
	std::string m_strSecond = "";
	std::string m_strMillisecond = "";

};

#endif // !__SCENE_RESULT_H__


