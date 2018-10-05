#include "Game.h"
#include "SceneManager.hpp"
#include "../../Input/Input.hpp"
#include "../../Utility/Counter.hpp"
#include "../GameController.h"
namespace Scene
{
	Game::Game(ECS::EntityManager& manager) :
			entityManager_(manager)
		{}
	void Game::update()
	{
		entityManager_.update();
		

	}
	void Game::draw()
	{
		//ƒOƒ‹[ƒv‡‚É•`‰æ
		entityManager_.orderByDraw(ENTITY_GROUP::MAX);
		DrawFormatString(0,0,0xffffffff,"aaaaaaa");
	}
}