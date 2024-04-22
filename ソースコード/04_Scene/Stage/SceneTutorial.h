/*********************************************************************
 * @file   SceneTutorial.h
 * @brief  チュートリアルシーン
 *********************************************************************/
#ifndef __SCENE_TUTORIAL_H__
#define __SCENE_TUTORIAL_H__
/*
==================================================

インクルード

==================================================
*/
#include "SceneStageBase.h"

class SceneTutorial : public SceneStageBase
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
	void DrawTutorial(float deltatime);
private:
	int m_tutorialStep = 0;
	std::vector<class ButtonBase*> m_pButtonList;
};

#endif // !__SCENE_TUTORIAL_H__


