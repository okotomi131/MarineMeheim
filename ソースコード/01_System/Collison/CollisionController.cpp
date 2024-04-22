/*********************************************************************
 * @file   CollisionController.cpp
 * @brief  �����蔻��̊Ǘ����s��
 *********************************************************************/

 /*
 ===================================================================

�C���N���[�h 

 ===================================================================
 */
#include "CollisionController.h"

#include "../../01_System/main.h"

#include "../../03_Object/Player/Player.h"
#include "../../03_Object/Enemy/EnemyBase.h"
#include "../../03_Object/Enemy/Scorpionfish/EnemyScorpionFish.h"
#include "../../03_Object/Enemy/GlobeFish/GlobeFish.h"
#include "../../03_Object/Enemy/Clownfish/Clownfish.h"
#include "../../03_Object/Enemy/Spawner/EnemySpawner.h"
#include "../../03_Object/Enemy/TutorialEnemy/TutorialEnemy.h"
#include "../../03_Object/Bullet/Bullet.h"
#include "../../03_Object/Obstacle/Obstacle.h"
#include "../../03_Object/Obstacle/Field.h"
#include "../../03_Object/Effect/Effect.h"
#include "../../03_Object/Item/Item_Heal.h" 
#include "../../03_Object/Item/Item_Stamina.h"

#include "../../04_Scene/SceneController.h"
#include "../../04_Scene/SceneBase.h"


float CollisionController::m_groundHeight	= 0.0f;		//�n�ʂ̍���
SceneBase*  CollisionController::m_pScene	= nullptr;	//�V�[���ϐ�
Player*		CollisionController::m_pPlayer	= nullptr;	//�v���C���[�ϐ�
Bullet*		CollisionController::m_pBullet	= nullptr;	//�e�ϐ�
EnemyBase*  CollisionController::m_pEnemy	= nullptr;	//�G�ϐ�
ItemBase*	CollisionController::m_pItem		= nullptr;	//�A�C�e���ϐ�

void CollisionController::Update(float deltatime)
{
	//- �Q�[���V�[���ɕK��������̂��擾
	m_pScene  = SceneController::Get_Scene();
	m_pPlayer = m_pScene->Get_Object<Player>();
	Field* field  = m_pScene->Get_Object<Field>();

	//- �n�ʏ���������
	m_groundHeight = 0.0f;
	m_groundHeight = field->Get_Pos().y;

	//- ��ƃv���C���[�̃R���W��������
	std::vector<Obstacle*> obstacles = m_pScene->Get_Objects<Obstacle>();
	CheckHitObstacletoPlayer(obstacles);

	//- �A�C�e���ƃv���C���[�̃R���W��������
	std::vector<ItemBase*> items = m_pScene->Get_BaseObjects<ItemBase>();
	if (items.size() > 0)
	{	CheckHitItemtoPlayer(items);}


	//- �v���C���[�ƒn�ʂ̔���
	CheckHitFieldtoPlayer();

	//- ��
	std::vector<Bullet*> bullets = m_pScene->Get_Objects<Bullet>();
	for (Bullet* bullet : bullets)
	{
		m_pBullet = bullet;
		AABB bulletAABB = ChangeAABB(m_pBullet->Get_Obj<Collider>());
		//- �e�̎�ނ𔻕ʂ��A�������I�������玟�̒e��
		if(SearchBulletType()){	continue; }

		//- �ǂƂ̔���
		CheckHitObstacletoBullet(obstacles);

		//- �n�ʂƂ̔���
		if (m_pBullet->Get_Pos().y < m_groundHeight)
		{	
			//- �e�������Ɠ����ɃG�t�F�N�g�𐶐�
			DirectX::XMFLOAT2 EffectSize = { 12.0f,12.0f };
			SpawnEffect(EffectSize);
			m_pBullet->Set_Destory();
			continue;
		}
	}

}

