/*********************************************************************
 * @file   Input.h
 * @brief  ���͏����N���X
 *********************************************************************/

#ifndef __INPUT_H__
#define __INPUT_H__

 /*
 ===================================================================

 �C���N���[�h

 ===================================================================
 */
#include <Windows.h>
#include "../DirectX/DirectXRenderer.h"


class Input
{
public:
	/**
	 * @brief ������
	 */
	static void Init();

	/**
	* @brief �X�V
	*/
	static void Update();

	/*
	===================================================================

	�Q�b�^�[

	===================================================================
	*/

	/**
	 * @brief �L�[��������Ă����
	 * @param KeyCode �L�[�R�[�h
	 */
	inline static bool Get_KeyPress(BYTE KeyCode)
	{ return (m_KeyState[KeyCode] & 0x80); };

	/**
	 * @brief �L�[�������ꂽ�u��
	 * @param KeyCode �L�[�R�[�h
	 */
	inline static bool Get_KeyTrigger(BYTE KeyCode)
	{ return (m_KeyState[KeyCode] & 0x80)  && !(m_OldKeyState[KeyCode] & 0x80); };

	/**
	 * @brief �L�[�������ꂽ�u��
 	 * @param KeyCode �L�[�R�[�h
 	 */
	inline static bool Get_KeyRelease(BYTE KeyCode) 
	{ return !(m_KeyState[KeyCode] & 0x80) && (m_OldKeyState[KeyCode] & 0x80);  };
private:
	static BYTE m_OldKeyState[256]; //�O�t���[���̃L�[
	static BYTE m_KeyState[256];	//���݂̃L�[
};

#endif // !__INPUT_H__