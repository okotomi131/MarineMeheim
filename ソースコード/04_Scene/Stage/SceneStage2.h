/*********************************************************************
 * @file   SceneStage2.h
 * @brief  �X�e�[�W2
 *********************************************************************/
#ifndef __SCENE_STAGE_2_H__
#define __SCENE_STAGE_2_H__
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "SceneStageBase.h"

class SceneStage2 : public SceneStageBase
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

#endif // !__SCENE_STAGE_2_H__
