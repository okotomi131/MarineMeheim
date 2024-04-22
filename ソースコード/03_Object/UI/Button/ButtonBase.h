/*********************************************************************
 * @file   ButtonBase.h
 * @brief  ボタンを作成する
 *********************************************************************/
#ifndef __BUTTON_BASE_H__
#define __BUTTON_BASE_H__
/*
==================================================

インクルード

==================================================
*/
#include "../../Object.h"
#include "../../../02_Component/Sprite/Sprite.h"
#include "../../../02_Component/Sound/Sound.h"
class ButtonBase :public Object
{
public:
	void Load(const char* path);
	void Init()override;
	void Update(float deltatime)override;

	/**
	 * @brief スプライトに直接座標をセットする
	 * @param pos
	 */
	inline void Set_Pos(const DirectX::XMFLOAT2& pos)
	{
		m_pSprite->Set_Pos(pos);
	}

	/**
	 * @brief スプライトに直接サイズをセットする
	 * @param size
	 */
	inline void Set_Size(const DirectX::XMFLOAT2& size)
	{	m_pSprite->Set_Size(size);	}

	/**
	 * @brief ボタンが押されたか
	 * @return 押されていたらtrue
	 */
	bool IsOverlap(bool force = false);

	/**
	 * @brief サウンドの追加
	 * @param fileName サウンドのパス
	 * @param keyname サウンドのキー名
	 */
	inline void Add_Sound(const char* fileName, const std::string keyname)
	{
		m_pSoundList.insert(std::make_pair(keyname, Add_Component<Sound>()));
		m_pSoundList[keyname]->Load(fileName);
	}

	/**
	 * @brief サウンドの再生
	 * @param keyname サウンドのキー名
	 * @param loop ループ再生するかどうか
	 */
	inline void Play_Sound(const std::string keyname, const bool loop = false)
	{
		m_pSoundList[keyname]->Play(loop);
	}

	/**
	 * @brief サウンドを一回だけ鳴らすか
	 * @param bOnceSound
	 */
	inline void Set_OnceSound(bool bOnceSound) { m_bOnceSound = bOnceSound; }

	/**
	 * @brief 一回だけ鳴らすサウンドかどうか
	 * @param bOnceSound 一回だけ鳴らすサウンドならtrue
	 */
	inline bool Get_OnceSound() { return m_bOnceSound; }

	/**
	 * @brief 画面外に配置
	 */
	inline void OutScreen() {	m_pSprite->Set_Pos({9999.9f,9999.9f}); }
private:
	Sprite* m_pSprite = nullptr;
	std::unordered_map<std::string,Sprite*> m_pButtonList = {};
	std::unordered_map<std::string, Sound*> m_pSoundList = {};
	bool m_bOverlap = false;
	bool m_bOnceSound = false;
};

#endif // !__BUTTON_BASE_H__


