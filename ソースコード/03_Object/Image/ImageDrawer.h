/*********************************************************************
 * @file   ImageDrawer.h
 * @brief  2D画像を汎用的に描画するクラス
 *********************************************************************/
#ifndef __IMAGE_DRAWER_H__
#define __IMAGE_DRAWER_H__
/*
==================================================

インクルード

==================================================
*/
#include "../Object.h"
#include "../../02_Component/Sprite/Sprite.h"
#include "../../02_Component/Sound/Sound.h"

class ImageDrawer : public Object
{
public:

	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief 終了処理
	 */
	void Uninit() override;

	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	//void Update(float deltatime) override;

	/**
	 * @brief 描画処理
	 */
	//	void Draw() override;

	
	/**
	 * @brief パスから画像を読み込み、描画する
	 * @param fileName   画像のパス
	 * @param backGround 背景かどうか
	 */
	inline void CreateImage(const char* fileName,bool backGround = false)
	{
		Init();
		m_pSprite = Add_Component<Sprite>();

		if (backGround){
			//- 背景なら、画面サイズいっぱいに表示する
			m_pSprite->Init(
				{ SPRITE_CENTER_POS_X(SCREEN_WIDTH),SPRITE_CENTER_POS_Y(SCREEN_HEIGHT) },
				{ SCREEN_WIDTH,SCREEN_HEIGHT},fileName);
		}
		else {
			m_pSprite->Init(
			{ SPRITE_CENTER_POS_X(1.0f),SPRITE_CENTER_POS_Y(1.0f) },
			{ 1.0f,1.0f }, fileName);	
		}
	}

	/**
	 * @brief スプライトに直接座標をセットする
	 * @param pos
	 */
	inline void Set_Pos(const DirectX::XMFLOAT2& pos)
	{	m_pSprite->Set_Pos(pos);	}

	/**
	 * @brief スプライトに直接サイズをセットする
	 * @param size
	 */
	inline void Set_Size(const DirectX::XMFLOAT2& size)
	{	m_pSprite->Set_Size(size);	}

	/**
	 * @brief スプライトに直接回転をセットする
	 * @param rot
	 */
	inline void Set_RotZ(const float& rot)
	{	m_pSprite->Set_Rot(rot);	}
	
	/**
	 * @brief サウンドの追加
	 * @param fileName サウンドのパス
	 * @param keyname サウンドのキー名
	 */
	inline void Add_Sound(const char* fileName,const std::string& keyname)
	{
		m_SoundList.insert(std::make_pair(keyname, Add_Component<Sound>()));
		m_SoundList[keyname]->Load(fileName);
	}

	/**
	 * @brief サウンドの再生
	 * @param keyname サウンドのキー名
	 * @param loop ループ再生するかどうか
	 */
	inline void Play_Sound(const std::string& keyname,const bool& loop = false)
	{	m_SoundList[keyname]->Play(loop);	}

private:
	
	Sprite* m_pSprite = nullptr;
	std::unordered_map<std::string,Sound*> m_SoundList = {};

};

#endif // !__IMAGE_DRAWER_H__


