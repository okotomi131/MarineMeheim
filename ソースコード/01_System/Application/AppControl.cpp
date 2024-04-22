/*********************************************************************
 * @file   AppControl.cpp
 * @brief  �A�v���P�[�V��������N���X

 �E�B���h�E�E�V�[���Ǘ��y�ѐ��䃋�[�v���s��
 *********************************************************************/

 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "AppControl.h"

#include "../Window/WinStartUp.h"
#include "../main.h"
#include "../Text/TextDraw.h"
#include "../../04_Scene/SceneController.h"

#pragma comment(lib, "winmm.lib")	//timeGettime�̎g�p

/*
==================================================

�萔�E�}�N����`

==================================================
*/
static const int FPS_NUM = 60;	//�t���[�����[�g


AppControl::AppControl(HINSTANCE hinst, int cmd)
{
	//-�@�E�B���h�E������
	WinStartUp::CreateInstance(hinst, cmd);
	if (FAILED(GET_WIN.Init()))
	{	Message::ErrorMessage("�E�B���h�E�̏������Ɏ��s���܂���");}

	//- �V�[��������
	SceneController::Init();

	//- �ϐ�������

	timeBeginPeriod(1);
	m_startTime     = timeGetTime();
	m_executionTime = m_startTime;
}

AppControl::~AppControl()
{
	SceneController::Uninit();
	GET_WIN.DeleteInstance();
}

void AppControl::Update()
{
	//- �A�v���P�[�V�������[�v
	while (true)
	{
		//- ���b�Z�[�W���[�v
		if (!GET_WIN.MsgLoop()) { break; }
		//- �Q�[�����[�v
		DWORD cur = timeGetTime();
		float diff = static_cast<float>(cur - m_executionTime);

		
		if (diff >= 1000.0f / FPS_NUM)
		{
			float deltatime =  diff / 1000.0f;

			//--- �X�V����
			SceneController::Update(deltatime);

			//--- �`�揈��
			DirectXRenderer::BeginDraw();
			SceneController::Draw();

//#ifdef _DEBUG
			//--- �f�o�b�N�pFPS�\��
			//DebugFPS(diff);
//#endif // _DEBUG

			DirectXRenderer::EndDraw();

			//--- �t���[�����[�g�v�Z
			m_executionTime = cur;
		}


	}
}

void AppControl::DebugFPS(float diff)
{
	TextDraw::Set_FontColor(D2D1::ColorF(D2D1::ColorF::White));
	TextDraw::Set_FontSize(10.0f);
	TextDraw::Set_FontType(1);
	TextDraw::DrawMessage("FPS : " + std::to_string(1000.0f / diff), { 1000.0f,700.0f });
}
