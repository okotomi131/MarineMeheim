/*********************************************************************
 * @file   TutorialMessage.cpp
 * @brief  チュートリアル用のメッセージを表示する
 *********************************************************************/

/*
==================================================

インクルード

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
	
	//- もしメッセージ最小値より小さい番号が指定されたら範囲内に変更
	if (m_curDrawMessage < -1){	m_curDrawMessage = 0;  }
	//- 最大値より大きい場合は、チュートリアルの操作を可能にさせる
	else if(m_curDrawMessage > m_pDrawMessage.size() - 1)
	{
		//- 表示する必要がないので全て非表示に
		for(int i = 0; i < m_pDrawMessage.size(); i++)
		{ m_pDrawMessage[i]->Set_Color({ 0.0f,0.0f,0.0f,0.0f }); }
		m_bEnd = true;
		return;
	}

	//- 現在の指定メッセージ番号に併せたメッセージを表示
	m_pDrawMessage[m_curDrawMessage]->Set_Pos(m_viewPos);
	//- その他のメッセージは画面外に
	for (int i = 0; i < m_pDrawMessage.size(); i++)
	{
		if (i != m_curDrawMessage)
		{ m_pDrawMessage[i]->Set_Pos({ 9999.9f,9999.9f }); }
	}
}

