/*********************************************************************
 * @file   SceneResult.h
 * @brief  ���U���g�V�[��
 *********************************************************************/
#ifndef __SCENE_RESULT_H__
#define __SCENE_RESULT_H__

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../SceneBase.h"
class SceneResult : public SceneBase
{
public:
	/**
	 * @brief ����������
	 */
	void Init() override;

	void CreateClearTime();

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/**
	 * @brief �`�揈��
	 */
	void Draw() override;
private:

	bool m_bNextScene = false;
	int m_stageNum = 0;
	float m_clearTime = 0.0f;
	int m_minute = 0;
	int m_second = 0;
	int m_millisecond = 0;
	std::string m_stageName = "";
	std::string m_strMinute = "";
	std::string m_strSecond = "";
	std::string m_strMillisecond = "";

};

#endif // !__SCENE_RESULT_H__


