/*********************************************************************
 * @file   SceneStage2.h
 * @brief  ステージ2
 *********************************************************************/
#ifndef __SCENE_STAGE_2_H__
#define __SCENE_STAGE_2_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "SceneStageBase.h"

class SceneStage2 : public SceneStageBase
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

#endif // !__SCENE_STAGE_2_H__
