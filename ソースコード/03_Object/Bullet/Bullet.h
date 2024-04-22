/*********************************************************************
 * @file   Bullet.h
 * @brief  �e
 *********************************************************************/
#ifndef __BULLET_H__
#define __BULLET_H__

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Object.h"

class Bullet : public Object
{
public:

	/*
	==================================================

	�񋓑�

	==================================================
	*/
	//- �e�̎��
	enum class E_TAG_TYPE
	{
		None,
		Player,
		Enemy,
	};

	/*
	==================================================

	�\����

	==================================================
	*/
	//- �e�Ɋ܂܂��f�[�^
	struct BulletData
	{
		float speed = 0.0f;	//�e��
		float damage = 10.0f;	//�_���[�W
		float range = 1000.0f;	//�L���˒�����
	};

	/**
	 * @brief ���f���̓ǂݍ���
	 */
	static void Load();

	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/*
	==================================================

	�Q�b�^�[

	==================================================
	*/

	/**
	 * @brief �폜�t���O�̎擾
	 * @return �폜�\��Ȃ�true
	 */
	bool Get_Destory() const { return m_bDestroy; }

	/**
	 * @brief �e�����_���[�W�̎擾
	 * @return  �_���[�W�l
	 */
	float Get_Damage() const { return m_bulletData.damage; }

	/**
	 * @brief �e�̎�ނ��擾
	 * @return �^�O
	 */
	E_TAG_TYPE Get_Tag() const	 { return m_tag; }

	/*
	==================================================

	�Z�b�^�[

	==================================================
	*/
	/**
	 * @brief �^�O��ݒ肷��
	 * @param tag �^�O�񋓑�
	 */
	void Set_Tag(const E_TAG_TYPE tag)  { m_tag = tag; }

	/**
	 * @brief �e���i�ޕ�����ݒ肷��
	 * @param dir ����
	 */
	void Set_Direction(const DirectX::XMFLOAT3& dir) { m_direction = dir; }

	/**
	* @brief �e�̃f�[�^��ݒ肷��
	* @param data �e�̃f�[�^
	*/
	void Set_BulletData(const BulletData& data) { m_bulletData = data; }

private:
	DirectX::XMFLOAT3 m_direction;
	
	BulletData m_bulletData;

	float m_deleteTime = 10.0f;	//�폜����
	float m_curTime = 0.0f;		//�o�ߎ���

	E_TAG_TYPE m_tag = E_TAG_TYPE::None;
};

#endif // !__BULLET_H__

