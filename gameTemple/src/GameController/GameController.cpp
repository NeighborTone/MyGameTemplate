#include "GameController.h"
#include "../Class/ResourceManager.hpp"
#include "../Input/Input.hpp"
void GameController::resourceLoad()
{

}

GameController::GameController()
{
	//�ŏ��ɕK�v�ȃ��\�[�X��Entity�̐����A���[�h���s��
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