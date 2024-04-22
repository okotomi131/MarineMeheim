#ifndef __SCENE_STAGE_BASE_H__
#define __SCENE_STAGE_BASE_H__
/*
==================================================

インクルード

==================================================
*/
#include "../SceneBase.h"
#include "../SceneController.h"
#include "../../03_Object/Obstacle/Barrier.h"
#include "../../03_Object/Obstacle/Obstacle.h"
#include "../../03_Object/UI/Pouse/Pause.h"
#include "../../03_Object/UI/Pouse/GameOverPause.h"
#include <random>

class SceneStageBase : public SceneBase
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief ポーズ中の処理
	 * @param deltatime
	 */
	void DoPause(float deltatime);

	/**
	 * @brief ポーズ解除時の処理
	 * @param deltatime
	 */
	void UnPause(float deltatime);

	/**
	 * @brief ゲームオーバー表示
	 * @param deltatime
	 */
	void GameOver(float deltatime);

protected:
	/*
	==================================================

	構造体

	==================================================
	*/
	//- シーン内にオブジェクトを生成する際に使用する構造体
	struct CREATE_INFO
	{
		int CreateNum;				//生成する数
		DirectX::XMFLOAT3 minArea;	//生成するエリアの最小座標
		DirectX::XMFLOAT3 maxArea;	//生成するエリアの最大座標
		float minSize = 1.0f;		//生成するオブジェクトの最小サイズ
		float maxSize = 1.0f;		//生成するオブジェクトの最大サイズ
	};


	/**
	 * @brief コリジョンがある障害物を生成する
	 * @param info オブジェクト生成に必要な情報
	 * @param objName 生成するオブジェクトの名前
	 */
	inline void CreateCollisionObstacle(
		const CREATE_INFO& info, 
		const char* fileName = "None")
	{
		DirectX::XMFLOAT3 SpawnPos;
		DirectX::XMFLOAT3 SpawnSize;
		float SpawnRotY = 0.0f;
		for (int i = 0; i < info.CreateNum; i++)
		{
			std::random_device rd;
			std::mt19937 gen(rd());

			std::uniform_real_distribution<float> disX(info.minArea.x, info.maxArea.x);
			std::uniform_real_distribution<float> disZ(info.minArea.z, info.maxArea.z);
			std::uniform_real_distribution<float> disSize(info.minSize,info.maxSize);
			std::uniform_real_distribution<float> disRotY(0.0f, 360.0f);

			SpawnSize.x = disSize(gen);
			SpawnSize.y = SpawnSize.x;
			SpawnSize.z = SpawnSize.x;

			SpawnPos.x = disX(gen);
			SpawnPos.y = 0.0f;
			SpawnPos.z = disZ(gen);

			SpawnRotY = DirectX::XMConvertToRadians(disRotY(gen));

			Obstacle* obstacle = Add_Object<Obstacle>();
			obstacle->Load(fileName);
			obstacle->Set_Size(SpawnSize);
			obstacle->Set_CollSize();
			obstacle->Set_Pos(SpawnPos);
			obstacle->Set_Rot({ 0.0f,SpawnRotY,0.0f });
		}
	}

	/**
	 * @brief コリジョンがない装飾を生成する
	 * @param info オブジェクト生成に必要な情報
	 * @param objName 生成するオブジェクトの名前
	 */
	template<class T>
	inline void CreateNotCollObstacle(
		const CREATE_INFO& info,const bool& resizeX = false,const bool& resizeY = false)
	{
		DirectX::XMFLOAT3 SpawnPos;
		DirectX::XMFLOAT3 SpawnSize;
		float SpawnRotY = 0.0f;
		for (int i = 0; i < info.CreateNum; i++)
		{
			std::random_device rd;
			std::mt19937 gen(rd());

			std::uniform_real_distribution<float> disX(info.minArea.x, info.maxArea.x);
			std::uniform_real_distribution<float> disZ(info.minArea.z, info.maxArea.z);
			std::uniform_real_distribution<float> disSize(info.minSize,info.maxSize);

			SpawnSize.x = 2.5f;
			SpawnSize.y = disSize(gen);
			SpawnSize.z = 1.0f;

			SpawnPos.x = disX(gen);
			SpawnPos.y = SpawnSize.y - SpawnSize.x;
			SpawnPos.z = disZ(gen);

			T* Ornament = Add_Object<T>();
			Ornament->Set_Size(SpawnSize);
			Ornament->Set_Pos(SpawnPos);
		}
	}

	/**
	 * @brief 敵の生成
	 * @param info オブジェクト生成に必要な情報
	 */
	template<class T>
	inline void CreateEnemy(const CREATE_INFO& info)
	{

		//- 与えられた型の親がEnemyBaseであるかチェック
		/*
		is_base_of...基底クラスかどうかをチェックする
		*/
		static_assert(std::is_base_of<class EnemyBase, T>::value,
			"与えられた型が敵ではありません");

		//- 生成する座標をエリア内座標の中でランダムで設定
		for (int i = 0; i < info.CreateNum; i++)
		{
			std::random_device rd;
			std::mt19937 gen(rd());

			std::uniform_real_distribution<float> disX(info.minArea.x, info.maxArea.x);
			std::uniform_real_distribution<float> disZ(info.minArea.z, info.maxArea.z);

			DirectX::XMFLOAT3 randomPos;
			randomPos.x = disX(gen);
			randomPos.y = 0.0f;
			randomPos.z = disZ(gen);

			T* enemy = Add_Object<T>();
			enemy->Set_SpawnPos(randomPos);
		}
	}

	/**
	 * @brief プレイヤーの生成
	 * プレイヤーとプレイヤーカメラの生成
	 */
	void CreatePlayer();

	/**
	 * @brief フィールドの作成
	 * フィールドおよびライト・スカイドームの作成
	 */
	void CreateField();

	/**
	 * @brief ステージ制限の制作
	 */
	void CreateBarrier();

	/**
	 * @brief シーン終了の判定が成立しているかを確認する
	 */
	void CheckEndSceneFlag(float deltatime);

	/**
	 * @brief シーンに必要なUIを生成する
	 */
	void CreateSceneUI();

	/**
	 * @brief 各フラグに合うシーンに移動
	 */
	inline void MoveScene()
	{
		//- クリア
		if (m_Fade->Get_State() == Fade::E_FADE_STATE::Finish && m_bClear)
		{
			//- 現在のシーン状態を取得
			//- チュートリアルまでのシーン数を引き、ステージ番号にする
			int stageNum = SceneController::Get_CurState();
			stageNum -= SceneController::E_SCENE_STATE::Tutorial;

			std::string ClearTimeName = "ClearTimeStage" + std::to_string(stageNum);
			DataSave::Set_Data<float>(ClearTimeName,&m_clearTime);


			int curClearStageNum = DataSave::Get_Data<int>("ClearStageNum");
			//- 現在のステージがクリアステージより大きい場合は更新
			if (stageNum > curClearStageNum)
			{
				DataSave::Set_Data<int>("ClearStageNum", &stageNum);
				DataSave::Save();
			}

			SceneController::Set_SceneState(SceneController::Result);
		}
	}

	const float LIMIT_STAGE_SIZE_X = 200.0f;
	const float LIMIT_STAGE_SIZE_Z = 200.0f;

	//- シーン内に必ずあるオブジェクト
	SceneBase* m_pScene = nullptr;
	Pause* m_pPause = nullptr;
	GameOverPause* m_pGameOverPause = nullptr;
	class Player* m_pPlayer = nullptr;
	class CameraPlayer* m_pCamera = nullptr;
	class RemainEnemy*  m_pRemainEnemy = nullptr;


	float m_clearTime = 0.0f;	//クリアタイム
	bool m_bPlayerDead = false;	//プレイヤーが死んだか
	bool m_bClear = false;		//クリアしたか
	bool m_bPauseSceneChange = false;	//ポーズ中にシーンを変更するか

};

#endif // !__SCENE_STAGE_BASE_H__

