/*********************************************************************
 * @file   Sky.h
 * @brief  �X�J�C�h�[��
 *********************************************************************/
#ifndef __SKY_H__
#define __SKY_H__
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "../Object.h"
class Sky : public Object
{
public:
	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime) override;

};
#endif // !__SKY_H__


