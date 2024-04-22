/*********************************************************************
 * @file   WinStartUp.cpp
 * @brief  �E�B���h�E�̐ݒ�
 *********************************************************************/
 /*
 ==================================================

 �C���N���[�h

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
	// COM������
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		MessageBox(NULL, _T("COM�̏������Ɏ��s���܂����B"), _T("error"), MB_OK);
		return E_FAIL;
	}

	//- �E�B���h�E�N���X�o�^
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
	//- �G���[�`�F�b�N
	if (!RegisterClass(&m_wc))
	{
		Message::ErrorMessage("�E�B���h�E�N���X�o�^�Ɏ��s���܂���");
		return E_FAIL;
	}

	//- ���C���E�B���h�E�쐬
	RECT rect	  = { 0,0,m_winSize.cx,m_winSize.cy };
	DWORD style	  = WS_CAPTION | WS_SYSMENU;
	DWORD exStyle = WS_EX_OVERLAPPEDWINDOW;
	AdjustWindowRectEx(&rect, style, false, exStyle);

	//- �E�B���h�E�̕��ƍ���
	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	//- ��ʂ̃T�C�Y���擾
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//- ��ʂ̒����ɃE�B���h�E��z�u������W���v�Z
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

	//- �쐬�G���[�`�F�b�N
	if (!m_hWnd)
	{	Message::ErrorMessage("���C���E�B���h�E�̍쐬�Ɏ��s���܂���"); return E_FAIL;}

	//- �E�B���h�E�쐬
	ShowWindow(m_hWnd, m_cmd);
	UpdateWindow(m_hWnd);

	//- �쐬����
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
	//- �E�B���h�E�폜
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
		//- 0���傫����Α����A0��菬������Ό���
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{ 	m_spInstance->m_wheelCnt++; }
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
		{ m_spInstance->m_wheelCnt--; }
		break;

	case(WM_CLOSE):
		if (MessageBox(hWnd, "�I�����܂����H", "�m�F", MB_YESNO) == IDNO) { return 0; }
		break;

	case(WM_DESTROY): PostQuitMessage(0); break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
