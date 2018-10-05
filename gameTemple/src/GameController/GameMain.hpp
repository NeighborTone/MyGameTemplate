/**
 * @file GameMain.hpp
 * @brief Dxlib�̍X�V�ƃA�v���P�[�V�����̍X�V���s���܂�
 * @author tonarinohito
 * @date 2018/10/05
 */
#pragma once
#include "../System/System.hpp"
#include "../GameController/GameController.h"
#include "../Utility/FPS.hpp"
#include <memory>

//!�A�v���P�[�V�����𐶐����܂�
class GameMain final
{
private:
	std::unique_ptr<System> system;
	std::unique_ptr<GameController> game;
	void update()
	{
		game->update();
	}
	void draw()
	{
		game->draw();
	}

public:
	GameMain()
	{
		system = std::make_unique<System>();
		game = std::make_unique<GameController>();
	}
	//!�A�v���P�[�V�����̍X�V���s���܂�
	void run()
	{
		while (system->isOk())
		{
			Fps::Get().update();
			update();
			draw();
			Fps::Get().wait();
		}
	}
};