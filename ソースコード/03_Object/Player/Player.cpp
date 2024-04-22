/*********************************************************************
 * @file   Player.cpp
 * @brief  �v���C���[
 *********************************************************************/

 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "Player.h"
#include "../Bullet/Bullet.h"
#include "../Collider/Collider.h"

#include "../Camera/CameraPlayer.h"
#include "../Weapon/PlayerWeapon/WeaponAssault.h"

#include "../../01_System/Input/Input.h"
#include "../../01_System/Window/WinStartUp.h"
#include "../../01_System/Save/DataSave.h"
#include "../../01_System/Collison/CollisionController.h"

#include "../../02_Component/Shader/Shader.h"
#include "../../02_Component/Sound/Sound.h"
#include "../../02_Component/Model/Model.h"

#include "../../04_Scene/SceneController.h"
#include "../../04_Scene/SceneBase.h"

void Player::Init()
{
	//- �v���C���[�ݒ�
	{
		Add_Component<Shader>()->Load("Assets/Shader/VS_Object.cso","Assets/Shader/PS_Light.cso");
		Add_Component<Model>()->Load("Assets/Model/Player/Player.obj");
		m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_size = DirectX::XMFLOAT3(1.5f, 1.5f, 1.5f);
		m_rot = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	
	//- HP�ݒ�
	{
		HPBase* hp = Add_Component<HPBase>();
		float dataHp = DataSave::Get_Data<float>("PlayerHP");
		hp->Set_MaxHP(dataHp);
		hp->ResetHP();
	}

	//- �R���W����
	{
		Collider* coll = Add_Obj<Collider>();
		coll->Set_Tag("Player");
		coll->Set_WorldMatrix(Get_WorldMatrix());
		coll->Set_wSize(m_size);
		coll->Set_Pos({ 0.0f, 1.0f, 0.0f });
	}

	//- �X�^�~�i
	m_Stamina = STAMINA_MAX;

	Add_Obj<WeaponAssault>();
	
	m_SoundList.insert(std::make_pair("Attack",Add_Component<Sound>()));
	m_SoundList["Attack"]->Load("Assets/Sound/SE/InGame/Shot.wav");
	m_SoundList.insert(std::make_pair("Dodge", Add_Component<Sound>()));
	m_SoundList["Dodge"]->Load("Assets/Sound/SE/InGame/Dodge.wav");
	m_SoundList.insert(std::make_pair("OverHeat", Add_Component<Sound>()));
	m_SoundList["OverHeat"]->Load("Assets/Sound/SE/InGame/OverHeat.wav");
	m_SoundList.insert(std::make_pair("Hit", Add_Component<Sound>()));
	m_SoundList["Hit"]->Load("Assets/Sound/SE/InGame/Hit.wav");
	m_SoundList.insert(std::make_pair("ItemGet", Add_Component<Sound>()));
	m_SoundList["ItemGet"]->Load("Assets/Sound/SE/InGame/ItemGet.wav");
}


void Player::Update(float deltatime)
{
	Get_Obj<Collider>()->Set_WorldMatrix(Get_WorldMatrix());

	//- �x�N�g���ϊ�
	//�O
	DirectX::XMVECTOR vForward = Get_vForward();
	vForward = DirectX::XMVector3Normalize(vForward);
	DirectX::XMStoreFloat3(&m_fForward, vForward);
	//�E
	DirectX::XMVECTOR vRight;
	DirectX::XMVECTOR vUp = Get_vUp();
	vUp = DirectX::XMVector3Normalize(vUp);
	vRight = DirectX::XMVector3Cross(vForward, vUp);
	vRight = DirectX::XMVector3Normalize(vRight);
	DirectX::XMStoreFloat3(&m_fRight, vRight);
	
	m_movement = { 0.0,0.0f,0.0f };	//�ړ��ʏ�����
	m_oldPos = m_pos;	


	//- ��������
	Move(deltatime);
	Rotation(deltatime);
	Attack(deltatime);

	//- ���S���Ă��邩
	if (Get_Component<HPBase>()->Get_HpData().curHp <= 0.0f)
	{	m_bDead = true;	}

	//- �������W�ȏ�𒴂��Ȃ��悤�ɂ���
	if(m_pos.x > m_LimitPos.x) { m_pos.x = m_LimitPos.x; }
	else if(m_pos.x < -m_LimitPos.x) { m_pos.x = -m_LimitPos.x; }
	if(m_pos.z > m_LimitPos.y) { m_pos.z = m_LimitPos.y; }
	else if(m_pos.z < -m_LimitPos.y) { m_pos.z = -m_LimitPos.y; }

	/*
	======================================================

	--------------------�f�o�b�N�p--------------------

	======================================================
	*/
	if (Input::Get_KeyPress(VK_F1) && Input::Get_KeyPress('P'))
	{	m_bGodMode = !m_bGodMode;	}

	if (m_bGodMode)
	{
		m_Stamina = STAMINA_MAX;
		Get_Component<HPBase>()->ResetHP();
	}
}

void Player::Uninit()
{
	for (auto& sound : m_SoundList)
	{
		sound.second->Stop();
	}
	m_SoundList.clear();
}


void Player::Attack(float deltatime)
{
	WeaponAssault* ar = Get_Obj<WeaponAssault>();
	if (Input::Get_KeyPress(VK_LBUTTON) && !ar->Get_Reload()) 
	{ 	
		ar->AttackPlayer(deltatime); 
		m_SoundList["Attack"]->Play();
	}
	
	if ((ar->Get_CurBulletNum() <= 0 || Input::Get_KeyTrigger('R')) && 
		!ar->Get_Reload()) 
	{ ar->Set_Reload(); }
	else if (ar->Get_Reload()) 
	{ ar->Reload(deltatime); }
}

WeaponBase* Player::Get_Weapon()
{
	return Get_Obj<WeaponAssault>();
}

void Player::Rotation(float deltatime)
{
	//- �E�B���h�E�̒������W���擾
	int centerX = static_cast<int>(SCREEN_WIDTH  * 0.5f);
	int centerY = static_cast<int>(SCREEN_HEIGHT * 0.5f);

	//- ���݂̃J�[�\���̍��W���擾
	POINT curMousePos;
	GetCursorPos(&curMousePos);
	ScreenToClient(GET_WIN.Get_WinhWnd(), &curMousePos);

	//- �E�B���h�E�̒������W�ƌ��݂̃J�[�\���̍��W�̍������v�Z
	float deltaX = static_cast<float>(curMousePos.x - centerX);
	float deltaY = static_cast<float>(curMousePos.y - centerY);

	//- �����̒l�����ɉ�]�p�x���v�Z
	float speed = 0.1f;
	m_rot.y += deltaX * speed * deltatime;
	m_rot.x += deltaY * speed * deltatime;

	//- �㉺�̉�](�s�b�`��])�̐���
	//�@80�`-80�x�̊ԂŐ����ɂ���
	float LimitAngle = DirectX::XMConvertToRadians(80.0f);
	m_rot.x = std::max(std::min(m_rot.x, LimitAngle),-LimitAngle);

	//- �J�[�\�����E�B���h�E�̒����ɖ߂�
	POINT centerPos = { centerX, centerY };
	ClientToScreen(GET_WIN.Get_WinhWnd(), &centerPos);
	SetCursorPos(centerPos.x, centerPos.y);
}

void Player::Move(float deltatime)
{
	//- ���͑���
	if (Input::Get_KeyPress('W'))
	{
		if (Input::Get_KeyPress(VK_SHIFT) && !m_bStaminaRecovery)
		{
			m_movement.x += m_fForward.x * m_RunSpeed;
			m_movement.z += m_fForward.z * m_RunSpeed;
			m_Stamina -= STAMINA_CONSUMPTION_RUN;
			if(m_Stamina < 0.0f) 
			{ 
				m_bStaminaRecovery = true; 
				m_SoundList["OverHeat"]->Play();
			}
		}
		else
		{
			m_movement.x += m_fForward.x;
			m_movement.z += m_fForward.z;
		}
	}
	if (Input::Get_KeyPress('S'))
	{
		m_movement.x -= m_fForward.x;
		m_movement.z -= m_fForward.z;
	}
	if (Input::Get_KeyPress('A'))
	{
		if (Input::Get_KeyTrigger(VK_SPACE) && m_Stamina > STAMINA_CONSUMPTION)
		{
			m_Stamina -= STAMINA_CONSUMPTION;
			m_bSlideLeft = true; 
			m_SoundList["Dodge"]->Play();
		}
		m_movement.x += m_fRight.x;
		m_movement.z += m_fRight.z;
	}
	if (Input::Get_KeyPress('D'))
	{
		if (Input::Get_KeyTrigger(VK_SPACE) && m_Stamina > STAMINA_CONSUMPTION)
		{	
			m_Stamina -= STAMINA_CONSUMPTION;
			m_bSlideRight = true;	
			m_SoundList["Dodge"]->Play();
		}
		m_movement.x -= m_fRight.x;
		m_movement.z -= m_fRight.z;
	}

	Slide(deltatime);

	m_movement.y -= m_Gravity;					//�d��
	m_movement.y -= m_movement.y * m_Resistor;	//��R 

	//- ���W�X�V
	m_pos.x += m_movement.x * m_MoveSpeed * deltatime;
	m_pos.z += m_movement.z * m_MoveSpeed * deltatime;
	m_pos.y += m_movement.y;
}

void Player::Slide(float deltatime)
{
	if (m_bSlideRight || m_bSlideLeft)
	{
		m_SlideTime += deltatime;
		if (m_SlideTime > SLIDE_DURATION)
		{
			m_bSlideRight = false;
			m_bSlideLeft = false;
			m_SlideTime = 0.0f;

		}
		else
		{
			// �X���C�h���̈ړ��ʌv�Z
			float slideAmount = (SLIDE_DURATION - m_SlideTime) / SLIDE_DURATION;
			if (m_bSlideRight)
			{
				m_movement.x -= m_fRight.x * SLIDE_DISTANCE * slideAmount;
				m_movement.z -= m_fRight.z * SLIDE_DISTANCE * slideAmount;
			}
			else if (m_bSlideLeft)
			{
				m_movement.x += m_fRight.x * SLIDE_DISTANCE * slideAmount;
				m_movement.z += m_fRight.z * SLIDE_DISTANCE * slideAmount;
			}
		}
	}
	else if (m_Stamina <= STAMINA_MAX)
	{
		m_Stamina += deltatime * 25.0f;
		if(m_Stamina > MIN_STAMINA_AMOUNT_RUN)
		{ m_bStaminaRecovery = false; }
		if(m_Stamina > STAMINA_MAX)
		{	m_Stamina = STAMINA_MAX; }
	}
}
