/*********************************************************************
 * @file   HPBase.h
 * @brief  HP処理
 *********************************************************************/

#ifndef _HP_BASE_H__
#define _HP_BASE_H__

/*
==================================================

インクルード

==================================================
*/
#include "../Component.h"

class HPBase : public Component
{
public:
	using Component::Component;

	/*
	==================================================

	構造体

	==================================================
	*/
	struct HpData
	{
		float curHp;
		float maxHp;
	};

	/**
	 * @brief 体力のリセットを行う
	 */
	void ResetHP() { m_curHP = m_MaxHP; };

	/**
	 * @brief 体力のダメージ処理を行う
	 */
	void Damage(float damage) { if (m_curHP > 0) { m_curHP -= damage; } };

	/**
	 * @brief 回復
	 * @param heal 回復量
	 */
	void Heal(float heal);

	/*
	==================================================
	
	ゲッター・セッター
	
	==================================================
	*/

	/**
	 * @brief 体力データの取得
	 * @return HpData 体力データ
	 */
	HpData Get_HpData() { return { m_curHP,m_MaxHP }; };

	/**
	 * @brief 体力の設定
	 */
	void Set_MaxHP(float maxHp) { m_MaxHP = maxHp; m_curHP = m_MaxHP;};
protected:
	float m_curHP = 0.0f;
	float m_MaxHP = 10.0f;
};


#endif // !_HP_BASE_H__
