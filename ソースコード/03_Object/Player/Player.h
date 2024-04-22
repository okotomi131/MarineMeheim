/*********************************************************************
 * @file   Player.h
 * @brief  �v���C���[�̏������s���N���X
 *********************************************************************/

#ifndef __PLAYER_H__
#define __PLAYER_H__

 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */

#include "../Object.h"
#include "../Weapon/WeaponBase.h"
#include "../../02_Component/HP/HPBase.h"
#include "../../02_Component/Sound/Sound.h"

class Player : public Object
{
public:
	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �X�V����
	 * @param deltatime �f���^�^�C��
	 */
	void Update(float deltatime) override;

	/**
	 * @brief �I������
	 */
	void Uninit() override;

	/*
	==================================================

	�Z�b�^�[

	==================================================
	*/

	/**
	 * @brief �ړ��ʂ�ݒ肷��
	 */
	inline void Set_Movement(DirectX::XMFLOAT3 movement) { m_movement = movement; };

	/**
	 * @brief �ړ��������W��ݒ肷��
	 */
	inline void Set_LimitPos(DirectX::XMFLOAT2 pos) { m_LimitPos = pos; };

	
	/**
	 * @brief �X�^�~�i��ݒ肷��
	 */
	inline void StaminaRecovery(float stamina) 
	{
		if (m_Stamina >= STAMINA_MAX) 
		{	return;		}
		m_Stamina += stamina; 
	};

	inline void SoundPlay(std::string name)
	{
		if (m_SoundList.find(name) != m_SoundList.end())
		{
			m_SoundList[name]->Play();
		}
	};

	/*
	==================================================

	�Q�b�^�[

	==================================================
	*/

	WeaponBase* Get_Weapon();
	inline DirectX::XMFLOAT3 Get_Movement() { return m_movement; };
	inline DirectX::XMFLOAT3 Get_OldPos()	{ return m_oldPos; };
	inline float Get_Stamina()				{ return m_Stamina; };
	inline float Get_MaxStamina()			{ return STAMINA_MAX; };
	inline bool Get_IsMove() const { return m_movement.x != 0.0f || m_movement.z != 0.0f; };
	inline bool Get_IsDead() const { return m_bDead; };
private:
	/**
	 * @brief �U������
	 * @param deltatime �f���^�^�C��
	 */
	void Attack(float deltatime);

	/**
	 * @brief �}�E�X�ړ��ɕ����ĉ�]����
	 * @param deltatime �f���^�^�C��
	 */
	void Rotation(float deltatime);

	/**
	 * @brief �ړ�����
	 * @param deltatime �f���^�^�C��
	 */
	void Move(float deltatime);

	/**
	 * @brief �������
	 * @param deltatime �f���^�^�C��
	 */
	void Slide(float deltatime);


	/*
	==================================================

	�萔

	==================================================
	*/
	const float SLIDE_DURATION = 0.5f;	//�X���C�f�B���O����
	const float SLIDE_DISTANCE = 5.0f;	//�X���C�f�B���O����
	const float STAMINA_MAX = 100.0f;	//�X�^�~�i�ő�l
	const float STAMINA_CONSUMPTION = 20.0f;	//�X�^�~�i�����
	const float STAMINA_CONSUMPTION_RUN = 0.5f;	//�_�b�V�����̃X�^�~�i�����
	const float MIN_STAMINA_AMOUNT_RUN = 20.0f; //�_�b�V���ł���X�^�~�i�̍Œ��
	const float INIT_MOVE_SPEED = 10.0f;	//�ړ����x

	//- �T�E���h
	class Sound* m_Sound = nullptr;

	//- �ړ�
	float m_MoveSpeed = INIT_MOVE_SPEED;
	float m_RunSpeed = 3.0f;
	DirectX::XMFLOAT3 m_movement = {};
	DirectX::XMFLOAT3 m_fForward = {};//�O���x�N�g��
	DirectX::XMFLOAT3 m_oldPos   = {};

	//- ��]
	POINT m_OldMousePos = {};
	DirectX::XMFLOAT3 m_fRight = {};//���x�N�g��

	float m_JumpForce	= 0.5f;
	float m_Resistor	= 0.15f;
	float m_Gravity		= 0.1f;

	//- ���
	bool  m_bSlideRight = false;
	bool  m_bSlideLeft = false;
	float m_SlideTime = 0.0f;
	DirectX::XMFLOAT3 m_SlideDir = {};

	//- �X�^�~�i
	float m_Stamina = 0.0f;
	bool m_bStaminaRecovery = false;

	//- �ړ��������W
	DirectX::XMFLOAT2 m_LimitPos = { 999.9f, 999.9f };

	//- �T�E���h
	std::unordered_map<std::string, class Sound*> m_SoundList = {};

	//- ���S
	bool m_bDead = false;

	//- �f�o�b�N
	bool m_bGodMode = false;
};


#endif // !__PLAYER_H__
