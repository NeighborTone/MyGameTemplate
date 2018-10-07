#include "GameController.h"
#include "../Class/ResourceManager.hpp"
#include "Scene/SceneManager.hpp"
#include "../Input/Input.hpp"
#include "../Events/EventManager.hpp"
#include "../Events/TestEvent.hpp"
void GameController::resourceLoad()
{
	
}

GameController::GameController()
{
	//�ŏ��ɕK�v�ȃ��\�[�X��Entity�̐����A���[�h���s��
	resourceLoad();
	//�����V�[���̐ݒ�
	Scene::SceneManager::Get().changeScene(Scene::SceneManager::State::TITLE, entityManager_);
	//�C�x���g�ǉ�
	Event::EventManager::Get().addEvent(Scene::SceneManager::State::GAME, Event::TestEvents::BlendSelect);
}


void GameController::update()
{
	entityManager_.refresh();
	Input::Get().updateKey();
	//�V�[���X�V
	Scene::SceneManager::Get().update();
	//�C�x���g�X�V
	Event::EventManager::Get().update(entityManager_);
}

void GameController::draw()
{
	//�V�[���`��
	Scene::SceneManager::Get().draw();
}