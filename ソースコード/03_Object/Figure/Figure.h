/*********************************************************************
 * @file   Figure.h
 * @brief  ���f���݂̂�\������
 *********************************************************************/
#ifndef __FIGURE_H__
#define __FIGURE_H__

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Object.h"

class Figure : public Object
{
public:
	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/**
	 * @brief ���f���̓ǂݍ���
	 * @param filename
	 */
	void LoadModel(const char* filename);

	/**
	 * @brief ��]�t���O�̐ݒ�
	 * @param flag
	 */
	void Set_Rotate(bool flag) { m_bRotate = flag; }
private:
	bool m_bRotate = false;
};

#endif // !__FIGURE_H__

