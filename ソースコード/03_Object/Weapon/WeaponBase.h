/*********************************************************************
 * @file   WeaponBase.h
 * @brief  ����̊��N���X
 *********************************************************************/
#ifndef __WEAPON_BASE_H__
#define __WEAPON_BASE_H__

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Object.h"
#include "../Bullet/Bullet.h"

class WeaponBase : public Object
{
public:
	/*
	==================================================

	�\����

	==================================================
	*/
	//- ����f�[�^
	struct WeaponData
	{
		Bullet::BulletData bulletData = {};	//�e�̃f�[�^
		int bulletNum	 = 0;	//�e��
		int multiShotNum = 0;	//�������˒e��
		float reloadTime = 0.0f;//�����[�h����
		float bulletSize = 0.0f;//�e�̑傫��
		float rate		 = 0.0f;//�ˌ����[�g
		DirectX::XMFLOAT2 SpreadAngle = {};//�g�U�p�x
	};


	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �v���C���[�̍U������
	 * @param deltatime
	 */
	void AttackPlayer(float deltatime);

	/**
	 * @brief �G�̍U������
	 * @param deltatime 
	 * @param enemy
	 */
	void AttackEnemy(float deltatime,class EnemyBase* enemy);
	
	/**
	 * @brief �����[�h����
	 * @param deltatime
	 * @return 
	 */
	bool Reload(float deltatime);

	/**
	 * @brief �����[�h�̌p�����Ԃ����Z�b�g
	 */
	void Reset_CurRateTime() { m_curRateTime = 0.0f; }

	/*
	==================================================

	�Q�b�^�[

	==================================================
	*/

	/**
	 * @brief �����[�h�t���O���擾
	 * @return �����[�h���Ȃ�true 
	 */
	bool  Get_Reload()	     const { return m_bReload; }

	/**
	 * @brief �����[�h�̌o�ߎ��Ԃ��擾
	 * @return 
	 */
	float Get_CurReloadTime()const { return m_curReloadTime; }
	float Get_ReloadTime()   const { return m_weaponData.reloadTime; }
	int   Get_CurBulletNum() const { return m_curBulletNum; }
	int   Get_MaxBulletNum() const { return m_weaponData.bulletNum; }

	/*
	==================================================

	�Z�b�^�[

	==================================================
	*/

	/**
	 * @brief �����[�h�t���O���Z�b�g
	 */
	void Set_Reload() { m_bReload = true; }
protected:
	int   m_curBulletNum;   //�c�e��
	float m_curRateTime;	//�o�ߎ���
	float m_curReloadTime;	//�����[�h�o�ߎ���
	bool  m_bReload;		//�����[�h����
	bool  m_bMultiShot;		//�������˂��邩
	class SceneBase* m_pScene = {};
	WeaponData m_weaponData = {};

};

#endif // !__WEAPON_BASE_H__


