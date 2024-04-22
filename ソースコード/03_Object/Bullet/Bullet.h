/*********************************************************************
 * @file   Bullet.h
 * @brief  弾
 *********************************************************************/
#ifndef __BULLET_H__
#define __BULLET_H__

/*
==================================================

インクルード

==================================================
*/
#include "../Object.h"

class Bullet : public Object
{
public:

	/*
	==================================================

	列挙体

	==================================================
	*/
	//- 弾の種類
	enum class E_TAG_TYPE
	{
		None,
		Player,
		Enemy,
	};

	/*
	==================================================

	構造体

	==================================================
	*/
	//- 弾に含まれるデータ
	struct BulletData
	{
		float speed = 0.0f;	//弾速
		float damage = 10.0f;	//ダメージ
		float range = 1000.0f;	//有効射程距離
	};

	/**
	 * @brief モデルの読み込み
	 */
	static void Load();

	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/*
	==================================================

	ゲッター

	==================================================
	*/

	/**
	 * @brief 削除フラグの取得
	 * @return 削除予定ならtrue
	 */
	bool Get_Destory() const { return m_bDestroy; }

	/**
	 * @brief 弾が持つダメージの取得
	 * @return  ダメージ値
	 */
	float Get_Damage() const { return m_bulletData.damage; }

	/**
	 * @brief 弾の種類を取得
	 * @return タグ
	 */
	E_TAG_TYPE Get_Tag() const	 { return m_tag; }

	/*
	==================================================

	セッター

	==================================================
	*/
	/**
	 * @brief タグを設定する
	 * @param tag タグ列挙体
	 */
	void Set_Tag(const E_TAG_TYPE tag)  { m_tag = tag; }

	/**
	 * @brief 弾が進む方向を設定する
	 * @param dir 方向
	 */
	void Set_Direction(const DirectX::XMFLOAT3& dir) { m_direction = dir; }

	/**
	* @brief 弾のデータを設定する
	* @param data 弾のデータ
	*/
	void Set_BulletData(const BulletData& data) { m_bulletData = data; }

private:
	DirectX::XMFLOAT3 m_direction;
	
	BulletData m_bulletData;

	float m_deleteTime = 10.0f;	//削除時間
	float m_curTime = 0.0f;		//経過時間

	E_TAG_TYPE m_tag = E_TAG_TYPE::None;
};

#endif // !__BULLET_H__

