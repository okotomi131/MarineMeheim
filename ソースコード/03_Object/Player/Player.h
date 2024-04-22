/*********************************************************************
 * @file   Player.h
 * @brief  プレイヤーの処理を行うクラス
 *********************************************************************/

#ifndef __PLAYER_H__
#define __PLAYER_H__

 /*
 ==================================================

 インクルード

 ==================================================
 */

#include "../Object.h"
#include "../Weapon/WeaponBase.h"
#include "../../02_Component/HP/HPBase.h"
#include "../../02_Component/Sound/Sound.h"

class Player : public Object
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief 更新処理
	 * @param deltatime デルタタイム
	 */
	void Update(float deltatime) override;

	/**
	 * @brief 終了処理
	 */
	void Uninit() override;

	/*
	==================================================

	セッター

	==================================================
	*/

	/**
	 * @brief 移動量を設定する
	 */
	inline void Set_Movement(DirectX::XMFLOAT3 movement) { m_movement = movement; };

	/**
	 * @brief 移動制限座標を設定する
	 */
	inline void Set_LimitPos(DirectX::XMFLOAT2 pos) { m_LimitPos = pos; };

	
	/**
	 * @brief スタミナを設定する
	 */
	inline void StaminaRecovery(float stamina) 
	{
		if (m_Stamina >= STAMINA_MAX) 
		{	return;		}
		m_Stamina += stamina; 
	};

	inline void SoundPlay(std::string name)
	{
		if (m_SoundList.find(name) != m_SoundList.end())
		{
			m_SoundList[name]->Play();
		}
	};

	/*
	==================================================

	ゲッター

	==================================================
	*/

	WeaponBase* Get_Weapon();
	inline DirectX::XMFLOAT3 Get_Movement() { return m_movement; };
	inline DirectX::XMFLOAT3 Get_OldPos()	{ return m_oldPos; };
	inline float Get_Stamina()				{ return m_Stamina; };
	inline float Get_MaxStamina()			{ return STAMINA_MAX; };
	inline bool Get_IsMove() const { return m_movement.x != 0.0f || m_movement.z != 0.0f; };
	inline bool Get_IsDead() const { return m_bDead; };
private:
	/**
	 * @brief 攻撃処理
	 * @param deltatime デルタタイム
	 */
	void Attack(float deltatime);

	/**
	 * @brief マウス移動に併せて回転する
	 * @param deltatime デルタタイム
	 */
	void Rotation(float deltatime);

	/**
	 * @brief 移動処理
	 * @param deltatime デルタタイム
	 */
	void Move(float deltatime);

	/**
	 * @brief 回避処理
	 * @param deltatime デルタタイム
	 */
	void Slide(float deltatime);


	/*
	==================================================

	定数

	==================================================
	*/
	const float SLIDE_DURATION = 0.5f;	//スライディング時間
	const float SLIDE_DISTANCE = 5.0f;	//スライディング距離
	const float STAMINA_MAX = 100.0f;	//スタミナ最大値
	const float STAMINA_CONSUMPTION = 20.0f;	//スタミナ消費量
	const float STAMINA_CONSUMPTION_RUN = 0.5f;	//ダッシュ時のスタミナ消費量
	const float MIN_STAMINA_AMOUNT_RUN = 20.0f; //ダッシュできるスタミナの最低量
	const float INIT_MOVE_SPEED = 10.0f;	//移動速度

	//- サウンド
	class Sound* m_Sound = nullptr;

	//- 移動
	float m_MoveSpeed = INIT_MOVE_SPEED;
	float m_RunSpeed = 3.0f;
	DirectX::XMFLOAT3 m_movement = {};
	DirectX::XMFLOAT3 m_fForward = {};//前方ベクトル
	DirectX::XMFLOAT3 m_oldPos   = {};

	//- 回転
	POINT m_OldMousePos = {};
	DirectX::XMFLOAT3 m_fRight = {};//横ベクトル

	float m_JumpForce	= 0.5f;
	float m_Resistor	= 0.15f;
	float m_Gravity		= 0.1f;

	//- 回避
	bool  m_bSlideRight = false;
	bool  m_bSlideLeft = false;
	float m_SlideTime = 0.0f;
	DirectX::XMFLOAT3 m_SlideDir = {};

	//- スタミナ
	float m_Stamina = 0.0f;
	bool m_bStaminaRecovery = false;

	//- 移動制限座標
	DirectX::XMFLOAT2 m_LimitPos = { 999.9f, 999.9f };

	//- サウンド
	std::unordered_map<std::string, class Sound*> m_SoundList = {};

	//- 死亡
	bool m_bDead = false;

	//- デバック
	bool m_bGodMode = false;
};


#endif // !__PLAYER_H__
