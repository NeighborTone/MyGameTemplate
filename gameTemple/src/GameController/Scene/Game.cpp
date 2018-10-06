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
		ResourceManager::GetGraph().loadDiv("Resource/Act_Chara2.png", "p", 48, 6, 8, 64, 64);
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		hoge = &entityManager_.addEntity();
		hoge->addComponent<ECS::Position>();
		hoge->addComponent<ECS::SimpleDraw>("test");
		hoge->addGroup(ENTITY_GROUP::LAYER0);

		fuga = &entityManager_.addEntity();
		fuga->addComponent<ECS::Transform>().setPosition(100.f, 300.f);
		fuga->addComponent<ECS::Color>();
		fuga->addComponent<ECS::AlphaBlend>();
		fuga->addComponent<ECS::SpriteAnimationDraw>("p").setIndex(1);
		fuga->getComponent<ECS::SpriteAnimationDraw>().setPivot(Vec2{32,32});
		fuga->addGroup(ENTITY_GROUP::LAYER1);
	}

	void Game::update()
	{
		entityManager_.update();
		
		if (Input::Get().getKeyFrame(KEY_INPUT_Z) == 1)
		{
			fuga->getComponent<ECS::AlphaBlend>().blendMode = ECS::AlphaBlend::INVSRC;
		}
	}

	void Game::draw()
	{
		//ƒOƒ‹[ƒv‡‚É•`‰æ
		entityManager_.orderByDraw(ENTITY_GROUP::MAX);
	}

	void Game::release()
	{
		ResourceManager::GetGraph().removeGraph("test");
		hoge->destroy();
		fuga->destroy();
	}
}