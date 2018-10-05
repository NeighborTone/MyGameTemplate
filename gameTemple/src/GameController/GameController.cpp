#include "GameController.h"
#include "../Class/ResourceManager.hpp"
#include "Scene/SceneManager.hpp"
#include "../Input/Input.hpp"

void GameController::resourceLoad()
{

}

GameController::GameController()
{
	//�ŏ��ɕK�v�ȃ��\�[�X��Entity�̐����A���[�h���s��
	resourceLoad();
	//�����V�[���̐ݒ�
	Scene::SceneManager::Get().changeScene(Scene::SceneManager::State::GAME, entityManager_);
}


void GameController::update()
{
	entityManager_.refresh();
	Input::Get().udateKey();
	Scene::SceneManager::Get().update();
}

void GameController::draw()
{
	Scene::SceneManager::Get().draw();
}