/*********************************************************************
 * @file   SceneController.h
 * @brief  シーン管理を行う
 *********************************************************************/
#ifndef __SCENE_CONTROLLER_H__
#define __SCENE_CONTROLLER_H__
 /*
 ==================================================

 インクルード

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
	 * @brief 初期化処理
	 */
	static void Init();

	/**
	 * @brief 終了処理
	 */
	static void Uninit();

	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	static void Update(float deltatime);

	/**
	 * @brief 描画処理
	 */
	static void Draw();

	/*
	==================================================

	セッター

	==================================================
	*/

	/**
	 * @brief シーン状態を変更
	 * @param state 次に変更するシーン
	 */
	static void Set_SceneState(E_SCENE_STATE state);

	/**
	 * @brief シーン内の全ての更新を停止するか
	 * @param bPause true:停止する false:停止しない
	 */
	static inline void Set_Pause(bool bPause) { m_bPause = bPause; }

	/**
	 * @brief シーン内のベース更新を行わない
	 * @param bPause true:停止する false:停止しない
	 */
	static inline void Set_BaseUpdatePause(bool bPause) { m_bBaseUpdate = bPause; }

	/*
	==================================================

	ゲッター

	==================================================
	*/

	/**
	 * @brief 現在のシーンを取得
	 * @return 
	 */
	static inline SceneBase* Get_Scene() { return m_pScene; }

	/**
	 * @brief 現在のシーン状態を取得
	 * @return 
	 */
	static inline E_SCENE_STATE Get_CurState() { return m_curState; }

	/**
	 * @brief 前のシーン状態を取得
	 * @return 
	 */
	static inline E_SCENE_STATE Get_OldState() { return m_oldState; }

	static inline bool Get_Pause() { return m_bPause; }
	
private:
	/**
	 * @brief シーンの変更を行う
	 */
	static void ChangeScene();

	/**
	 * @brief シーンの変更を行う
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

