/*********************************************************************
 * @file   SceneStage1.h
 * @brief  �X�e�[�W1
 *********************************************************************/
#ifndef __SCENE_STAGE_1_H__
#define __SCENE_STAGE_1_H__
/*
==================================================
 
�C���N���[�h
 
==================================================
*/
#include "SceneStageBase.h"

class SceneStage1 : public SceneStageBase
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


#endif // !__SCENE_STAGE_1_H__