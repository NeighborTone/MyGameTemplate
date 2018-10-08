#include "Game.h"
#include "SceneManager.hpp"
#include "../../ArcheType/TestArcheType.hpp"

namespace Scene
{
	Game::Game(ECS::EntityManager& manager) :
			entityManager_(manager)
	{
		ResourceManager::GetGraph().loadDiv("Resource/Act_Chara2.png", "test", 48, 6, 8, 64, 64);
		ResourceManager::GetSound().load("Resource/onion.ogg", "onion");
		testEntity = ECS::ArcheType::CreateTestEntity("test", Vec2{100.f,300.f}, entityManager_);
	}

	void Game::update()
	{
		entityManager_.update();
	}

	void Game::draw()
	{
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		//グループ順に描画
		entityManager_.orderByDraw(ENTITY_GROUP::MAX);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}

	void Game::release()
	{
		ResourceManager::GetGraph().removeDivGraph("test");
		testEntity->destroy();
	}
}