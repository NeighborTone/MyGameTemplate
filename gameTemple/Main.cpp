#ifdef __ANDROID__
#else
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW
#endif
#endif
#endif

#include "src/Utility/Utility.hpp"
#include "src/GameController/GameMain.hpp"

#ifdef __ANDROID__
// Android版のコンパイルだったら android_main
int android_main(void)
#else
// Windows版のコンパイルだったら WinMain
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
#endif
{
#if defined(_WIN64) || defined(_WIN32)
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(98);
	ShowConsole();
#endif
#endif
	GameMain main;
	main.run();
}