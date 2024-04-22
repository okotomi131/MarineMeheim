/*********************************************************************
 * @file   Object.h
 * @brief  �Q�[�����I�u�W�F�N�g�̊��N���X
 *********************************************************************/

#ifndef __OBJECT_H__
#define __OBJECT_H__
/*
==================================================

�C���N���[�h

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
	 * @brief ����������
	 */
	void InitBase();

	/**
	 * @brief �����̃R���|�[�l���g�̉���A�I������
	 */
	void UninitBase();

	/**
	 * @brief �����̃R���|�[�l���g�̍X�V�����A�X�V����
	 * @param deltatime
	 */
	void UpdateBase(float deltatime);

	/**
	 * @brief �`�揈��
	 * �R���|�[�l���g�E�q�I�u�W�F�N�g�E���g�̕`�揈�����s��
	 * @param parentmatrix �e�̍s��
	 */
	void DrawBase(DirectX::XMFLOAT4X4 parentmatrix);

	/**
	 * @brief �폜����
	 * @return �폜���������true
	 */
	bool Destory();

	/*
	==================================================

	�Q�b�^�[

	==================================================
	*/

	/**
	 * @brief ���W�擾
	 * @return
	 */
	inline DirectX::XMFLOAT3 Get_Pos()  const { return m_pos; }

	/**
	 * @brief ��]���擾
	 * @return
	 */
	inline DirectX::XMFLOAT3 Get_Rot()  const { return m_rot; }

	/**
	 * @brief �傫���擾
	 * @return
	 */
	inline DirectX::XMFLOAT3 Get_Size() const { return m_size; }

	/**
	 * @brief ���ʃx�N�g���̎擾
	 * @return 
	 */
	DirectX::XMVECTOR Get_vForward() const;

	/**
	 * @brief ������x�N�g���̎擾
	 * @return 
	 */
	DirectX::XMVECTOR Get_vUp() const;

	/**
	 * @brief �������x�N�g���̎擾
	 * @return 
	 */
	DirectX::XMVECTOR Get_vDown() const;

	/**
	 * @brief ���g�̍ŏ����W�l�̎擾
	 * @return 
	 */
	DirectX::XMFLOAT3 Get_MinPoint() const;

	/**
	 * @brief ���g�̍ő���W�l�̎擾
	 * @return 
	 */
	DirectX::XMFLOAT3 Get_MaxPoint() const;

	/**
	 * @brief �����̃��[���h�s��̎擾
	 * @return 
	 */
	DirectX::XMMATRIX Get_WorldMatrix() const;

	/**
	* @brief �����̖��O�̎擾
	* @return 
	*/
	inline std::string Get_Name() const { return m_name; };


	/*
	==================================================

	�Z�b�^�[

	==================================================
	*/

	/**
	 * @brief ���W�̐ݒ�
	 * @param pos
	 */
	inline void Set_Pos(const DirectX::XMFLOAT3 &pos) { m_pos = pos; }

	/**
	 * @brief ��]�̐ݒ�
	 * @param rot
	 */
	inline void Set_Rot(const DirectX::XMFLOAT3 &rot) { m_rot = rot; }

	/**
	 * @brief �T�C�Y�̐ݒ�
	 * @param size
	 */
	inline void Set_Size(const DirectX::XMFLOAT3 &size) { m_size = size; }

	/**
	 * @brief �폜�t���O��L���ɂ���
	 */
	inline void Set_Destory() { m_bDestroy = true; };

	/**
	 * @brief ���O�̐ݒ�
	 */
	inline void Set_Name(const std::string& name) { m_name = name; };

	/*
	==================================================
	
	�e���v���[�g
	
	==================================================
	*/

	/**
	 * @brief Component�ǉ�
	 * @return �ǉ�����Component�̃|�C���^
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
	 * @brief Component�̎擾
	 * @return ��v����Component�̃|�C���^
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
	 * @brief �����^��Component��S�Ď擾
	 * @return Component�̃x�N�^�[��Ԃ�
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

	//- �I�u�W�F�N�g
	/**
	 * @brief �I�u�W�F�N�g�̒ǉ�
	 * @return �I�u�W�F�N�g�̃|�C���^
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
	 * @brief �I�u�W�F�N�g�̎擾
	 * @return �^����v�����I�u�W�F�N�g�̃|�C���^
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
	 * @brief �I�u�W�F�N�g�̎擾
	 * @param name �I�u�W�F�N�g�̖��O
	 * @return ���O����v�����I�u�W�F�N�g�̃|�C���^
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
	 * @brief �����^�̃I�u�W�F�N�g��S�Ď擾
	 * @return �I�u�W�F�N�g�̃x�N�^�[��Ԃ�
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

	std::list<Component*> m_component;	//�����̃R���|�[�l���g�ꗗ
	std::list<Object*>	  m_childObj;	//�����̎q���I�u�W�F�ꗗ
};

#endif // !__OBJECT_H__