void CollisionController::CheckHitItemtoPlayer(std::vector<ItemBase*>& items)
{
	for (ItemBase* item : items)
	{
		m_pItem = item;
		AABB itemAABB	= ChangeAABB(m_pItem->Get_Obj<Collider>());
		AABB playerAABB = ChangeAABB(m_pPlayer->Get_Obj<Collider>());
		if (AABBWithAABB(playerAABB, itemAABB))
		{
			m_pPlayer->SoundPlay("ItemGet");
			//- �A�C�e���̎�ނ𔻕ʂ��A�A�C�e�����Ƃ̏������s��
			SearchItemTag();
			break;
		}
	}
}

void CollisionController::SearchItemTag()
{
	//- �A�C�e���̎�ނ𔻕�
	if (m_pItem->Get_Obj<Collider>()->Get_Tag() == "ItemHeal")
	{
		//- �񕜃A�C�e��
		Item_Heal* heal = dynamic_cast<Item_Heal*>(m_pItem);
		if (heal != nullptr)
		{	m_pPlayer->Get_Component<HPBase>()->Heal(heal->Get_Heal());	}
	}
	else if (m_pItem->Get_Obj<Collider>()->Get_Tag() == "ItemStamina")
	{
		//- �X�^�~�i�A�C�e��
		Item_Stamina* stamina = dynamic_cast<Item_Stamina*>(m_pItem);
		if (stamina != nullptr)
		{	m_pPlayer->StaminaRecovery(stamina->Get_Stamina());	}
	}
	m_pItem->Set_Destory();
}

void CollisionController::CheckHitFieldtoPlayer()
{
	//- �v���C���[���n�ʂ�艺���A���Ɉړ����Ă���Ƃ�
	if (m_pPlayer->Get_Pos().y < m_groundHeight && m_pPlayer->Get_Movement().y < 0.0f)
	{
		//- ���W��n�ʂ̍����ɍ��킹��
		m_pPlayer->Set_Pos({
			m_pPlayer->Get_Pos().x,m_groundHeight,m_pPlayer->Get_Pos().z });
		//- y�̈ړ��ʂ�0�ɂ���
		m_pPlayer->Set_Movement({
			m_pPlayer->Get_Movement().x,0.0f,m_pPlayer->Get_Movement().z });
	}
}

bool CollisionController::SearchBulletType()
{
	bool hit = false;

	//- �v���C���[
	if (m_pBullet->Get_Tag() == Bullet::E_TAG_TYPE::Player)
	{
		std::vector<EnemyBase*> enemys = m_pScene->Get_BaseObjects<EnemyBase>();
		for (EnemyBase* enemy : enemys)
		{
			m_pEnemy = enemy;
			//- �ڐG����
			if (CheckHitEnemytoBullet())
			{
				//- ��x���������烋�[�v�𔲂���
				hit = true;
				break;
			}
		}
	}
	//- �G
	else if (m_pBullet->Get_Tag() == Bullet::E_TAG_TYPE::Enemy)
	{
		AABB playerAABB = ChangeAABB(m_pPlayer->Get_Obj<Collider>());
		AABB bulletAABB = ChangeAABB(m_pBullet->Get_Obj<Collider>());
		if (AABBWithAABB(playerAABB, bulletAABB))
		{
			m_pPlayer->Get_Component<HPBase>()->Damage(m_pBullet->Get_Damage());
			m_pBullet->Set_Destory();
			hit = true;
		}
	}

	return hit;
}

bool CollisionController::CheckHitEnemytoBullet()
{
	AABB enemyAABB = ChangeAABB(m_pEnemy->Get_Obj<Collider>());
	AABB bulletAABB = ChangeAABB(m_pBullet->Get_Obj<Collider>());
	if (AABBWithAABB(enemyAABB, bulletAABB))
	{
		//- �G�̎�ނ𔻕ʂ��A�G���Ƃ̏������s��
		SearchEnemyTag();
		return true;
	}
	return false;
}

