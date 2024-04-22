/*********************************************************************
 * @file   EnemyScorpionFish.cpp
 * @brief  �G(�J�T�S)�N���X
 *********************************************************************/

 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */

#include "EnemyScorpionFish.h"

#include "../../Player/Player.h"
#include "../../Bullet/Bullet.h"
#include "../../Obstacle/Obstacle.h"
#include "../../Weapon/EnemyWeapon/WeaponScorpion.h"

#include "../../../01_System/Collison/CollisionController.h"
#include "../../../01_System/Input/Input.h"

void EnemyScorpionFish::Load()
{
	Model::Preload("Assets/Model/Enemy/EnemySC.obj");
}

void EnemyScorpionFish::Init()
{
	EnemyBase::Init();
	m_pHP->Set_MaxHP(40.0f) ;

	//- ���f���ݒ�
	{
		Add_Component<Shader>()->Load(
			"Assets/Shader/VS_Object.cso",
			"Assets/Shader/PS_Light.cso");
		Add_Component<Model>()->Load("Assets/Model/Enemy/EnemySC.obj");
	}

	m_size = { 1.5f,1.5f,1.5f };

	//- �R���C�_�[�ݒ�
	{
		Collider* coll = Add_Obj<Collider>();
		coll->Set_Tag("ScorpionFish");
		coll->Set_Pos({ 0.0f,1.0f,0.0f });
		coll->Set_WorldMatrix(Get_WorldMatrix());
	}
	//- �U���ݒ�
	m_pWeapon = Add_Obj<WeaponScorpion>();

	//- �X�e�[�g
	ChangeState(E_ENEMY_STATE::Spawn);

	m_MoveSpeed = 0.1f;
}

void EnemyScorpionFish::Update(float deltatime)
{
	Get_Obj<Collider>()->Set_WorldMatrix(Get_WorldMatrix());

	SceneBase*  scene = SceneController::Get_Scene();
	m_pPlayer = scene->Get_Object<Player>();
	//- ��͓����Ȃ��̂ŁA��x�擾�����珈�����Ȃ�
	if (!m_bSearchObstacles)
	{
		m_pObstacles = scene->Get_Objects<Obstacle>();
		m_bSearchObstacles = true;
	}
	
	//- �v���C���[�𖢔����̏ꍇ�A���E���ɂ��邩���m�F����
	if(!m_bTracking)
	{	
		m_bTracking = CheckPlayerVisible();
	}

	//- �ǔ����̍ۂɏ�Q��������ΉI�񂷂�
	if (m_curState == E_ENEMY_STATE::Tracking &&
		CheckDestinationObstacle())
	{
		//�I���̍��W�𐶐�����
		DecisionDetourPos(m_pPlayer->Get_Pos()); 
		ChangeState(E_ENEMY_STATE::Detour);
	}

	//- HP������������_���[�W��Ԃɂ���
	if (m_pHP->Get_HpData().curHp < m_oldHp && !m_bTracking)
	{	ChangeState(E_ENEMY_STATE::Tracking);	}
	
	if (m_pHP->Get_HpData().curHp <= 0.0f)
	{	ChangeState(E_ENEMY_STATE::Dead);	}

	m_oldHp = m_pHP->Get_HpData().curHp;

	EnemyBase::Update(deltatime);

	//�X�e�[�g�\��
	
//#ifdef _DEBUG
	////- ���݂̃X�e�[�g���f�o�b�N�\��
	//std::string stateName;
	//switch (m_curState)
	//{
	//	case E_ENEMY_STATE::None:		stateName = "None";			break;
	//	case E_ENEMY_STATE::Spawn:		stateName = "Spawn";		break;
	//	case E_ENEMY_STATE::Idle:		stateName = "Idle";			break;
	//	case E_ENEMY_STATE::Walk:		stateName = "Walk";			break;
	//	case E_ENEMY_STATE::Detour:		stateName = "Detour";		break;
	//	case E_ENEMY_STATE::Tracking:	stateName = "Tracking";		break;
	//	case E_ENEMY_STATE::Avoidance:	stateName = "Avoidance";	break;
	//	case E_ENEMY_STATE::Damage:		stateName = "Damage";		break;
	//	case E_ENEMY_STATE::Dead:		stateName = "Dead";			break;
	//	case E_ENEMY_STATE::Attack1:	stateName = "Attack1";		break;
	//	case E_ENEMY_STATE::Attack2:	stateName = "Attack2";		break;
	//	case E_ENEMY_STATE::Attack3:	stateName = "Attack3";		break;
	//}
	//Message::DebugLog(stateName + "\n");
//#endif // _DEBUG
}


