/*********************************************************************
 * @file   SceneTutorial.h
 * @brief  �`���[�g���A���V�[��
 *********************************************************************/
#ifndef __SCENE_TUTORIAL_H__
#define __SCENE_TUTORIAL_H__
/*
==================================================

�C���N���[�h

==================================================
*/
#include "SceneStageBase.h"

class SceneTutorial : public SceneStageBase
{
public:
	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �I������
	 * @param deltatime
	 */
	void Update(float deltatime) override;
	void DrawTutorial(float deltatime);
private:
	int m_tutorialStep = 0;
	std::vector<class ButtonBase*> m_pButtonList;
};

#endif // !__SCENE_TUTORIAL_H__


