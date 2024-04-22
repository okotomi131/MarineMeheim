/*********************************************************************
 * @file   DataSave.cpp
 * @brief  データの保存(Jsonライブラリ使用)
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "DataSave.h"
#include "../main.h"
#include "../../03_Object/Weapon/WeaponBase.h"

json DataSave::m_jsonData;
std::string DataSave::m_jsonName  = "SaveData";
std::string DataSave::m_Extension = ".json";
std::string DataSave::m_fileName  = "SaveData.json";

/*
==================================================

定数

==================================================
*/
const static float INIT_PLAYER_HP = 200.0f;	//プレイヤーHP
const static int   INIT_CLEAR_STAGE_NUM = 0;//クリア済ステージ番号


void DataSave::Save()
{
	std::fstream file;
	file.open(m_fileName, std::ios::out);
	file << m_jsonData.dump() << std::endl;
	file.close();
	Message::DebugLog("ファイルの保存に成功しました \n");
}

void DataSave::Load()
{
	//- ファイルの読み込み
	std::ifstream file(m_fileName);
	if (file.good())
	{	
		file >> m_jsonData;	
		Message::DebugLog("ファイルの読み込みに成功しました \n");
	}
	else
	{	
		//- 読み込みなければ初期化
		CreateData();
		Message::ErrorMessage("新規ファイルを作成します \n");	 
	}
}

void DataSave::CreateData()
{
	//- データ初期化
	//プレイヤー
	m_jsonData["PlayerHP"] = INIT_PLAYER_HP;
	//ステージ
	m_jsonData["ClearStageNum"] = INIT_CLEAR_STAGE_NUM;

	Save();

}