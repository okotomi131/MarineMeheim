/*********************************************************************
 * @file   ImageDrawer.cpp
 * @brief  2D画像を汎用的に描画するクラス
 *********************************************************************/

/*
==================================================

インクルード

==================================================
*/
#include "ImageDrawer.h"
#include "../../01_System/Window/WinStartUp.h"
#include "../../01_System/Input/Input.h"
#include "../../02_Component/Shader/Shader.h"
#include "../../02_Component/Sound/Sound.h"

void ImageDrawer::Init()
{
	Add_Component<Shader>()->Load("Assets/Shader/VS_Color.cso","Assets/Shader/PS_Texture.cso");
}

void ImageDrawer::Uninit()
{
	for (auto& sound : m_SoundList)
	{	sound.second->Stop();	}
	m_SoundList.clear();
}

//void ImageDrawer::Update(float deltatime)
//{
//}

//void ImageDrawer::Draw()
//{
//	
//}
