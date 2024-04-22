/*
	main.h
	各ヘッダーに必要な物をまとめたヘッダー
*/
#ifndef __MAIN_H__
#define __MAIN_H__

#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <assert.h>
#include <functional>

#include <Windows.h>
#include <iostream>
#include <wrl/client.h>
#include <string>

#include <d3d11.h>
#include <DirectXMath.h>

#pragma comment(lib,"d3d11.lib")
#pragma warning(disable:4005)

template<typename T>
void Release_and_Null(T* &x, const char* varname)
{
	if (x){	x->Release(); x = nullptr;	}
	else
	{
#if _DEBUG
		std::string output = "Not Release";
		output += varname;
		output += "\n";
		OutputDebugString(output.c_str());
#endif // _DEBUG
	}
}

template<typename T>
void Delete_and_Null(T* &x, const char* varname)
{
	if (x){  delete x;	x = nullptr; }
	else
	{
#if _DEBUG
		std::string output = "Not Delete: ";
		output += varname;
		output += "\n";
		OutputDebugString(output.c_str());
#endif // _DEBUG
	}
}

class Message
{
public:
	static void ErrorMessage(const char* msg)
	{	MessageBox(nullptr, msg, "Error", MB_OK);}
	static void ErrorMessage(std::string msg)
	{	MessageBox(nullptr, msg.c_str(), "Error", MB_OK);}

	static void DebugLog(const char* msg)
	{	OutputDebugString(msg);}
	static void DebugLog(std::string msg)
	{	OutputDebugString(msg.c_str());}
private:

};

#endif // !__MAIN_H__

