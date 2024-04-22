/*********************************************************************
 * @file   Fade.h
 * @brief  �t�F�[�h
 *********************************************************************/
#ifndef __FADE_H__
#define __FADE_H__

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Object.h"

class Fade : public Object
{
public:
	/*
	==================================================

	�񋓑�

	==================================================
	*/
	enum class E_FADE_STATE
	{
		Stop,
		In,
		Out,
		Finish,

		Max,
	};

	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/**
	 * @brief �t�F�[�h�C���̐ݒ�
	 */
	void FadeIn()  { m_alpha = 1.0f; m_state = E_FADE_STATE::In; };

	/**
	 * @brief �t�F�[�h�A�E�g�̐ݒ�
	 */
	void FadeOut() { m_alpha = 0.0f; m_state = E_FADE_STATE::Out; };

	/**
	 * @brief ���݂̃t�F�[�h�̏�Ԃ��擾
	 * @return 
	 */
	E_FADE_STATE Get_State();

private:
	float m_alpha = 0.0f;
	float m_speed = 0.035f;
	E_FADE_STATE m_state = E_FADE_STATE::Stop;
};

#endif // !__FADE_H__