void EnemyScorpionFish::State_Spawn(float deltatime, E_STEP step)
{
	switch (step)
	{
	case E_STEP::Start:	m_pos = m_SpawnPos;	break;
	case E_STEP::Loop:
		m_StateCurTime += deltatime;
		//- ������A��莞�ԍd��
		if (SPAWN_FREEZE_TIME < m_StateCurTime)
		{	
			ChangeState(E_ENEMY_STATE::Idle);
			m_StateCurTime = 0.0f;
		}
		break;
	case E_STEP::End:break;
	}
}

void EnemyScorpionFish::State_Idle(float deltatime, E_STEP step)
{
	switch (step)
	{
	case E_STEP::Start:

		//- �ҋ@���Ԃ̐ݒ�
		if (!m_bTracking)
		{
			m_NextChangeTime =
				(float)(rand() % (int)RANGE_IDLE_TIME) - RANGE_IDLE_TIME * 0.5f;
		}
		else
		{
			m_NextChangeTime =
				(float)(rand() % (int)RANDOM_TRAKING_IDLE_TIME) - RANDOM_TRAKING_IDLE_TIME * 0.5f;
		}

		break;

	case E_STEP::Loop:

		m_StateCurTime += deltatime;

		if (m_StateCurTime > m_NextChangeTime)
		{
			//- �v���C���[�̔F����ԂŃX�e�[�g��ύX
 			ChangeState(m_bTracking ? E_ENEMY_STATE::Tracking : E_ENEMY_STATE::Walk);
			m_StateCurTime = 0.0f;
		}

		//- �ǔ���Ԃł���΃v���C���[�̕���������
		if (m_bTracking)
		{
			ToTargetRotation(Get_toPlayerVector());	}
		break;

	case E_STEP::End:
		break;
	}
}

void EnemyScorpionFish::State_Walk(float deltatime, E_STEP step)
{
	switch (step)
	{
	case E_STEP::Start:
		CreateTargetPos();
		//- �����]���񐔂̐ݒ�
		m_DireChangeCnt = (int)(rand() % RANGE_DIRECTION_CHANGE) + (int)(RANGE_DIRECTION_CHANGE * 0.5f);
		//- ���̕����]���܂ł̎���
		m_StateCurTime = (float)(rand() % (int)1.0f) - 0.5f;
		break;
	case E_STEP::Loop: 
		MoveAtWaling(deltatime);//�ړ�����
		break;
	case E_STEP::End:	break;
	}
}

void EnemyScorpionFish::State_Detour(float deltatime, E_STEP step)
{
	switch (step)
	{
	case EnemyBase::E_STEP::Start: break;
	case EnemyBase::E_STEP::Loop:
	{
		ToTargetRotation(Get_toPlayerVector());

		float dist = DistanceToTarget(m_TargetPos);
		if (dist < MIN_OBSTACLE_DISTANCE)
		{
			ChangeState(E_ENEMY_STATE::Tracking);
		}
		else
		{
			float SpeedMulti = 3.0f;
			DirectX::XMVECTOR vToTarget = Get_toTargetVector(m_TargetPos);
			m_movement = CreateMovement(vToTarget, m_MoveSpeed * SpeedMulti);
			m_pos.x += m_movement.x;
			m_pos.z += m_movement.z;
		}
	}
	break;
	case EnemyBase::E_STEP::End: m_bDetour = false; break;
	}
}

