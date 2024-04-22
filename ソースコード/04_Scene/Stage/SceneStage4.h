/*********************************************************************
 * @file   SceneStage4.h
 * @brief  ステージ4
 *********************************************************************/
#ifndef __SCENE_STAGE_4_H__
#define __SCENE_STAGE_4_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "SceneStageBase.h"

class SceneStage4 : public SceneStageBase
{
	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	void Update(float deltatime) override;
};

#endif // !__SCENE_STAGE_4_H__
