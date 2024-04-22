/*********************************************************************
 * @file   CollisionController.cpp
 * @brief  当たり判定の管理を行う
 *********************************************************************/

 /*
 ===================================================================

インクルード 

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


float CollisionController::m_groundHeight	= 0.0f;		//地面の高さ
SceneBase*  CollisionController::m_pScene	= nullptr;	//シーン変数
Player*		CollisionController::m_pPlayer	= nullptr;	//プレイヤー変数
Bullet*		CollisionController::m_pBullet	= nullptr;	//弾変数
EnemyBase*  CollisionController::m_pEnemy	= nullptr;	//敵変数
ItemBase*	CollisionController::m_pItem		= nullptr;	//アイテム変数

void CollisionController::Update(float deltatime)
{
	//- ゲームシーンに必ずあるものを取得
	m_pScene  = SceneController::Get_Scene();
	m_pPlayer = m_pScene->Get_Object<Player>();
	Field* field  = m_pScene->Get_Object<Field>();

	//- 地面処理初期化
	m_groundHeight = 0.0f;
	m_groundHeight = field->Get_Pos().y;

	//- 岩とプレイヤーのコリジョン判定
	std::vector<Obstacle*> obstacles = m_pScene->Get_Objects<Obstacle>();
	CheckHitObstacletoPlayer(obstacles);

	//- アイテムとプレイヤーのコリジョン判定
	std::vector<ItemBase*> items = m_pScene->Get_BaseObjects<ItemBase>();
	if (items.size() > 0)
	{	CheckHitItemtoPlayer(items);}


	//- プレイヤーと地面の判定
	CheckHitFieldtoPlayer();

	//- 球
	std::vector<Bullet*> bullets = m_pScene->Get_Objects<Bullet>();
	for (Bullet* bullet : bullets)
	{
		m_pBullet = bullet;
		AABB bulletAABB = ChangeAABB(m_pBullet->Get_Obj<Collider>());
		//- 弾の種類を判別し、処理が終了したら次の弾へ
		if(SearchBulletType()){	continue; }

		//- 壁との判定
		CheckHitObstacletoBullet(obstacles);

		//- 地面との判定
		if (m_pBullet->Get_Pos().y < m_groundHeight)
		{	
			//- 弾を消すと同時にエフェクトを生成
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
			//- アイテムの種類を判別し、アイテムごとの処理を行う
			SearchItemTag();
			break;
		}
	}
}

void CollisionController::SearchItemTag()
{
	//- アイテムの種類を判別
	if (m_pItem->Get_Obj<Collider>()->Get_Tag() == "ItemHeal")
	{
		//- 回復アイテム
		Item_Heal* heal = dynamic_cast<Item_Heal*>(m_pItem);
		if (heal != nullptr)
		{	m_pPlayer->Get_Component<HPBase>()->Heal(heal->Get_Heal());	}
	}
	else if (m_pItem->Get_Obj<Collider>()->Get_Tag() == "ItemStamina")
	{
		//- スタミナアイテム
		Item_Stamina* stamina = dynamic_cast<Item_Stamina*>(m_pItem);
		if (stamina != nullptr)
		{	m_pPlayer->StaminaRecovery(stamina->Get_Stamina());	}
	}
	m_pItem->Set_Destory();
}

void CollisionController::CheckHitFieldtoPlayer()
{
	//- プレイヤーが地面より下かつ、下に移動しているとき
	if (m_pPlayer->Get_Pos().y < m_groundHeight && m_pPlayer->Get_Movement().y < 0.0f)
	{
		//- 座標を地面の高さに合わせる
		m_pPlayer->Set_Pos({
			m_pPlayer->Get_Pos().x,m_groundHeight,m_pPlayer->Get_Pos().z });
		//- yの移動量を0にする
		m_pPlayer->Set_Movement({
			m_pPlayer->Get_Movement().x,0.0f,m_pPlayer->Get_Movement().z });
	}
}

bool CollisionController::SearchBulletType()
{
	bool hit = false;

	//- プレイヤー
	if (m_pBullet->Get_Tag() == Bullet::E_TAG_TYPE::Player)
	{
		std::vector<EnemyBase*> enemys = m_pScene->Get_BaseObjects<EnemyBase>();
		for (EnemyBase* enemy : enemys)
		{
			m_pEnemy = enemy;
			//- 接触判定
			if (CheckHitEnemytoBullet())
			{
				//- 一度当たったらループを抜ける
				hit = true;
				break;
			}
		}
	}
	//- 敵
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
		//- 敵の種類を判別し、敵ごとの処理を行う
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
	//- スポナーは特殊な為、別関数で処理
	else if (m_pEnemy->Get_Obj<Collider>()->Get_Tag() == "Spawner")
	{	HitProcessSpawner(); }
}

void CollisionController::HitProcessSpawner()
{
	EnemySpawner* spawner = dynamic_cast<EnemySpawner*>(m_pEnemy);
	if (spawner != nullptr && spawner->Get_Spawning())
	{
		//- 生成中でなければダメージを与えない
		m_pEnemy->Get_Component<HPBase>()->Damage(m_pBullet->Get_Damage());
	}
	DirectX::XMFLOAT2 EffectSize = { 12.0f,12.0f };
	SpawnEffect(EffectSize);
	m_pBullet->Set_Destory();
}

void CollisionController::SpawnEffect(DirectX::XMFLOAT2 size /* = {4.0f,4.0f}*/)
{
	//- エフェクトの生成
	Effect* effect = m_pScene->Add_Object<Effect>(2);
	effect->Load("Assets/Effect/Hit.png");
	//- エフェクトの座標を弾の座標に合わせる
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
		//- この箱と衝突するか
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
		//- この箱と衝突するか
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
	float tMin = 0.0f;		//交点の1単位最小値
	float tMax = 100000.0f; //交点の1単位最大値
	
	//- 方向ベクトルのX成分が限りなく0に近いか
	if (std::abs(ray.dir.x) < EPSILON)
	{
		//- X軸に平行であるが、原点がAABBの範囲外にあるか
		if (ray.origin.x < aabb.min.x || ray.origin.x > aabb.max.x)
		{
			//- X軸に並行であり、原点の範囲外に存在するならば、
			//	X軸方向に動くことはないため、当たらない
			return false;
		}
	}
	else
	{
		//- X軸に平行ではないので、交点を求める
		/*
		レイの原点からAABBの最小値までの距離(※)を求めた後、
		レイが1単位の間にどれだけ移動するのかを求める
		※レイがどの程度軸に沿って移動すればAABBの面に到達するかの距離
		*/
		float t1 = (aabb.min.x - ray.origin.x) / ray.dir.x;
		float t2 = (aabb.max.x - ray.origin.x) / ray.dir.x;

		
		tMin = std::max(tMin, std::min(t1, t2));//交点の値が小さいほうをtMinに
		tMax = std::min(tMax, std::max(t1, t2));//交点の値が大きいほうをtMaxに

		//- tMinがtMaxが大きいと、入る時間が出る時間よりも後になってしまう
		//　つまり交差していない
		if (tMin > tMax)
		{	return false;
		}
	}

	//- Y軸についても同様に判定
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

	//- Z軸についても同様に判定
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

	//- 全ての軸で交差しているので当たっている
	return true;
}

