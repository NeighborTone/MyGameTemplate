#include "Game.h"
#include "SceneManager.hpp"
#include "../../ArcheType/Fuga.hpp"

namespace Scene
{
	Game::Game(ECS::EntityManager& manager) :
			entityManager_(manager)
	{
		ResourceManager::GetGraph().loadDiv("Resource/Act_Chara2.png", "Fuga", 48, 6, 8, 64, 64);
		
		fuga = ECS::ArcheType::CreateFuga("Fuga", Vec2{100.f,300.f}, entityManager_);
	}

	void Game::update()
	{
		entityManager_.update();
	}

	void Game::draw()
	{
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		//ƒOƒ‹[ƒv‡‚É•`‰æ
		entityManager_.orderByDraw(ENTITY_GROUP::MAX);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}

	void Game::release()
	{
		ResourceManager::GetGraph().removeDivGraph("Fuga");
		fuga->destroy();
	}
}