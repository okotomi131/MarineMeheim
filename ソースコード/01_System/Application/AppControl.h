/*********************************************************************
 * @file   AppControl.h
 * @brief  �A�v���P�[�V��������N���X
 *********************************************************************/

#ifndef __APPCONTROL_H__
#define __APPCONTROL_H__

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Window/WinStartUp.h"


class AppControl
{
public:
	/**
	 * @brief �R���X�g���N�^
	 *
	 * �E�B���h�E�A�V�[���̏��������Ăяo��
	 *
	 * @param hinst �C���X�^���g�n���h��(�G���g���[�|�C���g����n�����
	 * @param cmd �R�}���h���C��(��L�Ɠ���
	 */
	AppControl(HINSTANCE hinst, int cmd);


	/**
	 * @brief �f�X�g���N�^
	 * �E�B���h�E�A�V�[���̏I���������Ăяo��
	 */
	~AppControl();

	/**
	 * @brief �A�v���P�[�V�������[�v
	 * ���b�Z�[�W���[�v�ƃQ�[�����[�v���s��
	 */
	void Update();

	/**
	 * @brief �f�o�b�N�pFPS�\��
	 * @param diff �t���[�����[�g
	 */
	void DebugFPS(float diff);
private:
	DWORD		m_startTime;		//�J�n����
	DWORD		m_executionTime;	//���s����
};

#endif // !__APPCONTROL_H__
