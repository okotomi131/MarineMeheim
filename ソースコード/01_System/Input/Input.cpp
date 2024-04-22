/*********************************************************************
 * @file   Input.cpp
 * @brief  “ü—Íˆ—
 *********************************************************************/
#include "Input.h"

BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];

void Input::Init()
{
	memset(m_OldKeyState, 0, 256);
	memset(m_KeyState, 0, 256);
}

void Input::Update()
{
	memcpy(m_OldKeyState, m_KeyState, 256);
	GetKeyboardState(m_KeyState);
}

