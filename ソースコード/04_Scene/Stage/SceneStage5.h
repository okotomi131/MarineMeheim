/*********************************************************************
 * @file   SceneStage5.h
 * @brief  �X�e�[�W5
 *********************************************************************/
#ifndef __SCENE_STAGE_5_H__
#define __SCENE_STAGE_5_H__
/*
==================================================

�C���N���[�h

==================================================
*/
#include "SceneStageBase.h"

class SceneStage5 : public SceneStageBase
{
	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime) override;
};

#endif // !__SCENE_STAGE_5_H__