void CollisionController::ResolveOverlap(Object* ObjDynamic, Object* ObjStatic)
{
	DirectX::XMFLOAT3 pos = ObjDynamic->Get_Pos();
	Collider* DynamicColl = ObjDynamic->Get_Obj<Collider>();
	Collider* StaticColl  = ObjStatic->Get_Obj<Collider>();
	//-全ての差を計算
	float dx1 = StaticColl->Get_wMinPoint().x - DynamicColl->Get_wMaxPoint().x;
	float dy1 = StaticColl->Get_wMinPoint().y - DynamicColl->Get_wMaxPoint().y;
	float dz1 = StaticColl->Get_wMinPoint().z - DynamicColl->Get_wMaxPoint().z;
	float dx2 = StaticColl->Get_wMaxPoint().x - DynamicColl->Get_wMinPoint().x;
	float dy2 = StaticColl->Get_wMaxPoint().y - DynamicColl->Get_wMinPoint().y;
	float dz2 = StaticColl->Get_wMaxPoint().z - DynamicColl->Get_wMinPoint().z;

	//- 絶対値が小さいほうをセット
	float dx = (std::abs(dx1) < std::abs(dx2)) ? dx1 : dx2;
	float dy = (std::abs(dy1) < std::abs(dy2)) ? dy1 : dy2;
	float dz = (std::abs(dz1) < std::abs(dz2)) ? dz1 : dz2;

	//- 最も差が小さい軸を求めて、その軸に移動する
	if (std::abs(dx) <= std::abs(dy) && std::abs(dx) <= std::abs(dz))
	{	pos.x += dx;	}
	else if (std::abs(dy) <= std::abs(dx) && std::abs(dy) <= std::abs(dz))
	{
		pos.y += dy;
		if (dy > 0.0f)
		{	m_groundHeight = ObjStatic->Get_Obj<Collider>()->Get_wMaxPoint().y;	}
	}
	else {	pos.z += dz;	}
	//- 位置をセット
	ObjDynamic->Set_Pos(pos);
}
