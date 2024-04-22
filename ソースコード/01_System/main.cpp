/*
	main.cpp
	エントリーポイント
*/

#include <Windows.h>
#include "../01_System/Application/AppControl.h"
#include "main.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpstr, int cmd)
{
 	AppControl* app = new AppControl(hInst, cmd);
	app->Update();
 	Delete_and_Null<>(app,"app");
	return 0;
}
