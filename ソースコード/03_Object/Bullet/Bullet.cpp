/*
	Bullet.cpp
	弾
*/
#include "Bullet.h"

#include "../Player/Player.h"
#include "../Collider/Collider.h"

#include "../../02_Component/Shader/Shader.h"
#include "../../02_Component/Model/Model.h"

#include "../../04_Scene/SceneBase.h"
#include "../../04_Scene/SceneController.h"

/// <summary>
/// 読み込み
/// </summary>
void Bullet::Load()
{
	Model::Preload("Assets/Model/Object/Sphere.obj");
}

/// <summary>
/// 初期化処理
/// </summary>
void Bullet::Init()
{
	Collider* coll = Add_Obj<Collider>();
	coll->Set_Tag("Bullet");
	coll->Set_Pos({ 0.0f,1.0f,0.0f });
	coll->Set_WorldMatrix(Get_WorldMatrix());

	Add_Component<Shader>()->Load(
		"Assets/Shader/VS_Color.cso",
		"Assets/Shader/PS_Color.cso");
	Add_Component<Model>()->Load("Assets/Model/Object/Sphere.obj");

	m_direction = { 0.0f, 0.0f, 0.0f };
	m_bulletData.damage = 10.0f;
	m_bulletData.speed	= 10.0f;
	m_bulletData.range	= 100.0f;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltatime">デルタタイム</param>
void Bullet::Update(float deltatime)
{
	Get_Obj<Collider>()->Set_WorldMatrix(Get_WorldMatrix());
	SceneBase* scene = SceneController::Get_Scene();
	Player* player = scene->Get_Object<Player>();

	//- 時間更新
	m_curTime += deltatime;
	
	m_pos.x += m_direction.x * m_bulletData.speed * deltatime;
	m_pos.y += m_direction.y * m_bulletData.speed * deltatime;
	m_pos.z += m_direction.z * m_bulletData.speed * deltatime;

	//- 射程距離をプレイヤーの座標からにする
	DirectX::XMFLOAT3 diff;
	diff.x = player->Get_Pos().x - m_pos.x;
	diff.y = player->Get_Pos().y - m_pos.y;
	diff.z = player->Get_Pos().z - m_pos.z;


	//- 現在の距離
	float length;
	DirectX::XMStoreFloat(
		&length,
		DirectX::XMVector3LengthSq(DirectX::XMLoadFloat3(&diff))
	);



	//- 射程距離を超えたら消滅
	if(length > m_bulletData.range)
	{	Set_Destory();	}

	//- 生存時間を超えたら消滅
	if (m_curTime > m_deleteTime) 
	{
		m_curTime = 0.0f;
		Set_Destory(); 
	}
}
