/*********************************************************************
 * @file   SceneTitle.h
 * @brief  �^�C�g���V�[��
 *********************************************************************/

#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../SceneBase.h"


class SceneTitle : public SceneBase
{
public:
	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime) override;
	void MoveScene();
private:
	int m_selectNum = 0;
	
};

#endif // !__SCENE_TITLE_H__

