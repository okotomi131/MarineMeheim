/*********************************************************************
 * @file   SceneTitle.h
 * @brief  タイトルシーン
 *********************************************************************/

#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

/*
==================================================

インクルード

==================================================
*/
#include "../SceneBase.h"


class SceneTitle : public SceneBase
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	void Update(float deltatime) override;
	void MoveScene();
private:
	int m_selectNum = 0;
	
};

#endif // !__SCENE_TITLE_H__

