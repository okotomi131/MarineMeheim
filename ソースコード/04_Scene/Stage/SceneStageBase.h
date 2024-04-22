#ifndef __SCENE_STAGE_BASE_H__
#define __SCENE_STAGE_BASE_H__
/*
==================================================

�C���N���[�h

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
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �|�[�Y���̏���
	 * @param deltatime
	 */
	void DoPause(float deltatime);

	/**
	 * @brief �|�[�Y�������̏���
	 * @param deltatime
	 */
	void UnPause(float deltatime);

	/**
	 * @brief �Q�[���I�[�o�[�\��
	 * @param deltatime
	 */
	void GameOver(float deltatime);

protected:
	/*
	==================================================

	�\����

	==================================================
	*/
	//- �V�[�����ɃI�u�W�F�N�g�𐶐�����ۂɎg�p����\����
	struct CREATE_INFO
	{
		int CreateNum;				//�������鐔
		DirectX::XMFLOAT3 minArea;	//��������G���A�̍ŏ����W
		DirectX::XMFLOAT3 maxArea;	//��������G���A�̍ő���W
		float minSize = 1.0f;		//��������I�u�W�F�N�g�̍ŏ��T�C�Y
		float maxSize = 1.0f;		//��������I�u�W�F�N�g�̍ő�T�C�Y
	};


	/**
	 * @brief �R���W�����������Q���𐶐�����
	 * @param info �I�u�W�F�N�g�����ɕK�v�ȏ��
	 * @param objName ��������I�u�W�F�N�g�̖��O
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
	 * @brief �R���W�������Ȃ������𐶐�����
	 * @param info �I�u�W�F�N�g�����ɕK�v�ȏ��
	 * @param objName ��������I�u�W�F�N�g�̖��O
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
	 * @brief �G�̐���
	 * @param info �I�u�W�F�N�g�����ɕK�v�ȏ��
	 */
	template<class T>
	inline void CreateEnemy(const CREATE_INFO& info)
	{

		//- �^����ꂽ�^�̐e��EnemyBase�ł��邩�`�F�b�N
		/*
		is_base_of...���N���X���ǂ������`�F�b�N����
		*/
		static_assert(std::is_base_of<class EnemyBase, T>::value,
			"�^����ꂽ�^���G�ł͂���܂���");

		//- ����������W���G���A�����W�̒��Ń����_���Őݒ�
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
	 * @brief �v���C���[�̐���
	 * �v���C���[�ƃv���C���[�J�����̐���
	 */
	void CreatePlayer();

	/**
	 * @brief �t�B�[���h�̍쐬
	 * �t�B�[���h����у��C�g�E�X�J�C�h�[���̍쐬
	 */
	void CreateField();

	/**
	 * @brief �X�e�[�W�����̐���
	 */
	void CreateBarrier();

	/**
	 * @brief �V�[���I���̔��肪�������Ă��邩���m�F����
	 */
	void CheckEndSceneFlag(float deltatime);

	/**
	 * @brief �V�[���ɕK�v��UI�𐶐�����
	 */
	void CreateSceneUI();

	/**
	 * @brief �e�t���O�ɍ����V�[���Ɉړ�
	 */
	inline void MoveScene()
	{
		//- �N���A
		if (m_Fade->Get_State() == Fade::E_FADE_STATE::Finish && m_bClear)
		{
			//- ���݂̃V�[����Ԃ��擾
			//- �`���[�g���A���܂ł̃V�[�����������A�X�e�[�W�ԍ��ɂ���
			int stageNum = SceneController::Get_CurState();
			stageNum -= SceneController::E_SCENE_STATE::Tutorial;

			std::string ClearTimeName = "ClearTimeStage" + std::to_string(stageNum);
			DataSave::Set_Data<float>(ClearTimeName,&m_clearTime);


			int curClearStageNum = DataSave::Get_Data<int>("ClearStageNum");
			//- ���݂̃X�e�[�W���N���A�X�e�[�W���傫���ꍇ�͍X�V
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

	//- �V�[�����ɕK������I�u�W�F�N�g
	SceneBase* m_pScene = nullptr;
	Pause* m_pPause = nullptr;
	GameOverPause* m_pGameOverPause = nullptr;
	class Player* m_pPlayer = nullptr;
	class CameraPlayer* m_pCamera = nullptr;
	class RemainEnemy*  m_pRemainEnemy = nullptr;


	float m_clearTime = 0.0f;	//�N���A�^�C��
	bool m_bPlayerDead = false;	//�v���C���[�����񂾂�
	bool m_bClear = false;		//�N���A������
	bool m_bPauseSceneChange = false;	//�|�[�Y���ɃV�[����ύX���邩

};

#endif // !__SCENE_STAGE_BASE_H__