void CollisionController::SearchEnemyTag()
{
	if (m_pEnemy->Get_Obj<Collider>()->Get_Tag() == "ScorpionFish" ||
		m_pEnemy->Get_Obj<Collider>()->Get_Tag() == "TutorialEnemy" ||
		m_pEnemy->Get_Obj<Collider>()->Get_Tag() == "GlobeFish" || 
		m_pEnemy->Get_Obj<Collider>()->Get_Tag() == "Clownfish" )
	{
		m_pEnemy->Get_Component<HPBase>()->Damage(m_pBullet->Get_Damage());
		DirectX::XMFLOAT2 EffectSize = { 10.0f,10.0f };
		SpawnEffect(EffectSize);
		m_pBullet->Set_Destory();
	}
	//- �X�|�i�[�͓���ȈׁA�ʊ֐��ŏ���
	else if (m_pEnemy->Get_Obj<Collider>()->Get_Tag() == "Spawner")
	{	HitProcessSpawner(); }
}

void CollisionController::HitProcessSpawner()
{
	EnemySpawner* spawner = dynamic_cast<EnemySpawner*>(m_pEnemy);
	if (spawner != nullptr && spawner->Get_Spawning())
	{
		//- �������łȂ���΃_���[�W��^���Ȃ�
		m_pEnemy->Get_Component<HPBase>()->Damage(m_pBullet->Get_Damage());
	}
	DirectX::XMFLOAT2 EffectSize = { 12.0f,12.0f };
	SpawnEffect(EffectSize);
	m_pBullet->Set_Destory();
}

void CollisionController::SpawnEffect(DirectX::XMFLOAT2 size /* = {4.0f,4.0f}*/)
{
	//- �G�t�F�N�g�̐���
	Effect* effect = m_pScene->Add_Object<Effect>(2);
	effect->Load("Assets/Effect/Hit.png");
	//- �G�t�F�N�g�̍��W��e�̍��W�ɍ��킹��
	DirectX::XMFLOAT3 pos = m_pBullet->Get_Pos();
	pos.y += m_pBullet->Get_Size().y * 0.5f;

	effect->Set_Pos(pos);
	effect->Set_Size({ size.x,size.y,1.0f });
	effect->Set_UvDivision(10, 4);
	effect->Set_PlayTime(0.01f);
}

void CollisionController::CheckHitObstacletoPlayer(std::vector<Obstacle*>& obj)
{
	for (Obstacle* obstacle : obj)
	{
		//- ���̔��ƏՓ˂��邩
		AABB rockAABB = ChangeAABB(obstacle->Get_Obj<Collider>());
		AABB playerAABB = ChangeAABB(m_pPlayer->Get_Obj<Collider>());
		if (AABBWithAABB(playerAABB, rockAABB))
		{ ResolveOverlap(m_pPlayer, obstacle); }
	}
}


void CollisionController::CheckHitObstacletoBullet(std::vector<Obstacle*>& obj)
{
	AABB bulletAABB = ChangeAABB(m_pBullet->Get_Obj<Collider>());
	for (Obstacle* obstacle : obj)
	{
		//- ���̔��ƏՓ˂��邩
		AABB obsAABB = ChangeAABB(obstacle->Get_Obj<Collider>());
		if (AABBWithAABB(bulletAABB, obsAABB))
		{
			DirectX::XMFLOAT2 EffectSize = { 12.0f,12.0f };
			SpawnEffect(EffectSize);
			m_pBullet->Set_Destory();
			break;
		}
	}
}

