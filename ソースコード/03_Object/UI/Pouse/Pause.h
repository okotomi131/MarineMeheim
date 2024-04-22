/*********************************************************************
 * @file   Pause.h
 * @brief  �|�[�Y����
 *********************************************************************/
#ifndef __PAUSE_H__
#define __PAUSE_H__
/*
==================================================

�C���N���[�h

==================================================
*/

#include "../../Object.h"
#include "../../../02_Component/Sprite/Sprite.h"

class Pause : public Object
{
public:
	/**
	 * @brief ����������
	 */
	virtual void Init() override;

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	virtual void Update(float deltatime)override;

	/**
	 * @brief ��ʓ��ɕ`��
	 */
	virtual void DrawPause();

	/**
	 * @brief ��ʊO�ɕ`��
	 */
	virtual void UnDrawPause();

	/**
	 * @brief �ĊJ�t���O���擾
	 * @return �ĊJ�{�^���������ꂽ��true
	 */
	bool Get_Restart() { return m_bRestart; }

	/**
	 * @brief ���Ȃ����t���O���擾
	 * @return ���Ȃ����{�^���������ꂽ��true
	 */
	bool Get_NewStart() { return m_bNewStart; }

	/**
	 * @brief �P�ރt���O���擾
	 * @return �P�ރ{�^���������ꂽ��true
	 */
	bool Get_ReTreat() { return m_bReTreat; }

	/**
	 * @brief �S�Ẵt���O�����Z�b�g
	 * �e�t���O�͂��ꂼ�ꓯ����true�ɂȂ邱�Ƃ͂Ȃ�
	 */
	virtual void AllFlagReset() { m_bRestart = false; m_bNewStart = false; m_bReTreat = false; }
protected:
	bool m_bNewStart = false;
	bool m_bReTreat = false;

	DirectX::XMFLOAT2 m_PausePos = { 0.0f,0.0f };
	std::vector<DirectX::XMFLOAT2> m_buttonPos;
	std::vector<class ButtonBase*> m_pButtonList;
private:
	bool m_bRestart = false;
};

#endif // !__PUSE_H__
