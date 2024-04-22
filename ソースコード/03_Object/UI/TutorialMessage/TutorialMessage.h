/*********************************************************************
 * @file   TutorialMessage.h
 * @brief  �`���[�g���A���p�̃��b�Z�[�W��\������
 *********************************************************************/

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../../Object.h"
#include "../../../02_Component/Sprite/Sprite.h"
#include "../../../02_Component/Sound/Sound.h"

class TutorialMessage : public Object
{
public:
	/**
	 * @brief ����������
	 */
	void Init()override;
	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime)override;

	/**
	 * @brief ���ݕ\�����郁�b�Z�[�W�ԍ���ݒ�
	 * @param num ���b�Z�[�W�ԍ�
	 */
	inline void Set_CurDrawMessage(int num) { m_curDrawMessage = num; }

	/**
	 * @brief ���b�Z�[�W�\�����I��������
	 * @return �I�������true
	 */
	inline bool Get_IsEnd() { return m_bEnd; }

private:
	bool m_bEnd = false;
	int m_curDrawMessage = 0;
	DirectX::XMFLOAT2 m_viewPos = {};

	std::vector<Sprite*> m_pDrawMessage;
	std::vector<Sound*>  m_pSoundList;
};

