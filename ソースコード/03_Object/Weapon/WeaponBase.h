/*********************************************************************
 * @file   WeaponBase.h
 * @brief  武器の基底クラス
 *********************************************************************/
#ifndef __WEAPON_BASE_H__
#define __WEAPON_BASE_H__

/*
==================================================

インクルード

==================================================
*/
#include "../Object.h"
#include "../Bullet/Bullet.h"

class WeaponBase : public Object
{
public:
	/*
	==================================================

	構造体

	==================================================
	*/
	//- 武器データ
	struct WeaponData
	{
		Bullet::BulletData bulletData = {};	//弾のデータ
		int bulletNum	 = 0;	//弾数
		int multiShotNum = 0;	//同時発射弾数
		float reloadTime = 0.0f;//リロード時間
		float bulletSize = 0.0f;//弾の大きさ
		float rate		 = 0.0f;//射撃レート
		DirectX::XMFLOAT2 SpreadAngle = {};//拡散角度
	};


	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief プレイヤーの攻撃処理
	 * @param deltatime
	 */
	void AttackPlayer(float deltatime);

	/**
	 * @brief 敵の攻撃処理
	 * @param deltatime 
	 * @param enemy
	 */
	void AttackEnemy(float deltatime,class EnemyBase* enemy);
	
	/**
	 * @brief リロード処理
	 * @param deltatime
	 * @return 
	 */
	bool Reload(float deltatime);

	/**
	 * @brief リロードの継続時間をリセット
	 */
	void Reset_CurRateTime() { m_curRateTime = 0.0f; }

	/*
	==================================================

	ゲッター

	==================================================
	*/

	/**
	 * @brief リロードフラグを取得
	 * @return リロード中ならtrue 
	 */
	bool  Get_Reload()	     const { return m_bReload; }

	/**
	 * @brief リロードの経過時間を取得
	 * @return 
	 */
	float Get_CurReloadTime()const { return m_curReloadTime; }
	float Get_ReloadTime()   const { return m_weaponData.reloadTime; }
	int   Get_CurBulletNum() const { return m_curBulletNum; }
	int   Get_MaxBulletNum() const { return m_weaponData.bulletNum; }

	/*
	==================================================

	セッター

	==================================================
	*/

	/**
	 * @brief リロードフラグをセット
	 */
	void Set_Reload() { m_bReload = true; }
protected:
	int   m_curBulletNum;   //残弾数
	float m_curRateTime;	//経過時間
	float m_curReloadTime;	//リロード経過時間
	bool  m_bReload;		//リロード中か
	bool  m_bMultiShot;		//同時発射するか
	class SceneBase* m_pScene = {};
	WeaponData m_weaponData = {};

};

#endif // !__WEAPON_BASE_H__