bool CollisionController::AABBwithRay(const AABB& aabb, const Ray& ray)
{
	float tMin = 0.0f;		//��_��1�P�ʍŏ��l
	float tMax = 100000.0f; //��_��1�P�ʍő�l
	
	//- �����x�N�g����X����������Ȃ�0�ɋ߂���
	if (std::abs(ray.dir.x) < EPSILON)
	{
		//- X���ɕ��s�ł��邪�A���_��AABB�͈̔͊O�ɂ��邩
		if (ray.origin.x < aabb.min.x || ray.origin.x > aabb.max.x)
		{
			//- X���ɕ��s�ł���A���_�͈̔͊O�ɑ��݂���Ȃ�΁A
			//	X�������ɓ������Ƃ͂Ȃ����߁A������Ȃ�
			return false;
		}
	}
	else
	{
		//- X���ɕ��s�ł͂Ȃ��̂ŁA��_�����߂�
		/*
		���C�̌��_����AABB�̍ŏ��l�܂ł̋���(��)�����߂���A
		���C��1�P�ʂ̊Ԃɂǂꂾ���ړ�����̂������߂�
		�����C���ǂ̒��x���ɉ����Ĉړ������AABB�̖ʂɓ��B���邩�̋���
		*/
		float t1 = (aabb.min.x - ray.origin.x) / ray.dir.x;
		float t2 = (aabb.max.x - ray.origin.x) / ray.dir.x;

		
		tMin = std::max(tMin, std::min(t1, t2));//��_�̒l���������ق���tMin��
		tMax = std::min(tMax, std::max(t1, t2));//��_�̒l���傫���ق���tMax��

		//- tMin��tMax���傫���ƁA���鎞�Ԃ��o�鎞�Ԃ�����ɂȂ��Ă��܂�
		//�@�܂�������Ă��Ȃ�
		if (tMin > tMax)
		{	return false;
		}
	}

	//- Y���ɂ��Ă����l�ɔ���
	if (std::abs(ray.dir.y) < EPSILON)
	{
		if (ray.origin.y < aabb.min.y || ray.origin.y > aabb.max.y)
		{	return false;	}
	}
	else
	{
		float t1 = (aabb.min.y - ray.origin.y) / ray.dir.y;
		float t2 = (aabb.max.y - ray.origin.y) / ray.dir.y;
		tMin = std::max(tMin, std::min(t1, t2));
		tMax = std::min(tMax, std::max(t1, t2));
		if (tMin > tMax)
		{	return false;	}
	}

	//- Z���ɂ��Ă����l�ɔ���
	if (std::abs(ray.dir.z) < EPSILON)
	{
		if (ray.origin.z < aabb.min.z || ray.origin.z > aabb.max.z)
		{	return false;	}
	}
	else
	{
		float t1 = (aabb.min.z - ray.origin.z) / ray.dir.z;
		float t2 = (aabb.max.z - ray.origin.z) / ray.dir.z;
		tMin = std::max(tMin, std::min(t1, t2));
		tMax = std::min(tMax, std::max(t1, t2));
		if (tMin > tMax)
		{	return false;	}
	}

	//- �S�Ă̎��Ō������Ă���̂œ������Ă���
	return true;
}

void CollisionController::ResolveOverlap(Object* ObjDynamic, Object* ObjStatic)
{
	DirectX::XMFLOAT3 pos = ObjDynamic->Get_Pos();
	Collider* DynamicColl = ObjDynamic->Get_Obj<Collider>();
	Collider* StaticColl  = ObjStatic->Get_Obj<Collider>();
	//-�S�Ă̍����v�Z
	float dx1 = StaticColl->Get_wMinPoint().x - DynamicColl->Get_wMaxPoint().x;
	float dy1 = StaticColl->Get_wMinPoint().y - DynamicColl->Get_wMaxPoint().y;
	float dz1 = StaticColl->Get_wMinPoint().z - DynamicColl->Get_wMaxPoint().z;
	float dx2 = StaticColl->Get_wMaxPoint().x - DynamicColl->Get_wMinPoint().x;
	float dy2 = StaticColl->Get_wMaxPoint().y - DynamicColl->Get_wMinPoint().y;
	float dz2 = StaticColl->Get_wMaxPoint().z - DynamicColl->Get_wMinPoint().z;

	//- ��Βl���������ق����Z�b�g
	float dx = (std::abs(dx1) < std::abs(dx2)) ? dx1 : dx2;
	float dy = (std::abs(dy1) < std::abs(dy2)) ? dy1 : dy2;
	float dz = (std::abs(dz1) < std::abs(dz2)) ? dz1 : dz2;

	//- �ł������������������߂āA���̎��Ɉړ�����
	if (std::abs(dx) <= std::abs(dy) && std::abs(dx) <= std::abs(dz))
	{	pos.x += dx;	}
	else if (std::abs(dy) <= std::abs(dx) && std::abs(dy) <= std::abs(dz))
	{
		pos.y += dy;
		if (dy > 0.0f)
		{	m_groundHeight = ObjStatic->Get_Obj<Collider>()->Get_wMaxPoint().y;	}
	}
	else {	pos.z += dz;	}
	//- �ʒu���Z�b�g
	ObjDynamic->Set_Pos(pos);
}
