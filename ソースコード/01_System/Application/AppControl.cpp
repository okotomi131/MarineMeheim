/*********************************************************************
 * @file   AppControl.cpp
 * @brief  アプリケーション制御クラス

 ウィンドウ・シーン管理及び制御ループを行う
 *********************************************************************/

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "AppControl.h"

#include "../Window/WinStartUp.h"
#include "../main.h"
#include "../Text/TextDraw.h"
#include "../../04_Scene/SceneController.h"

#pragma comment(lib, "winmm.lib")	//timeGettimeの使用

/*
==================================================

定数・マクロ定義

==================================================
*/
static const int FPS_NUM = 60;	//フレームレート


AppControl::AppControl(HINSTANCE hinst, int cmd)
{
	//-　ウィンドウ初期化
	WinStartUp::CreateInstance(hinst, cmd);
	if (FAILED(GET_WIN.Init()))
	{	Message::ErrorMessage("ウィンドウの初期化に失敗しました");}

	//- シーン初期化
	SceneController::Init();

	//- 変数初期化

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
	//- アプリケーションループ
	while (true)
	{
		//- メッセージループ
		if (!GET_WIN.MsgLoop()) { break; }
		//- ゲームループ
		DWORD cur = timeGetTime();
		float diff = static_cast<float>(cur - m_executionTime);

		
		if (diff >= 1000.0f / FPS_NUM)
		{
			float deltatime =  diff / 1000.0f;

			//--- 更新処理
			SceneController::Update(deltatime);

			//--- 描画処理
			DirectXRenderer::BeginDraw();
			SceneController::Draw();

//#ifdef _DEBUG
			//--- デバック用FPS表示
			//DebugFPS(diff);
//#endif // _DEBUG

			DirectXRenderer::EndDraw();

			//--- フレームレート計算
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