void EnemyScorpionFish::State_Tracking(float deltatime, E_STEP step)
{
	switch (step)
	{
	case E_STEP::Start:
	{
		m_NextChangeTime = RANGE_TRAKING_TIME;
		m_AddPlayerPos.x = (float)(rand() % (int)PLAYER_TRACKING_BLUR) - PLAYER_TRACKING_BLUR * 0.5f;
		m_AddPlayerPos.z = (float)(rand() % (int)PLAYER_TRACKING_BLUR) - PLAYER_TRACKING_BLUR * 0.5f;
	}
		break;
	case E_STEP::Loop:
	{
		m_StateCurTime += deltatime;
		if (m_StateCurTime > m_NextChangeTime)
		{
			m_AddPlayerPos.x = (float)(rand() % (int)PLAYER_TRACKING_BLUR) - PLAYER_TRACKING_BLUR * 0.5f;
			m_AddPlayerPos.z = (float)(rand() % (int)PLAYER_TRACKING_BLUR) - PLAYER_TRACKING_BLUR * 0.5f;
			m_StateCurTime = 0.0f;
		}

		//- �v���C���[�̕���������
		ToTargetRotation(Get_toPlayerVector());

		float dist = DistanceToTarget(m_pPlayer->Get_Pos());
		if (dist < MIN_PLAYER_DISTANCE)
		{
			ChangeState(E_ENEMY_STATE::Attack1);
			m_StateCurTime = 0.0f;
		}
		else
		{
			DirectX::XMFLOAT3 playerPos = m_pPlayer->Get_Pos();
			playerPos.x += m_AddPlayerPos.x;
			playerPos.z += m_AddPlayerPos.z;

			float SpeedMulti = 3.0f;
			DirectX::XMVECTOR vToTarget = Get_toTargetVector(playerPos);
			m_movement = CreateMovement(vToTarget, m_MoveSpeed * SpeedMulti);
			m_pos.x += m_movement.x;
			m_pos.z += m_movement.z;

			//- �e�؂�Ȃ烊���[�h�t���O�𗧂Ă�
			if (m_pWeapon->Get_CurBulletNum() <= 0 &&
				!m_pWeapon->Get_Reload())
			{
				m_pWeapon->Set_Reload();
				ChangeState(E_ENEMY_STATE::Attack1);
			}
		}
	}
		break;
	case E_STEP::End:	break;
	}
}


void EnemyScorpionFish::State_Avoidance(float deltatime, E_STEP step)
{
	switch (step)
	{
	case E_STEP::Start:
	{
		DirectX::XMVECTOR vRight = DirectX::XMVector3Cross(Get_vForward(),Get_vUp());
		vRight = DirectX::XMVector3Normalize(vRight);
		//- ���E�ǂ���ɉ�����邩������
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 1);
		bool bRight = dis(gen);
		if (!bRight)
		{	vRight = DirectX::XMVectorScale(vRight, -1.0f);	}
		m_TargetPos = CreateMovement(vRight);
	}
		break;
	case E_STEP::Loop:
		ToTargetRotation(Get_toPlayerVector());
		DirectX::XMVECTOR vToTarget = Get_toTargetVector(m_TargetPos);
		vToTarget = DirectX::XMVector3Normalize(vToTarget);
		vToTarget = DirectX::XMVectorScale(vToTarget, m_MoveSpeed);

		DirectX::XMStoreFloat3(&m_movement, vToTarget);
		m_pos.x += m_movement.x;
		m_pos.z += m_movement.z;
		//- �ڕW�n�_�ɓ���������AIdle�ɑJ��
		if (DistanceToTarget(m_TargetPos) < MIN_WALK_APPROACH_DISTANCE)
		{	ChangeState(E_ENEMY_STATE::Tracking);	}
		break;
	case E_STEP::End:
		break;
	}
}

void EnemyScorpionFish::State_Damage(float deltatime, E_STEP step)
{
	switch (step)
	{
	case E_STEP::Start:
		if(!m_bTracking){m_bTracking = true;}
		break;
	case E_STEP::Loop:
		if (m_pHP->Get_HpData().curHp <= 0.0f)
		{	ChangeState(E_ENEMY_STATE::Dead);	}
		else
		{	ChangeState(E_ENEMY_STATE::Idle);	}
		m_oldHp = m_pHP->Get_HpData().curHp;
		break;
	case E_STEP::End:
		break;
	}
}

