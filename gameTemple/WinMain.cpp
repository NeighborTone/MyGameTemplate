#include "src/System/System.hpp"
#include <memory>
#include <new>
#include <crtdbg.h>
#include "src/Utility/Vec.hpp"
#include "src/Class/ResourceManager.hpp"
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(7087);
	Utility::ShowConsole();
	System sys;
	ResourceManager::GetGraph().load("a.png", "test0");
	for (auto i(1u); i < 1000; ++i)
	{
		ResourceManager::GetGraph().loadAsync("a.png", "test" + std::to_string(i));
	}
	while (sys.isOk())
	{
		if (ResourceManager::GetAsyncLoadNum() == 0)
		{
			DrawGraph(100, 200, ResourceManager::GetGraph().getHandle("test0"), true);
		}
		else
		{
			DrawGraph(200, 100, ResourceManager::GetGraph().getHandle("test0"), true);
		}
		DrawFormatString(0, 0, 0xffffffff, "”%d", ResourceManager::GetAsyncLoadNum());
	}
}
