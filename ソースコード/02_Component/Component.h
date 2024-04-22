/*********************************************************************
 * @file   Component.h
 * @brief  コンポーネント
 *********************************************************************/

#ifndef __CONPONENT_H__
#define __CONPONENT_H__

/*
==================================================

インクルード

==================================================
*/
#include "../01_System/DirectX/DirectXRenderer.h"
#include "../03_Object/Object.h"

class Object;

class Component
{
public:

	/**
	 * @brief デフォルトコンストラクタ
	 */
	Component() = delete;

	/**
	 * @brief コンストラクタ
	 * @param obj 親のオブジェクト
	 */
	Component(Object* obj) { m_parentObj = obj; }

	/**
	 * @brief 名前を登録
	 * @param name
	 */
	void Set_ComponentName(const std::string name) { m_compName = name; }

	/**
	 * @brief 名前を取得
	 * @return 名前
	 */
	std::string Get_ComponentName() const {return m_compName; }

	virtual ~Component()  {};
	virtual void Init()   {};
	virtual void Uninit() {};
	virtual void Update(float DeltaTime) {};
	virtual void Draw()   {};

protected:
	std::string m_compName = "None";		//コンポーネントの名前
	class Object* m_parentObj = nullptr;	//親のオブジェクト
};

#endif // !__CONPONENT_H__
