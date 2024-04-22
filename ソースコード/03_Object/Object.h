/*********************************************************************
 * @file   Object.h
 * @brief  ゲーム内オブジェクトの基底クラス
 *********************************************************************/

#ifndef __OBJECT_H__
#define __OBJECT_H__
/*
==================================================

インクルード

==================================================
*/
#include <list>
#include <random>

#include "../01_System/DirectX/DirectXRenderer.h"
#include "../01_System/Window/WinStartUp.h"
#include "../01_System/Text/TextDraw.h"

#include "../01_System/Save/DataSave.h"
#include "../02_Component/Component.h"

#define SPRITE_CENTER_POS_X(x) ((SCREEN_WIDTH  / 2.0f) - (x / 2.0f))
#define SPRITE_CENTER_POS_Y(y) ((SCREEN_HEIGHT / 2.0f) - (y / 2.0f))

class Component;

class Object
{
public:
	Object() {};
	virtual ~Object() {};
	virtual void Init()   {};
	virtual void Uninit() {};
	virtual void Update(float deltatime) {};
	virtual void Draw()   {};

	/**
	 * @brief 初期化処理
	 */
	void InitBase();

	/**
	 * @brief 自分のコンポーネントの解放、終了処理
	 */
	void UninitBase();

	/**
	 * @brief 自分のコンポーネントの更新処理、更新処理
	 * @param deltatime
	 */
	void UpdateBase(float deltatime);

	/**
	 * @brief 描画処理
	 * コンポーネント・子オブジェクト・自身の描画処理を行う
	 * @param parentmatrix 親の行列
	 */
	void DrawBase(DirectX::XMFLOAT4X4 parentmatrix);

	/**
	 * @brief 削除処理
	 * @return 削除成功すればtrue
	 */
	bool Destory();

	/*
	==================================================

	ゲッター

	==================================================
	*/

	/**
	 * @brief 座標取得
	 * @return
	 */
	inline DirectX::XMFLOAT3 Get_Pos()  const { return m_pos; }

	/**
	 * @brief 回転情報取得
	 * @return
	 */
	inline DirectX::XMFLOAT3 Get_Rot()  const { return m_rot; }

	/**
	 * @brief 大きさ取得
	 * @return
	 */
	inline DirectX::XMFLOAT3 Get_Size() const { return m_size; }

	/**
	 * @brief 正面ベクトルの取得
	 * @return 
	 */
	DirectX::XMVECTOR Get_vForward() const;

	/**
	 * @brief 上方向ベクトルの取得
	 * @return 
	 */
	DirectX::XMVECTOR Get_vUp() const;

	/**
	 * @brief 下方向ベクトルの取得
	 * @return 
	 */
	DirectX::XMVECTOR Get_vDown() const;

	/**
	 * @brief 自身の最小座標値の取得
	 * @return 
	 */
	DirectX::XMFLOAT3 Get_MinPoint() const;

	/**
	 * @brief 自身の最大座標値の取得
	 * @return 
	 */
	DirectX::XMFLOAT3 Get_MaxPoint() const;

	/**
	 * @brief 自分のワールド行列の取得
	 * @return 
	 */
	DirectX::XMMATRIX Get_WorldMatrix() const;

	/**
	* @brief 自分の名前の取得
	* @return 
	*/
	inline std::string Get_Name() const { return m_name; };


	/*
	==================================================

	セッター

	==================================================
	*/

	/**
	 * @brief 座標の設定
	 * @param pos
	 */
	inline void Set_Pos(const DirectX::XMFLOAT3 &pos) { m_pos = pos; }

	/**
	 * @brief 回転の設定
	 * @param rot
	 */
	inline void Set_Rot(const DirectX::XMFLOAT3 &rot) { m_rot = rot; }

	/**
	 * @brief サイズの設定
	 * @param size
	 */
	inline void Set_Size(const DirectX::XMFLOAT3 &size) { m_size = size; }

	/**
	 * @brief 削除フラグを有効にする
	 */
	inline void Set_Destory() { m_bDestroy = true; };

	/**
	 * @brief 名前の設定
	 */
	inline void Set_Name(const std::string& name) { m_name = name; };

	/*
	==================================================
	
	テンプレート
	
	==================================================
	*/

	/**
	 * @brief Component追加
	 * @return 追加したComponentのポインタ
	 */
	template<typename T>
	T* Add_Component()
	{
		T* comp = new T(this);
		m_component.push_back(comp);
		((Component*)comp)->Init();
		return comp;
	}

	/**
	 * @brief Componentの取得
	 * @return 一致したComponentのポインタ
	 */
	template<typename T>
	T* Get_Component()
	{
		for(Component* comp : m_component)
		{
			if (typeid(*comp) == typeid(T))
			{	return (T*)comp;	}
		}
		return nullptr;
	}


	/**
	 * @brief 同じ型のComponentを全て取得
	 * @return Componentのベクターを返す
	 */
	template<typename T>
	std::vector<T*> Get_Components()
	{
		std::vector <T*> vecComp;
		for (Component* comp : m_component)
		{
			if (typeid(*comp) == typeid(T))
			{
				vecComp.push_back((T*)comp);
			}
		}
		return vecComp;
	}

	//- オブジェクト
	/**
	 * @brief オブジェクトの追加
	 * @return オブジェクトのポインタ
	 */
	template<typename T>
	T* Add_Obj()
	{
		T* child = new T();
		m_childObj.push_back(child);
		child->InitBase();
		return child;
	}

	/**
	 * @brief オブジェクトの取得
	 * @return 型が一致したオブジェクトのポインタ
	 */
	template<typename T>
	T* Get_Obj()
	{
		for (Object* obj : m_childObj)
		{
			if (typeid(*obj) == typeid(T))
			{	return (T*)obj;	}
		}
		return nullptr;
	}

	/**
	 * @brief オブジェクトの取得
	 * @param name オブジェクトの名前
	 * @return 名前が一致したオブジェクトのポインタ
	 */
	template<typename T>
	T* Get_Obj(const std::string& name)
	{
		for (Object* obj : m_childObj)
		{
			if (obj->Get_Name() == name)
			{	return obj;	}
		}
		return nullptr;
	}

	/**
	 * @brief 同じ型のオブジェクトを全て取得
	 * @return オブジェクトのベクターを返す
	 */
	template<typename T>
	std::vector<T*> Get_Objs()
	{
		std::vector<T*> vecObj;
		for (Object* obj : m_childObj)
		{
			if (typeid(*obj) == typeid(T))
			{
				vecObj.push_back((T*)obj);
			}
		}
		return vecObj;
	}

protected:
	std::string m_name = "None";
	DirectX::XMFLOAT3 m_pos = {};
	DirectX::XMFLOAT3 m_rot = {};
	DirectX::XMFLOAT3 m_size = {};
	bool m_bDestroy = false;

	std::list<Component*> m_component;	//自分のコンポーネント一覧
	std::list<Object*>	  m_childObj;	//自分の子供オブジェ一覧
};

#endif // !__OBJECT_H__

