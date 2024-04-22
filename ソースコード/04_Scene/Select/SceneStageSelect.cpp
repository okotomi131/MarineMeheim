/*********************************************************************
 * @file   SceneStageSelect.cpp
 * @brief  �X�e�[�W�Z���N�g�V�[��
 *********************************************************************/
/*
==================================================

�C���N���[�h

==================================================
*/
#include "SceneStageSelect.h"
#include "../../01_System/Input/Input.h"

#include "../../03_Object/UI/Logo/TitleKeyText.h"
#include "../../03_Object/UI/Logo/TitleKeyTextBack.h"
#include "../../03_Object/UI/Button/ButtonBase.h"
#include "../../03_Object/Image/ImageDrawer.h"
#include "../../03_Object/BGM/BGM.h"

#include "../../04_Scene/SceneController.h"

void SceneStageSelect::Init()
{
	ImageDrawer* background = Add_Object<ImageDrawer>(0);
	background->Set_Name("Background");
	background->CreateImage("Assets/Texture/UI/SelectBG.png", true);

	//- �{�^���̍쐬
	CreateButton();
	//- �X�e�[�W�摜�̍쐬
	CreateStageView();

	m_pStageButtons = Get_Objects<ButtonBase>();

	BGM* bgm = Add_Object<BGM>();
	bgm->Register("Select", "Assets/Sound/BGM/Lobby.wav");
	bgm->Play("Select");

	m_Fade->FadeIn();
}

void SceneStageSelect::CreateStageView()
{
	m_viewImageSize = { 500.0f,400.0f };
	m_viewImagePos  = { 100.0f,SPRITE_CENTER_POS_Y(m_viewImageSize.y) };
	DirectX::XMFLOAT2 outPos = { 9999.9f,9999.9f };
	std::vector<std::string> stageName = 
	{ "TutorialView","Stage1View","Stage2View","Stage3View","Stage4View","Stage5View","Unlock" };
	
	std::string path = "Assets/Texture/UI/";

	for (std::string name : stageName)
	{
		ImageDrawer* view = Add_Object<ImageDrawer>(0);
		view->Set_Name(name);
		std::string fileName = path + name+ ".png";
		view->CreateImage(fileName.c_str());
		view->Set_Size(m_viewImageSize);
		view->Set_Pos(outPos);
		m_pStageViews.push_back(view);
	}
}

void SceneStageSelect::CreateButton()
{
	m_selectButtonSize = { 380.0f,100.0f };
	m_selectButtonPos = { 800.0f,SPRITE_CENTER_POS_Y(m_selectButtonSize.y) };
	m_UnSelectButtonSize = { 200.0f,50.0f };
	float unSelectPosUpY = 210;
	float unSelectPosDownY = 460;

	ButtonBase* Tutorial = Add_Object<ButtonBase>(0);
	Tutorial->Set_Name("Tutorial");
	Tutorial->Load("Assets/Texture/UI/Tutorial.png");
	Tutorial->Set_Size(m_UnSelectButtonSize);
	Tutorial->Set_Pos({ m_selectButtonPos.x,unSelectPosUpY });
	m_pStageButtons.push_back(Tutorial);


	int clearStageNum = DataSave::Get_Data<int>("ClearStageNum");
	int stageNum = 5;
	for (int i = 0; i < stageNum; i++)
	{
		ButtonBase* button = Add_Object<ButtonBase>(0);
		button->Set_Name("Stage" + std::to_string(i + 1));
		std::string path = "Assets/Texture/UI/";
		if (i <= clearStageNum)
		{	path += "Stage" + std::to_string(i + 1) + ".png"; }
		else
		{	path += "LookStage" + std::to_string(i + 1) + ".png"; }

		button->Load(path.c_str());

		button->Set_Size(m_UnSelectButtonSize);
		button->Set_Pos({ m_selectButtonPos.x,unSelectPosDownY });


		m_pStageButtons.push_back(button);
	}


}

void SceneStageSelect::Update(float deltatim)
{
	
	//- �X�N���[������
	MoveScroll();


}

