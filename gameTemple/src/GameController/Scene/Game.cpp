#include "Game.h"
#include "SceneManager.hpp"
#include "../../Components/Collider.hpp"
#include "../../Input/Input.hpp"
#include "../../Utility/Counter.hpp"
#include "../GameController.h"
#include "../../Components/Renderer.hpp"
namespace Scene
{
	Game::Game(ECS::EntityManager& manager) :
			entityManager_(manager)
	{
		ResourceManager::GetGraph().load("Resource/a.png","test");
		ECS::Entity* hoge = &entityManager_.addEntity();
		hoge->addComponent<ECS::Position>();
		hoge->addComponent<ECS::SimpleDraw>("test");
		hoge->addGroup(ENTITY_GROUP::LAYER0);

		ECS::Entity* fuga = &entityManager_.addEntity();
		fuga->addComponent<ECS::Position>(100.f, 50.f);
		fuga->addComponent<ECS::Color>(255, 0, 255);
		fuga->addComponent<ECS::AlphaBlend>(ECS::AlphaBlend::INVSRC,200);
		fuga->addComponent<ECS::RectDraw>("test",0,0,461,573);
		fuga->addGroup(ENTITY_GROUP::LAYER1);
	}
	void Game::update()
	{
		entityManager_.update();

	}
	void Game::draw()
	{
		//ƒOƒ‹[ƒv‡‚É•`‰æ
		entityManager_.orderByDraw(ENTITY_GROUP::MAX);
	}
}