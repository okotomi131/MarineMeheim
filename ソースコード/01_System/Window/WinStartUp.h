/*********************************************************************
 * @file   WinStartUp.h
 * @brief  �E�B���h�E�̐ݒ�
 *********************************************************************/
#ifndef __WIN_START_UP_H__
#define __WIN_START_UP_H__
/*
==================================================

�C���N���[�h

==================================================
*/
#include <Windows.h>
#include "../main.h"

/*
==================================================

�萔

==================================================
*/
static const LONG SCREEN_WIDTH  = 1280;		//�E�B���h�E�T�C�Y
static const LONG SCREEN_HEIGHT = 720;
static const char*  MENU_NAME	 = "App";	//���j���[�\
static const char*  CLASS_NAME	 = "�}�������w�C��";	//�E�B���h�E��

#define GET_WIN WinStartUp::Get_Instance()

class WinStartUp
{
public:
	//- �\����
	struct Float2
	{
		float x;
		float y;
	};

	//- �V���O���g���֘A
	/**
	 * @brief �C���X�^���X�쐬
	 * @param hInst
	 * @param cmd
	 */
	static void CreateInstance(HINSTANCE hInst, int cmd);

	/**
	 * @brief �C���X�^���X�폜
	 */
	static void DeleteInstance() { Delete_and_Null<>(m_spInstance, "m_spInstance"); }

	/**
	 * @brief �C���X�^���X�擾
	 * @return 
	 */
	static WinStartUp& Get_Instance() { return *m_spInstance; }

	/**
	 * @brief ����������
	 * @return 
	 */
	HRESULT Init();

	/**
	 * @brief ���b�Z�[�W���[�v
	 * @return 
	 */
	bool	MsgLoop();

	/**
	 * @brief �I������
	 */
	void	Uninit();

	/*
	==================================================

	�Q�b�^�[

	==================================================
	*/
	/**
	 * @brief �E�B���h�E�n���h���擾
	 * @return 
	 */
	HWND	Get_WinhWnd()	{ return m_hWnd; }

	/**
	 * @brief �z�C�[���̃J�E���g�����擾����
	 * �ŏ��l����ő�l�̊ԂŃJ�E���g���s��
	 * @param min �ŏ��l�ݒ�
	 * @param max �ő�l�ݒ�
	 * @param loop �l�����[�v���邩�ǂ���
	 * @return �J�E���g��
	 */
	inline int Get_HweelCnt(int min,int max,bool loop = false)	
	{
		m_oldWheelCnt = m_wheelCnt;
		if (loop)
		{
			if (m_wheelCnt < min) { m_wheelCnt = max; }
			if (m_wheelCnt > max) { m_wheelCnt = min; }
		}
		else
		{
			if (m_wheelCnt < min) { m_wheelCnt = min; }
			if (m_wheelCnt > max) { m_wheelCnt = max; }
		}
		return m_wheelCnt;
	}

	/**
	 * @brief �O�t���[���̃z�C�[���̃J�E���g�����擾����
	 * @return 
	 */
	inline int Get_OldHweelCnt() { return m_oldWheelCnt; }

private:
	/**
	 * @brief �R���X�g���N�^
	 * @param hInst
	 * @param cmd
	 */
	WinStartUp(HINSTANCE hInst, int cmd); //�R���X�g���N�^

	/**
	 * @brief 
	 * 
	 * @param hWnd
	 * @param msg
	 * @param wParam
	 * @param lParam
	 * @return 
	 */
	static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


	static inline WinStartUp* m_spInstance;
	static POINT  m_OldMousePos;
	static POINT  m_CurMousePos;

	WNDCLASS	m_wc	  = {};
	HWND		m_hWnd	  = {};
	HINSTANCE	m_hInst	  = {};
	SIZE		m_winSize = {};
	MSG			m_msg	  = {};
	int			m_cmd	  = 0;

	int m_wheelCnt = 0;
	int m_oldWheelCnt = 0;
};



#endif // !__WIN_START_UP__
