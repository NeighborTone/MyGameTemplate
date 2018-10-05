#include "GameController.h"
#include "../Class/ResourceManager.hpp"
#include "../Input/Input.hpp"
void GameController::resourceLoad()
{

}

GameController::GameController()
{
	//最初に必要なリソースやEntityの生成、ロードを行う
	resourceLoad();


	
}


void GameController::update()
{
	Input::Get().udateKey();
	entityManager_.refresh();
	entityManager_.update();

}

void GameController::draw()
{
	entityManager_.orderByDraw(ENTITY_GROUP::MAX);
}