/*********************************************************************
 * @file   BulletNumUI.h
 * @brief  �e�̎c�e��\������UI
 *********************************************************************/
#ifndef __BULLET_NUM_UI_H__
#define __BULLET_NUM_UI_H__
 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "../../Object.h"

class BulletNumUI : public Object
{
public:
	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �I������
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/**
	 * @brief �`�揈��
	 */
	void Draw() override;

	/**
	 * @brief ���������ݒ肷��
	 * @param weapon
	 */
	void Set_Weapon(class WeaponBase* weapon) { m_pWeapon = weapon; }
private:
	const float MAX_GAGE_SIZE_Y = 230.0f; //�Q�[�W�̍ő�T�C�Y
	
	const char* m_pBaseFileName   = nullptr;	//UI�̃x�[�X
	const char* m_pCntBoxFileName = nullptr; //�e���\���g
	const char* m_pGageFileName   = nullptr;	//�e�Q�[�W
	class WeaponBase* m_pWeapon = {};
	float m_initSizeY = 0.0f;
};
#endif // !__BULLET_NUM_UI_H__


