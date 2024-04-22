/*********************************************************************
 * @file   TutorialMessage.cpp
 * @brief  �`���[�g���A���p�̃��b�Z�[�W��\������
 *********************************************************************/

/*
==================================================

�C���N���[�h

==================================================
*/
#include "TutorialMessage.h"

void TutorialMessage::Init()
{
	DirectX::XMFLOAT2 size = { 700.0f,438.0f };
	m_viewPos = { SPRITE_CENTER_POS_X(size.x),SPRITE_CENTER_POS_Y(size.y) };
	DirectX::XMFLOAT2 pos = {9999.9f,9999.9f};
	
	int messageNum = 7;
	for (int i = 0; i < messageNum; i++)
	{
		Sprite* sp = Add_Component<Sprite>();
		std::string path = "Assets/Texture/UI/";
		std::string fileName = "Description" + std::to_string(i + 1) + ".png";
		path += fileName;
		sp->Init(pos, size,path.c_str());
		m_pDrawMessage.push_back(sp);
	}

}

void TutorialMessage::Update(float deltatime)
{
	
	//- �������b�Z�[�W�ŏ��l��菬�����ԍ����w�肳�ꂽ��͈͓��ɕύX
	if (m_curDrawMessage < -1){	m_curDrawMessage = 0;  }
	//- �ő�l���傫���ꍇ�́A�`���[�g���A���̑�����\�ɂ�����
	else if(m_curDrawMessage > m_pDrawMessage.size() - 1)
	{
		//- �\������K�v���Ȃ��̂őS�Ĕ�\����
		for(int i = 0; i < m_pDrawMessage.size(); i++)
		{ m_pDrawMessage[i]->Set_Color({ 0.0f,0.0f,0.0f,0.0f }); }
		m_bEnd = true;
		return;
	}

	//- ���݂̎w�胁�b�Z�[�W�ԍ��ɕ��������b�Z�[�W��\��
	m_pDrawMessage[m_curDrawMessage]->Set_Pos(m_viewPos);
	//- ���̑��̃��b�Z�[�W�͉�ʊO��
	for (int i = 0; i < m_pDrawMessage.size(); i++)
	{
		if (i != m_curDrawMessage)
		{ m_pDrawMessage[i]->Set_Pos({ 9999.9f,9999.9f }); }
	}
}

