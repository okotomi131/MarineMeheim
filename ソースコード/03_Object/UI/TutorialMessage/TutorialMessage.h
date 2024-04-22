/*********************************************************************
 * @file   TutorialMessage.h
 * @brief  チュートリアル用のメッセージを表示する
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "../../Object.h"
#include "../../../02_Component/Sprite/Sprite.h"
#include "../../../02_Component/Sound/Sound.h"

class TutorialMessage : public Object
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init()override;
	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	void Update(float deltatime)override;

	/**
	 * @brief 現在表示するメッセージ番号を設定
	 * @param num メッセージ番号
	 */
	inline void Set_CurDrawMessage(int num) { m_curDrawMessage = num; }

	/**
	 * @brief メッセージ表示が終了したか
	 * @return 終了すればtrue
	 */
	inline bool Get_IsEnd() { return m_bEnd; }

private:
	bool m_bEnd = false;
	int m_curDrawMessage = 0;
	DirectX::XMFLOAT2 m_viewPos = {};

	std::vector<Sprite*> m_pDrawMessage;
	std::vector<Sound*>  m_pSoundList;
};

