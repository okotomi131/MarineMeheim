/*********************************************************************
 * @file   Component.h
 * @brief  �R���|�[�l���g
 *********************************************************************/

#ifndef __CONPONENT_H__
#define __CONPONENT_H__

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../01_System/DirectX/DirectXRenderer.h"
#include "../03_Object/Object.h"

class Object;

class Component
{
public:

	/**
	 * @brief �f�t�H���g�R���X�g���N�^
	 */
	Component() = delete;

	/**
	 * @brief �R���X�g���N�^
	 * @param obj �e�̃I�u�W�F�N�g
	 */
	Component(Object* obj) { m_parentObj = obj; }

	/**
	 * @brief ���O��o�^
	 * @param name
	 */
	void Set_ComponentName(const std::string name) { m_compName = name; }

	/**
	 * @brief ���O���擾
	 * @return ���O
	 */
	std::string Get_ComponentName() const {return m_compName; }

	virtual ~Component()  {};
	virtual void Init()   {};
	virtual void Uninit() {};
	virtual void Update(float DeltaTime) {};
	virtual void Draw()   {};

protected:
	std::string m_compName = "None";		//�R���|�[�l���g�̖��O
	class Object* m_parentObj = nullptr;	//�e�̃I�u�W�F�N�g
};

#endif // !__CONPONENT_H__