void EnemyScorpionFish::State_Dead(float deltatime, E_STEP step)
{
	switch (step)
	{
	case E_STEP::Start:
		break;
	case E_STEP::Loop:
	{
		float addsizeY = 0.1f;
		float diffsizeXZ = 0.1f;

		//- Y����L�΂�XZ�����k�߂�
		m_size.y += addsizeY;
		m_size.x -= diffsizeXZ;
		m_size.z -= diffsizeXZ;

		if (m_size.x < 0.0f || m_size.z < 0.0f)
		{
			m_size.x = 0.0f;
			m_size.z = 0.0f;
			Set_Destory();
			SceneBase* scene = SceneController::Get_Scene();
			//- �A�C�e���𐶐�
			int item = rand() % 3;
			if (item == 0)
			{
				Item_Stamina* stamina = scene->Add_Object<Item_Stamina>();
				stamina->Set_Pos(m_pos);
			}
			else if (item == 1)
			{
				Item_Heal* heal = scene->Add_Object<Item_Heal>();
				heal->Set_Pos(m_pos);
			}
		}
	}
		break;
	case E_STEP::End:
		break;
	}
}

void EnemyScorpionFish::State_Attack1(float deltatime, E_STEP step)
{
	switch (step)
	{
	case E_STEP::Start:
		break;
	case E_STEP::Loop:
		//- �v���C���[�̕���������
		ToTargetRotation(Get_toPlayerVector());
		//- �U��
		m_pWeapon->AttackEnemy(deltatime,this);
		//- �e�؂�Ȃ烊���[�h�t���O�𗧂Ă�
		if(m_pWeapon->Get_CurBulletNum() <= 0 && !m_pWeapon->Get_Reload())
		{	m_pWeapon->Set_Reload();	}
		else if (m_pWeapon->Get_Reload())
		{	
			//- �����[�h���I�������A�ǔ���Ԃɂ���
			if (m_pWeapon->Reload(deltatime))
			{	ChangeState(E_ENEMY_STATE::Tracking);	}
		}
		break;
	case E_STEP::End:
		break;
	}
}

void EnemyScorpionFish::State_Attack2(float deltatime, E_STEP step)
{
	switch (step)
	{
	case E_STEP::Start:	break;
	case E_STEP::Loop:	break;
	case E_STEP::End:	break;
	}
}

void EnemyScorpionFish::State_Attack3(float deltatime, E_STEP step)
{
	switch (step)
	{
	case E_STEP::Start:	break;
	case E_STEP::Loop:	break;
	case E_STEP::End:	break;
	}
}


bool EnemyScorpionFish::CheckPlayerVisible()
{
	//- �v���C���[�܂ł̋������v�Z
	DirectX::XMFLOAT3 playerPos = m_pPlayer->Get_Pos();
	float dist = DistanceToTarget(playerPos,true);
	float ViewDist = 20.0f;	//���E�̋���

	//- ���E���ɂ��邩
	if (dist < ViewDist)
	{
		//- �����̎����x�N�g���ƃv���C���[�܂ł̃x�N�g���̊p�x���擾
		float angle = AngleFromFrontVector(Get_toPlayerVector());
		float ViewAngle = 45.0f; //�G�̎��E�̍ő�p�x
		//- ���E���ɂ��邩
		if (angle <= ViewAngle){ return true; }
		else { return false; }
	}
	return false;
}

DirectX::XMVECTOR EnemyScorpionFish::Get_toPlayerVector()
{
	DirectX::XMFLOAT3 playerPos = m_pPlayer->Get_Pos();
	DirectX::XMVECTOR vToPlayer = DirectX::XMVectorSubtract(
		DirectX::XMLoadFloat3(&playerPos), DirectX::XMLoadFloat3(&m_pos));
	return vToPlayer;
}

inline void EnemyScorpionFish::CreateTargetPos()
{
	//- �����n�������͈͂������_���Ɍ��߂�
	DirectX::XMFLOAT3 minArea = m_SpawnPos;
	DirectX::XMFLOAT3 maxArea = { m_SpawnPos.x + RANGE_TARGET_POS ,0.0f,m_SpawnPos.z + RANGE_TARGET_POS};
	
	//- ����������W���G���A�����W�̒��Ń����_���Őݒ�
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> disX(minArea.x, maxArea.x);
	std::uniform_real_distribution<float> disZ(minArea.z, maxArea.z);

	DirectX::XMFLOAT3 randomPos;
	randomPos.x = disX(gen);
	randomPos.y = 0.0f;
	randomPos.z = disZ(gen);

	if(randomPos.x > maxArea.x)
	{	randomPos.x = maxArea.x;	}
	if (randomPos.z > maxArea.z)
	{	randomPos.z = maxArea.z;	}

	m_TargetPos = randomPos;

	if(CheckDestinationObstacle())
	{	DecisionDetourPos(m_TargetPos);	}
}

