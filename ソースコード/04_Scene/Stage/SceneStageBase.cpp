#include "SceneStageBase.h"

#include "../../01_System/Collison/CollisionController.h"
#include "../../01_System/Input/Input.h"
#include "../../03_Object/Player/Player.h"
#include "../../03_Object/Camera/CameraPlayer.h"
#include "../../03_Object/UI/CrossHair/Crosshair.h"
#include "../../03_Object/UI/PlayerHPBar.h"
#include "../../03_Object/UI/BulletNum/BulletNumUI.h"
#include "../../03_Object/UI/Stamina/StaminaUI.h"
#include "../../03_Object/UI/RemainEnemy/RemainEnemy.h"
#include "../../03_Object/Light/LightBase.h"
#include "../../03_Object/Obstacle/Field.h"
#include "../../03_Object/Effect/Effect.h"
#include "../../03_Object/Sky/Sky.h"
#include "../../03_Object/Enemy/Spawner/EnemySpawner.h"
#include "../../03_Object/Player/Player.h"
#include "../../03_Object/Obstacle/Barrier.h"


void SceneStageBase::Init()
{
	m_pGameOverPause = Add_Object<GameOverPause>(4);
	m_pGameOverPause->UnDrawPause();
	m_pPause = Add_Object<Pause>(4);
}

void SceneStageBase::DoPause(float deltatime)
{
	m_pPause->Update(deltatime);
	m_Fade->Update(deltatime);

	//- 続ける
	if (m_pPause->Get_Restart())
	{
		UnPause(deltatime);
		SceneController::Set_Pause(false);
		m_pPause->AllFlagReset();
	}
	//- やりなおす
	else if (m_pPause->Get_NewStart())
	{
		if (!m_bPauseSceneChange) {
			UnPause(deltatime);
			m_bPauseSceneChange = true;
			m_Fade->FadeOut();
		}
		if (m_Fade->Get_State() == Fade::E_FADE_STATE::Finish)
		{
			//- 現在のシーン状態を取得
			SceneController::E_SCENE_STATE state = SceneController::Get_CurState();
			SceneController::Set_SceneState(state);
			m_pPause->AllFlagReset();
			SceneController::Set_Pause(false);
		}
	}
	//- セレクトに戻る
	else if (m_pPause->Get_ReTreat())
	{
		if (!m_bPauseSceneChange) {
			UnPause(deltatime);
			m_bPauseSceneChange = true;
			m_Fade->FadeOut();
		}
		if (m_Fade->Get_State() == Fade::E_FADE_STATE::Finish)
		{
			//- 現在のシーン状態を取得
			SceneController::Set_SceneState(SceneController::Select);
			m_pPause->AllFlagReset();
			SceneController::Set_Pause(false);
		}
	}
	else
	{
		m_pPause->DrawPause();
	}

}

void SceneStageBase::UnPause(float deltatime)
{
	m_pPause->UnDrawPause();
	m_pGameOverPause->UnDrawPause();
}

void SceneStageBase::GameOver(float deltatime)
{
	SceneController::Set_BaseUpdatePause(true);
	m_pGameOverPause->Update(deltatime);
	m_Fade->Update(deltatime);
	
	if (m_pGameOverPause->Get_NewStart())
	{
		if (!m_bPauseSceneChange) {
			UnPause(deltatime);
			m_bPauseSceneChange = true;
			m_Fade->FadeOut();
		}
		if (m_Fade->Get_State() == Fade::E_FADE_STATE::Finish)
		{
			//- 現在のシーン状態を取得
			SceneController::E_SCENE_STATE state = SceneController::Get_CurState();
			SceneController::Set_SceneState(state);
			m_pGameOverPause->AllFlagReset();
			SceneController::Set_BaseUpdatePause(false);
		}
	}
	else if (m_pGameOverPause->Get_ReTreat())
	{
		if (!m_bPauseSceneChange) {
			UnPause(deltatime);
			m_bPauseSceneChange = true;
			m_Fade->FadeOut();
		}
		if (m_Fade->Get_State() == Fade::E_FADE_STATE::Finish)
		{
			//- 現在のシーン状態を取得
			SceneController::Set_SceneState(SceneController::Select);
			m_pGameOverPause->AllFlagReset();
			SceneController::Set_BaseUpdatePause(false);
		}
	}
	else
	{
		m_pGameOverPause->DrawPause();
	}
}

void SceneStageBase::CreatePlayer()
{
	m_pCamera = Add_Object<CameraPlayer>();
	m_pPlayer = Add_Object<Player>();
	m_pPlayer->Set_Pos({ 0.0f,0.0f,-15.0f });
	m_pPlayer->Set_LimitPos({ LIMIT_STAGE_SIZE_X,LIMIT_STAGE_SIZE_Z });
	m_pCamera->Set_TargetObj(m_pPlayer);
}

void SceneStageBase::CreateField()
{
	Add_Object<Field>();
	Add_Object<LightBase>();
	Add_Object<Sky>();
}

void SceneStageBase::CreateBarrier()
{
	Barrier* barrier = Add_Object<Barrier>();
	barrier->Set_Size({ LIMIT_STAGE_SIZE_X,100.0f,0.0f });
	barrier->Set_Pos({ 0.0f,10.0f,LIMIT_STAGE_SIZE_Z });
	barrier = Add_Object<Barrier>();
	barrier->Set_Size({ LIMIT_STAGE_SIZE_X,100.0f,0.0f });
	barrier->Set_Pos({ 0.0f,10.0f,-LIMIT_STAGE_SIZE_Z });
	barrier->Set_Rot({ 0.0f,DirectX::XMConvertToRadians(180.0f),0.0f });
	barrier = Add_Object<Barrier>();
	barrier->Set_Size({ LIMIT_STAGE_SIZE_X,100.0f,0.0f });
	barrier->Set_Pos({ LIMIT_STAGE_SIZE_X,10.0f,0.0f });
	barrier->Set_Rot({ 0.0f,DirectX::XMConvertToRadians(90.0f),0.0f });
	barrier = Add_Object<Barrier>();
	barrier->Set_Size({ LIMIT_STAGE_SIZE_X,100.0f,0.0f });
	barrier->Set_Pos({ -LIMIT_STAGE_SIZE_X,10.0f,0.0f });
	barrier->Set_Rot({ 0.0f,DirectX::XMConvertToRadians(-90.0f),0.0f });
}

void SceneStageBase::CheckEndSceneFlag(float deltatime)
{
	int enemyNum = m_pRemainEnemy->Get_CurEnemyNum();
	if (enemyNum <= 0 && m_Fade->Get_State() == Fade::E_FADE_STATE::Stop)
	{
		m_bClear = true;
		m_Fade->FadeOut();
	}
	else if (m_pPlayer->Get_IsDead())
	{
		m_bPlayerDead = true;
	}
}

void SceneStageBase::CreateSceneUI()
{
	PlayerHPBar* playerHpBar = Add_Object<PlayerHPBar>(3);
	playerHpBar->Set_MaxHP(m_pPlayer->Get_Component<HPBase>()->Get_HpData().maxHp);

	BulletNumUI* bulletNum = Add_Object<BulletNumUI>(3);
	bulletNum->Set_Weapon(m_pPlayer->Get_Weapon());

	std::vector<EnemyBase*> enemys = Get_BaseObjects<EnemyBase>();
	m_pRemainEnemy = Add_Object<RemainEnemy>(3);
	m_pRemainEnemy->Set_EnemyMaxNum(static_cast<int>(enemys.size()));

	Add_Object<Crosshair>(3);
	Add_Object<StaminaUI>(3);
}
