/*********************************************************************
 * @file   WeaponBase.cpp
 * @brief  武器の基底クラス
 *********************************************************************/
/*
==================================================

インクルード

==================================================
*/
#include "WeaponBase.h"

#include "../Camera/CameraPlayer.h"
#include "../Player/Player.h"
#include "../Enemy/EnemyBase.h"

#include "../../01_System/Text/TextDraw.h"
#include "../../02_Component/Sprite/Sprite.h"

#include "../../04_Scene/SceneController.h"
#include "../../04_Scene/SceneBase.h"

void WeaponBase::Init()
{	
	m_weaponData.multiShotNum > 1 ? m_bMultiShot = true : m_bMultiShot = false;
}

void WeaponBase::AttackPlayer(float deltatime)
{
	m_curRateTime += deltatime;
	

	if (0 <= m_curBulletNum && m_weaponData.rate <= m_curRateTime)
	{
		m_pScene = SceneController::Get_Scene();
		Bullet* bullet = m_pScene->Add_Object<Bullet>();
		CameraPlayer* camera = m_pScene->Get_Object<CameraPlayer>();
		Player* player = m_pScene->Get_Object<Player>();
	
		bullet->Set_Tag(Bullet::E_TAG_TYPE::Player);
		bullet->Set_BulletData(m_weaponData.bulletData);
		bullet->Set_Size({ 
			m_weaponData.bulletSize,
			m_weaponData.bulletSize,
			m_weaponData.bulletSize });

		DirectX::XMFLOAT3 pos = player->Get_Pos();
		float AddSpawnPosY = 2.35f;
		pos.y += AddSpawnPosY;
		
		bullet->Set_Pos(pos);
		DirectX::XMFLOAT3 dir = camera->Get_LookPoint();
		AddSpawnPosY = 0.05f;
		dir.y += AddSpawnPosY;
		bullet->Set_Direction(dir);

		m_curBulletNum--;	 //弾数を減らす
		m_curRateTime = 0.0f;//レートをリセット
		m_curReloadTime = 0.0f;
	}
}

void WeaponBase::AttackEnemy(float deltatime,EnemyBase* enemy)
{
	m_curRateTime += deltatime;

	if (0 <= m_curBulletNum && m_weaponData.rate <= m_curRateTime)
	{
		m_pScene = SceneController::Get_Scene();
		std::vector<Bullet*> bullets;
		for (int i = 0; i < m_weaponData.multiShotNum; i++)
		{
			Bullet* bullet = m_pScene->Add_Object<Bullet>();
			bullets.push_back(bullet);

		}
		for (Bullet* bullet : bullets)
		{
			bullet->Set_Tag(Bullet::E_TAG_TYPE::Enemy);
			bullet->Set_BulletData(m_weaponData.bulletData);
			bullet->Set_Size({
			m_weaponData.bulletSize,
			m_weaponData.bulletSize,
			m_weaponData.bulletSize });
			DirectX::XMFLOAT3 pos = enemy->Get_Pos();
			float AddSpawnPosY = 1.0f;
			pos.y += AddSpawnPosY;
			bullet->Set_Pos(pos);
			DirectX::XMFLOAT3 dir;
			if (m_bMultiShot)
			{
				//- 正面方向のベクトルを基準にランダム方向にする
				DirectX::XMVECTOR vForward = enemy->Get_vForward();
				DirectX::XMFLOAT3 forward;
				DirectX::XMStoreFloat3(&forward, vForward);
				// ランダムな方向を生成するための角度を設定
				float angleH = ((float)rand() / RAND_MAX - 0.5f) * m_weaponData.SpreadAngle.x;
				float angleV = ((float)rand() / RAND_MAX - 0.5f) * m_weaponData.SpreadAngle.y;

				// 水平方向と垂直方向の回転を適用してランダムな方向を計算
				DirectX::XMMATRIX matRot = DirectX::XMMatrixRotationRollPitchYaw(angleV, angleH, 0.0f);
				DirectX::XMVECTOR vDir = DirectX::XMVector3TransformNormal(vForward, matRot);
				DirectX::XMStoreFloat3(&dir, vDir);
			}
			else
			{
				DirectX::XMStoreFloat3(&dir, enemy->Get_vForward());
			}
			bullet->Set_Direction(dir);
		}

		m_curBulletNum--;	 //弾数を減らす
		m_curRateTime = 0.0f;//レートをリセット
		m_curReloadTime = 0.0f;
	}
}

bool WeaponBase::Reload(float deltatime)
{
	m_curReloadTime += deltatime;
	if (m_weaponData.reloadTime <= m_curReloadTime)
	{
		m_curBulletNum = m_weaponData.bulletNum;
		m_curReloadTime = 0.0f;
		m_bReload = false;
		return true;
	}

	return false;
}

