/*********************************************************************
 * @file   SceneStage4.h
 * @brief  �X�e�[�W4
 *********************************************************************/
#ifndef __SCENE_STAGE_4_H__
#define __SCENE_STAGE_4_H__
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "SceneStageBase.h"

class SceneStage4 : public SceneStageBase
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

#endif // !__SCENE_STAGE_4_H__
