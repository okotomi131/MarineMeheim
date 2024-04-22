/*********************************************************************
 * @file   GlobeFish.cpp
 * @brief  敵(フグ)クラス
 *********************************************************************/
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "GlobeFish.h"

#include "../../Player/Player.h"
#include "../../Bullet/Bullet.h"
#include "../../Obstacle/Obstacle.h"
#include "../../Weapon/EnemyWeapon/WeaponGlobeFish.h"

#include "../../../01_System/Collison/CollisionController.h"
#include "../../../01_System/Input/Input.h"

void GlobeFish::Load()
{
	Model::Preload("Assets/Model/Enemy/GlobeFish.obj");
}

void GlobeFish::Init()
{
	EnemyBase::Init();

	m_pHP->Set_MaxHP(40.0f) ;

	//- モデル設定
	{
		Add_Component<Shader>()->Load(
			"Assets/Shader/VS_Object.cso",
			"Assets/Shader/PS_Light.cso");
		Add_Component<Model>()->Load("Assets/Model/Enemy/GlobeFish.obj");
	}

	m_size = { 2.0f,2.0f,2.0f };

	//- コライダー設定
	{
		Collider* coll = Add_Obj<Collider>();
		coll->Set_Tag("GlobeFish");
		coll->Set_Pos({ 0.0f,1.0f,0.0f });
		coll->Set_WorldMatrix(Get_WorldMatrix());
	}
	//- 攻撃設定
	m_pWeapon = Add_Obj<WeaponGlobeFish>();

	//- ステート
	ChangeState(E_ENEMY_STATE::Spawn);

	m_MoveSpeed = 0.05f;
}