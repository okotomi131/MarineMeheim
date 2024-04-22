/*********************************************************************
 * @file   DataSave.h
 * @brief  �Z�[�u����(Json���C�u�����g�p)
 *********************************************************************/

#ifndef __DATA_SAVE_H__
#define __DATA_SAVE_H__
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include <string>
#include <fstream>
#include "../Save/Json/json.hpp"
#include "../../01_System/main.h"
using json = nlohmann::json;


class DataSave
{
public:
	/**
	 * @brief �����f�[�^���쐬
	 */
	static void CreateData();

	/**
	 * @brief �Z�[�u����
	 */
	static void Save();

	/**
	 * @brief ���[�h����
	 */
	static void Load();

	/**
	 * @brief �f�[�^��V�����o�^����
	 * @param name �L�[�̖��O
	 * @param data �o�^����f�[�^
	 */
	template<typename T>
	static void Set_Data(const std::string name, const T* data)
	{	
		if (data == nullptr)
		{
			Message::ErrorMessage("�f�[�^�����݂��܂���\n");
			return;
		}

		std::istringstream ss(name);
		std::string token;
		bool isFind = false;
		isFind = name.find('.') != std::string::npos;//��؂蕶���́u.�v�����邩
		//-�@��؂蕶��������ꍇ
		if (isFind)
		{
			while (std::getline(ss, token, '.'))
			{
				if (!token.empty())
				{
					//- �L�[�����݂��Ȃ��ꍇ�͐V�����쐬
					if (!m_jsonData.contains(token))
					{	m_jsonData[token] = json();	}
					//- �Ō�̃L�[�Ƀf�[�^��o�^
					if (token == name.substr(name.find_last_of('.') + 1))
					{	m_jsonData[token] = *data;	}
					else
					{	m_jsonData = m_jsonData[token];	}
				}
			}
		}
		else
		{
			m_jsonData[name] = *data;
		}
		
	}

	/**
	 * @brief �o�^�����f�[�^���擾����
	 * @param name �L�[�̖��O
	 * @return �L�[�ɑΉ������f�[�^
	 */
	template<typename T>
	static T Get_Data(std::string name)
	{	
		json j = m_jsonData;//��ԏ�̊K�w����{������
		std::istringstream ss(name);
		std::string token;
		bool isFind = false;
		isFind = name.find('.') != std::string::npos;//��؂蕶���́u.�v�����邩

		//-�@��؂蕶��������ꍇ
		if (isFind)
		{
			//- ��؂蕶���ŕ���
			while (std::getline(ss, token, '.'))
			{
				/*
				contains�F�L�[�ƈ�v����v�f�����邩���ׂ�
				https://cpprefjp.github.io/reference/map/map/contains.html
				*/
				if(j.contains(token))
				{	j = j[token];	}
				else {
					Message::ErrorMessage("�f�[�^�����݂��܂���\n");
					return 0;
				}
			}
			return j.get<T>();
		}
		//- ��؂蕶�����Ȃ��ꍇ
		else
		{
			//- �f���Ƀf�[�^���擾
			if (m_jsonData[name].is_null()){
				Message::ErrorMessage("�f�[�^�����݂��܂���\n");
				return 0;
			}
			else
			{	return m_jsonData[name].get<T>(); }
		}
	}

private:
	static json m_jsonData;
	static std::string m_jsonName;	//�t�@�C����
	static std::string m_Extension;	//�g���q
	static std::string m_fileName;	//�t�@�C����+�g���q

	//- �X�V�l
	float m_pPlayerHP;
	int   m_StageNum;
};

#endif // !__DATA_SAVE_H__
