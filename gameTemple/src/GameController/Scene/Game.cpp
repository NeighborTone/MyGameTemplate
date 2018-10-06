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
		ResourceManager::GetGraph().load("Resource/a.png", "test");
		hoge = &entityManager_.addEntity();
		hoge->addComponent<ECS::Position>();
		hoge->addComponent<ECS::SimpleDraw>("test");
		hoge->addGroup(ENTITY_GROUP::LAYER0);

		fuga = &entityManager_.addEntity();
		fuga->addComponent<ECS::Position>(0.f, 0.f);
		fuga->addComponent<ECS::Color>(255, 0, 255);
		fuga->addComponent<ECS::AlphaBlend>(ECS::AlphaBlend::INVSRC,200);
		fuga->addComponent<ECS::SimpleDraw>("test").doCenter(true);
		fuga->addGroup(ENTITY_GROUP::LAYER1);
	}
	Game::~Game()
	{
		
		hoge->destroy();
		fuga->destroy();
	}
	void Game::update()
	{
		entityManager_.update();
		if (Input::Get().getKeyFrame(KEY_INPUT_Z) == 1)
		{
			ResourceManager::GetGraph().removeGraph("test");
		}

	}
	void Game::draw()
	{
		//ƒOƒ‹[ƒv‡‚É•`‰æ
		entityManager_.orderByDraw(ENTITY_GROUP::MAX);
	}
}