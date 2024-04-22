/*********************************************************************
 * @file   WinStartUp.cpp
 * @brief  ウィンドウの設定
 *********************************************************************/
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "WinStartUp.h"
#include "../../01_System/Input/Input.h"

POINT WinStartUp::m_OldMousePos = {};
POINT WinStartUp::m_CurMousePos = {};

WinStartUp::WinStartUp(HINSTANCE hInst, int cmd)
{
	m_hInst = hInst;
	m_cmd = cmd;
	m_winSize.cx = SCREEN_WIDTH;
	m_winSize.cy = SCREEN_HEIGHT;
}

void WinStartUp::CreateInstance(HINSTANCE hInst, int cmd)
{
	DeleteInstance();
	m_spInstance = new WinStartUp(hInst, cmd);
}

HRESULT WinStartUp::Init()
{
	// COM初期化
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		MessageBox(NULL, _T("COMの初期化に失敗しました。"), _T("error"), MB_OK);
		return E_FAIL;
	}

	//- ウィンドウクラス登録
	memset(&m_wc, 0, sizeof(m_wc));
	m_wc.style		 = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	m_wc.lpfnWndProc = (WNDPROC)WinStartUp::MainWndProc;
	m_wc.cbClsExtra	 = 0;
	m_wc.cbWndExtra	 = 0;
	m_wc.hInstance	 = m_hInst;
	m_wc.hIcon = (HICON)LoadImage(
		NULL, "Assets/Texture/Window/TitleIcon.ico",
		IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	m_wc.hCursor	 = LoadCursor(nullptr, IDC_CROSS);
	m_wc.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
	m_wc.lpszMenuName  = MENU_NAME;
	m_wc.lpszClassName = CLASS_NAME;
	//- エラーチェック
	if (!RegisterClass(&m_wc))
	{
		Message::ErrorMessage("ウィンドウクラス登録に失敗しました");
		return E_FAIL;
	}

	//- メインウィンドウ作成
	RECT rect	  = { 0,0,m_winSize.cx,m_winSize.cy };
	DWORD style	  = WS_CAPTION | WS_SYSMENU;
	DWORD exStyle = WS_EX_OVERLAPPEDWINDOW;
	AdjustWindowRectEx(&rect, style, false, exStyle);

	//- ウィンドウの幅と高さ
	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	//- 画面のサイズを取得
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//- 画面の中央にウィンドウを配置する座標を計算
	int posX = (screenWidth - windowWidth)   * 0.5f;
	int posY = (screenHeight - windowHeight) * 0.5f;

	m_hWnd = CreateWindowEx(
		exStyle,
		m_wc.lpszClassName,
		CLASS_NAME,
		style,
		posX,
		posY,
		rect.right - rect.left,
		rect.bottom - rect.top,
		HWND_DESKTOP, nullptr,
		m_hInst, nullptr);

	//- 作成エラーチェック
	if (!m_hWnd)
	{	Message::ErrorMessage("メインウィンドウの作成に失敗しました"); return E_FAIL;}

	//- ウィンドウ作成
	ShowWindow(m_hWnd, m_cmd);
	UpdateWindow(m_hWnd);

	//- 作成完了
	return S_OK;
}


bool WinStartUp::MsgLoop()
{
	if (PeekMessage(&m_msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}
	if (m_msg.message == WM_QUIT) { return false; }
	return true;
}


void WinStartUp::Uninit()
{
	//- ウィンドウ削除
	CoUninitialize();
	DestroyWindow(m_hWnd);
	UnregisterClass(m_wc.lpszClassName, m_wc.hInstance);
	m_hWnd = nullptr;

}


LRESULT WinStartUp::MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	float diffX = {};
	float diffY = {};

	switch (msg)
	{
	case(WM_MOUSEWHEEL):
		//- 0より大きければ増加、0より小さければ減少
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{ 	m_spInstance->m_wheelCnt++; }
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
		{ m_spInstance->m_wheelCnt--; }
		break;

	case(WM_CLOSE):
		if (MessageBox(hWnd, "終了しますか？", "確認", MB_YESNO) == IDNO) { return 0; }
		break;

	case(WM_DESTROY): PostQuitMessage(0); break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
