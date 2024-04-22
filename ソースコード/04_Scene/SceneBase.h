/*
	SceneBase.h
	シーンベース
*/
#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include <array>
#include <list>
#include <vector>
#include "../01_System/Save/DataSave.h"
#include "../03_Object/Object.h"
#include "../03_Object/Fade/Fade.h"

class SceneBase
{
public:
	SceneBase() {};
	virtual ~SceneBase() {};

	virtual void Init()		{};
	virtual void Uninit()	{};
	virtual void Update(float deltatime)	{};
	virtual void Draw()		{};

	void InitBase();
	void UninitBase();
	void UpdateBase(float deltatime);
	void DrawBase();

	//- テンプレート
	template <typename T>
	T* Add_Object(int drawnum = 1)
	{
		T* obj = new T();
		m_Objects[drawnum].push_back(obj);	//指定した要素数のリストに追加
		obj ->Init();
		return obj;
	}

	template <typename T>
	T* Get_Object()
	{
		for (std::list objs : m_Objects) {
			for (Object* obj : objs) {
				if (typeid(*obj) == typeid(T)) { return (T*)obj; }
			}
		}
		return nullptr;
	}

	template<typename T>
	T* Get_Object(const std::string& name)
	{
		for (std::list objs : m_Objects) {
			for (Object* obj : objs) {
				if (typeid(*obj) == typeid(T) &&obj->Get_Name() == name)
				{ return (T*)obj; }
			}
		}
		return nullptr;
	}

	template<typename T>
	T* Get_BaseObject()
	{
		for (std::list objs : m_Objects) {
			for (Object* obj : objs) {
				T* baseObj = dynamic_cast<T*>(obj);
				if (baseObj != nullptr) { return baseObj; }
			}
		}
		return nullptr;
	}



	template <typename T>
	std::vector<T*> Get_Objects()
	{
		std::vector<T*> vecObj;
		for (auto& objectList : m_Objects)
		{
			for (Object* obj : objectList)
			{
				if (typeid(*obj) == typeid(T))
				{
					vecObj.push_back((T*)obj);
				}
			}
		}
		return vecObj;
	}

	template<typename T>
	std::vector<T*> Get_Objects(const std::string& name)
	{
		std::vector<T*> vecObj;
		for (auto& objectList : m_Objects){
			for (Object* obj : objectList){
				if (typeid(*obj) == typeid(T) && obj->Get_Name() == name)
				{	vecObj.push_back((T*)obj);	}
			}
		}
		return vecObj;
	}

	template <typename T>
	std::vector<T*> Get_BaseObjects()
	{
		std::vector<T*> vecObj;
		for (auto& objectList : m_Objects)
		{
			for (Object* obj : objectList)
			{
				T* baseObj = dynamic_cast<T*>(obj);
				if (baseObj != nullptr)
				{
					vecObj.push_back(baseObj);
				}
			}
		}
		return vecObj;
	}

protected:
	std::array<std::list<Object*>, 5> m_Objects; //リストを複数し、描画順として使用
	class Fade* m_Fade = {};

};


#endif // !__SCENE_BASE_H__