void SceneStageSelect::MoveScroll()
{
	m_oldSelectCnt = m_selectCnt;
	m_selectCnt = GET_WIN.Get_HweelCnt(0, m_pStageButtons.size() - 1);//�z�C�[����]���擾
	int clearStageNum = DataSave::Get_Data<int>("ClearStageNum");

	//- �ԍ��ɑΉ������{�^����I�𒆂̍��W�ƃT�C�Y�ɕύX
	m_pStageButtons[m_selectCnt]->Set_Size(m_selectButtonSize);
	m_pStageButtons[m_selectCnt]->Set_Pos(m_selectButtonPos);
	//- �I��SE���Đ�����
	if (m_selectCnt != m_oldSelectCnt)
	{
		m_pStageButtons[m_selectCnt]->Play_Sound("select");
	}

	//- �I������Ă��Ȃ��{�^���̃T�C�Y�ƈʒu��ύX
	for (int i = 0; i < m_pStageButtons.size(); i++)
	{
		if (i != m_selectCnt)
		{
			m_pStageButtons[i]->Set_Size(m_UnSelectButtonSize);
			m_pStageButtons[i]->Get_Component<Sprite>()->Set_Color({ 1.0f,1.0f,1.0f,1.0f });

			//- �I������Ă��Ȃ��{�^���͑O��̊֌W�ɂ���Ĕz�u�ʒu��ς���
			//- �I���{�^���̈�O
			if (i == m_selectCnt - 1)
			{	m_pStageButtons[i]->Set_Pos({ m_selectButtonPos.x,460 }); }
			//- �I���{�^���̈��
			else if (i == m_selectCnt + 1)
			{	m_pStageButtons[i]->Set_Pos({ m_selectButtonPos.x,210 }); }
			//- �͈͊O
			else
			{	m_pStageButtons[i]->Set_Pos({ m_selectButtonPos.x,9999.9f }); }
		}
	}


	//- �ꗥ��ʊO�ɔz�u
	for (int i = 0; i < m_pStageViews.size(); i++)
	{
		m_pStageViews[i]->Set_Pos({ 9999.9f,9999.9f });
	}
	//- �I�𒆂̃{�^�����N���A�σX�e�[�W��2���ȏ�̏ꍇ�̓��b�N�摜��\��
	if (m_selectCnt > clearStageNum + 1)
	{
		m_pStageViews[m_pStageViews.size() - 1]->Set_Pos(m_viewImagePos);
	}//���b�N�摜�͕K���Ō�ɂ���̂ŁA�傫���̔ԍ����w��
	else
	{
		m_pStageViews[m_selectCnt]->Set_Pos(m_viewImagePos);
	}


	if (m_Fade->Get_State() == Fade::E_FADE_STATE::Stop)
	{
		//- �I������Ă���{�^�����J�[�\���Əd�Ȃ��Ă��邩
		if (m_pStageButtons[m_selectCnt]->IsOverlap())
		{
			//- �N���A�σX�e�[�W�̎��̃X�e�[�W�܂ł����I���ł��Ȃ��悤�ɂ���
			if (Input::Get_KeyTrigger(VK_LBUTTON) && m_selectCnt <= clearStageNum + 1)
			{
				m_pStageButtons[m_selectCnt]->Play_Sound("push");
				m_Fade->FadeOut();
			}
			else
			{

			}
		}
	}


	if (m_Fade->Get_State() == Fade::E_FADE_STATE::Finish)
	{
		//- �Ή�����V�[���Ɉړ�
		std::string stageName = m_pStageButtons[m_selectCnt]->Get_Name();
		SceneController::E_SCENE_STATE stageState;
		if (stageName == "Tutorial") { stageState = SceneController::Tutorial; }
		else if (stageName == "Stage1")
		{
			stageState = SceneController::Stage1;
		}
		else if (stageName == "Stage2")
		{
			stageState = SceneController::Stage2;
		}
		else if (stageName == "Stage3")
		{
			stageState = SceneController::Stage3;
		}
		else if (stageName == "Stage4")
		{
			stageState = SceneController::Stage4;
		}
		else if (stageName == "Stage5")
		{
			stageState = SceneController::Stage5;
		}

		SceneController::Set_SceneState(stageState);
	}
}


