/*********************************************************************
 * @file   Obstacle.h
 * @brief  ��Q����ėp�I�ɍ쐬����
 *********************************************************************/
#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "../Object.h"

class Obstacle : public Object
{
public:
	enum class E_OBJECT_TYPE
	{
		Rock,
		Coral,

		Max
	};

	/**
	 * @brief �t�@�C���ǂݍ���
	 * @param fileName �ǂݍ��ރt�@�C����
	 */
	void Load(const char* fileName);

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
	 * @brief �R���C�_�[�̃T�C�Y��ݒ肷��
	 * @param size
	 */
	void Set_CollSize(float size = 2.5f);
private:
};

#endif // !__OBSTACLE_H__


