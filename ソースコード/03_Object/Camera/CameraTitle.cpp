/*********************************************************************
 * @file   CameraTitle.cpp
 * @brief　タイトル画面のカメラ
 *********************************************************************/

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "CameraTitle.h"
#include "../../01_System/Window/WinStartUp.h"
#include "../../01_System/Input/Input.h"
#include "../../02_Component/Sprite/Sprite.h"
#include "../../02_Component/Shader/Shader.h"
#include <random>
void CameraTitle::Init()
{
	CameraBase::Init();
	m_pos = { 10.0f,5.5f,-15.0f };
	m_target = { 0.0f,3.0f,0.0f };
	m_up = { 0.0f,1.0f,0.0f };

	m_startPos = m_pos;
	m_endPos = { -10.0f,5.5f,-35.0f };
	m_startTarget = m_target;
	m_endTarget = { 0.0f,3.0f,0.0f };
	m_easingTime = 5.0f;
	m_curTime = 0.0f;
	m_bEndMove = false;
}

void CameraTitle::Update(float deltatime)
{
}

void CameraTitle::Draw()
{
	CameraBase::Draw();
}
