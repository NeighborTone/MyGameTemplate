#include "Game.h"
#include "../GameController.h"
#include "../../Input/Input.hpp"

namespace Scene
{
	Game::Game(IOnSceneChangeCallback* sceneTitleChange, ECS::EntityManager* entityManager)
		: AbstractScene(sceneTitleChange),
		entityManager_(entityManager)
	{
		
	}

	void Game::initialize()
	{

	}
	void Game::update()
	{
		
		entityManager_->update();
		if (Input::Get().getKeyFrame(KEY_INPUT_A)== 1)
		{
			ON_SCENE_CHANGE(SceneName::TITLE, StackPopFlag::POP,true);
			return;
		}
		
		
	}

	void Game::draw()
	{
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		//グループ順に描画
		entityManager_->orderByDraw(ENTITY_GROUP::MAX);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawFormatString(0, 0, 0xffffffff, "ゲーム画面");
	}

	Game::~Game()
	{
		entityManager_->removeAll();
	}
	
}