/*********************************************************************
 * @file   SceneStage3.h
 * @brief  �X�e�[�W3
 *********************************************************************/
#ifndef __SCENE_STAGE_3_H__
#define __SCENE_STAGE_3_H__
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "SceneStageBase.h"

class SceneStage3 : public SceneStageBase
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

#endif // !__SCENE_STAGE_3_H__