bool EnemyScorpionFish::CheckDestinationObstacle()
{
	//- ��̐��������[�v
	for (Obstacle* obj : m_pObstacles)
	{
		//- �i�s�����ɏ�Q�������邩���m�F
		CollisionController::AABB aabb;
		aabb = CollisionController::ChangeAABB(obj->Get_Obj<Collider>());
		CollisionController::Ray ray;
		ray.origin = m_pos;
		ray.dir = m_TargetPos;

		float dist = DistanceToTarget(obj->Get_Pos());
		//- �ڕW�n�_�ɏ�Q��������@���@��Q���܂ł̋�������苗���ȓ�
		if (CollisionController::AABBwithRay(aabb, ray) &&
			dist < MIN_OBSTACLE_DISTANCE)
		{
			m_pObstacle = obj;
			return true;
		}
		else
		{	continue;	}
	}

	return false;
}



void EnemyScorpionFish::DecisionDetourPos(DirectX::XMFLOAT3 TargetPos)
{
	//- �I�񒆂ł���Ώ������Ȃ�
	if(m_bDetour){return;}

	DirectX::XMFLOAT3 rockPos  = m_pObstacle->Get_Pos();
	DirectX::XMFLOAT3 rockSize = m_pObstacle->Get_Size();
	
	float extraDistace = 15.0f;//�I�񋗗��̗]�T�l

	//-�I����W�́A��̕ӂ̒�������I�񋗗������ꂽ���W�ɐݒ肷��
	//���Ɖ��s���̕ӂ̒����l�����߂�
	float HalfWidth = rockSize.x * 0.5f;
	float HalfDepth = rockSize.z * 0.5f;

	//XZ���̂ǂ���ɉI�񂷂邩������
	if (std::abs(TargetPos.x - m_pos.x) >
		std::abs(TargetPos.z - m_pos.z))
	{

		//- X����̋����������ꍇ�AZ���ɉ����ĉI��
		//�ڕW��Z����Ŋ�̑O�ɂ��邩�A���ɂ��邩�ŉI��������
		m_TargetPos.z = (TargetPos.z < rockPos.z) ?
			(rockPos.z - HalfWidth - extraDistace) : //�O
			(rockPos.z + HalfDepth + extraDistace);	 //��
		m_TargetPos.x = rockSize.x;	//��̕�
	}
	else
	{
		//- Z����̋����������ꍇ�AX���ɉ����ĉI��
		//�ڕW��X����Ŋ�̑O�ɂ��邩�A���ɂ��邩�ŉI��������
		m_TargetPos.x = (TargetPos.x < rockPos.x) ?
			(rockPos.x - HalfWidth - extraDistace) : //�O
			(rockPos.x + HalfDepth + extraDistace);	 //��
		m_TargetPos.z = rockSize.z; //��̉��s��
	}

	m_TargetPos.y = 0.0f;
	m_bDetour = true;
}

void EnemyScorpionFish::MoveAtWaling(float deltatime)
{
	ToTargetRotation(Get_toTargetVector(m_TargetPos));
	DirectX::XMVECTOR vToTarget = Get_toTargetVector(m_TargetPos);
	vToTarget = DirectX::XMVector3Normalize(vToTarget);
	vToTarget = DirectX::XMVectorScale(vToTarget, m_MoveSpeed);

	DirectX::XMStoreFloat3(&m_movement, vToTarget);
	m_pos.x += m_movement.x;
	m_pos.z += m_movement.z;

	m_StateCurTime -= deltatime;
	if (m_StateCurTime <= 0 && m_DireChangeCnt > 0)
	{
		CreateTargetPos();
		m_DireChangeCnt--;
		m_StateCurTime =
			(float)(rand() % (int)RANDOM_MOVE_TIME) - RANDOM_MOVE_TIME;
	}

	//- �ڕW�n�_�ɓ���������AIdle�ɑJ��
	if (DistanceToTarget(m_TargetPos) < MIN_WALK_APPROACH_DISTANCE)
	{
		ChangeState(E_ENEMY_STATE::Idle);
	}
}