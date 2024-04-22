/*********************************************************************
 * @file   SceneController.h
 * @brief  �V�[���Ǘ����s��
 *********************************************************************/
#ifndef __SCENE_CONTROLLER_H__
#define __SCENE_CONTROLLER_H__
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "SceneBase.h"

class SceneController
{
public:
	enum E_SCENE_STATE
	{
		None = -1,
		Title,
		Result,
		Select,
		Tutorial,
		Stage1,
		Stage2,
		Stage3,
		Stage4,
		Stage5,

		Max
	};

	/**
	 * @brief ����������
	 */
	static void Init();

	/**
	 * @brief �I������
	 */
	static void Uninit();

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	static void Update(float deltatime);

	/**
	 * @brief �`�揈��
	 */
	static void Draw();

	/*
	==================================================

	�Z�b�^�[

	==================================================
	*/

	/**
	 * @brief �V�[����Ԃ�ύX
	 * @param state ���ɕύX����V�[��
	 */
	static void Set_SceneState(E_SCENE_STATE state);

	/**
	 * @brief �V�[�����̑S�Ă̍X�V���~���邩
	 * @param bPause true:��~���� false:��~���Ȃ�
	 */
	static inline void Set_Pause(bool bPause) { m_bPause = bPause; }

	/**
	 * @brief �V�[�����̃x�[�X�X�V���s��Ȃ�
	 * @param bPause true:��~���� false:��~���Ȃ�
	 */
	static inline void Set_BaseUpdatePause(bool bPause) { m_bBaseUpdate = bPause; }

	/*
	==================================================

	�Q�b�^�[

	==================================================
	*/

	/**
	 * @brief ���݂̃V�[�����擾
	 * @return 
	 */
	static inline SceneBase* Get_Scene() { return m_pScene; }

	/**
	 * @brief ���݂̃V�[����Ԃ��擾
	 * @return 
	 */
	static inline E_SCENE_STATE Get_CurState() { return m_curState; }

	/**
	 * @brief �O�̃V�[����Ԃ��擾
	 * @return 
	 */
	static inline E_SCENE_STATE Get_OldState() { return m_oldState; }

	static inline bool Get_Pause() { return m_bPause; }
	
private:
	/**
	 * @brief �V�[���̕ύX���s��
	 */
	static void ChangeScene();

	/**
	 * @brief �V�[���̕ύX���s��
	 */
	template<typename T>
	static void Set_Scene()
	{
		if (m_pScene != nullptr)
		{
			m_pScene->UninitBase();
			Delete_and_Null<>(m_pScene, "m_pScene");
		}
		m_pScene = new T();
		m_pScene->InitBase();
	}

	static E_SCENE_STATE  m_curState;
	static E_SCENE_STATE  m_nextState;
	static E_SCENE_STATE  m_oldState;
	static SceneBase*	 m_pScene;
	static bool			 m_bPause;
	static bool			 m_bBaseUpdate;
	static bool			 m_bOncePauseUpdate;
};


#endif // !__SCENE_CONTROLLER_H__

