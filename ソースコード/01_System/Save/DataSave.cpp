/*********************************************************************
 * @file   DataSave.cpp
 * @brief  �f�[�^�̕ۑ�(Json���C�u�����g�p)
 *********************************************************************/

/*
==================================================

�C���N���[�h

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

�萔

==================================================
*/
const static float INIT_PLAYER_HP = 200.0f;	//�v���C���[HP
const static int   INIT_CLEAR_STAGE_NUM = 0;//�N���A�σX�e�[�W�ԍ�


void DataSave::Save()
{
	std::fstream file;
	file.open(m_fileName, std::ios::out);
	file << m_jsonData.dump() << std::endl;
	file.close();
	Message::DebugLog("�t�@�C���̕ۑ��ɐ������܂��� \n");
}

void DataSave::Load()
{
	//- �t�@�C���̓ǂݍ���
	std::ifstream file(m_fileName);
	if (file.good())
	{	
		file >> m_jsonData;	
		Message::DebugLog("�t�@�C���̓ǂݍ��݂ɐ������܂��� \n");
	}
	else
	{	
		//- �ǂݍ��݂Ȃ���Ώ�����
		CreateData();
		Message::ErrorMessage("�V�K�t�@�C�����쐬���܂� \n");	 
	}
}

void DataSave::CreateData()
{
	//- �f�[�^������
	//�v���C���[
	m_jsonData["PlayerHP"] = INIT_PLAYER_HP;
	//�X�e�[�W
	m_jsonData["ClearStageNum"] = INIT_CLEAR_STAGE_NUM;

	Save();

}