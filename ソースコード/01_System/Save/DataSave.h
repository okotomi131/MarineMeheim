/*********************************************************************
 * @file   DataSave.h
 * @brief  セーブ処理(Jsonライブラリ使用)
 *********************************************************************/

#ifndef __DATA_SAVE_H__
#define __DATA_SAVE_H__
 /*
 ==================================================

 インクルード

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
	 * @brief 初期データを作成
	 */
	static void CreateData();

	/**
	 * @brief セーブ処理
	 */
	static void Save();

	/**
	 * @brief ロード処理
	 */
	static void Load();

	/**
	 * @brief データを新しく登録する
	 * @param name キーの名前
	 * @param data 登録するデータ
	 */
	template<typename T>
	static void Set_Data(const std::string name, const T* data)
	{	
		if (data == nullptr)
		{
			Message::ErrorMessage("データが存在しません\n");
			return;
		}

		std::istringstream ss(name);
		std::string token;
		bool isFind = false;
		isFind = name.find('.') != std::string::npos;//区切り文字の「.」があるか
		//-　区切り文字がある場合
		if (isFind)
		{
			while (std::getline(ss, token, '.'))
			{
				if (!token.empty())
				{
					//- キーが存在しない場合は新しく作成
					if (!m_jsonData.contains(token))
					{	m_jsonData[token] = json();	}
					//- 最後のキーにデータを登録
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
	 * @brief 登録したデータを取得する
	 * @param name キーの名前
	 * @return キーに対応したデータ
	 */
	template<typename T>
	static T Get_Data(std::string name)
	{	
		json j = m_jsonData;//一番上の階層から捜索する
		std::istringstream ss(name);
		std::string token;
		bool isFind = false;
		isFind = name.find('.') != std::string::npos;//区切り文字の「.」があるか

		//-　区切り文字がある場合
		if (isFind)
		{
			//- 区切り文字で分割
			while (std::getline(ss, token, '.'))
			{
				/*
				contains：キーと一致する要素があるか調べる
				https://cpprefjp.github.io/reference/map/map/contains.html
				*/
				if(j.contains(token))
				{	j = j[token];	}
				else {
					Message::ErrorMessage("データが存在しません\n");
					return 0;
				}
			}
			return j.get<T>();
		}
		//- 区切り文字がない場合
		else
		{
			//- 素直にデータを取得
			if (m_jsonData[name].is_null()){
				Message::ErrorMessage("データが存在しません\n");
				return 0;
			}
			else
			{	return m_jsonData[name].get<T>(); }
		}
	}

private:
	static json m_jsonData;
	static std::string m_jsonName;	//ファイル名
	static std::string m_Extension;	//拡張子
	static std::string m_fileName;	//ファイル名+拡張子

	//- 更新値
	float m_pPlayerHP;
	int   m_StageNum;
};

#endif // !__DATA_SAVE_H__
