/**
 * @file GameMain.hpp
 * @brief Dxlibの更新とアプリケーションの更新を行います
 * @author tonarinohito
 * @date 2018/10/05
 */
#pragma once
#include "../System/System.hpp"
#include "../GameController/GameController.h"
#include "../Utility/FPS.hpp"
#include <memory>

//!アプリケーションを生成します
class GameMain final
{
private:
	std::unique_ptr<System> system_;
	std::unique_ptr<GameController> game_;
	void update()
	{
		game_->update();
	}
	void draw()
	{
		game_->draw();
	}

public:
	GameMain()
	{
		system_ = std::make_unique<System>();
		game_ = std::make_unique<GameController>();
	}
	//!アプリケーションの更新を行います
	void run()
	{
		while (system_->isOk())
		{
			Fps::Get().update();
			update();
			draw();
			Fps::Get().wait();
		}
	}
};