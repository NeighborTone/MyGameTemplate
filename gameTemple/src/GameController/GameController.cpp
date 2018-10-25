#include "GameController.h"
#include "../Class/ResourceManager.hpp"
#include "Scene/SceneManager.hpp"
#include "../Input/Input.hpp"
#include "Scene/Title.h"
#include "Scene/Game.h"

void GameController::resourceLoad()
{
	
}

GameController::GameController()
{
	//最初に必要なリソースやEntityの生成、ロードを行う
	resourceLoad();
	//初期シーンの設定
	sceneStack_.push(std::make_unique< Scene::Title >(this, param_,&entityManager_));	//タイトルシーンを作成し、プッシュ
}

GameController::~GameController()
{
	stackClear();
}

void GameController::onSceneChange(const Scene::SceneName& scene, const Parameter* parame, Scene::StackPopFlag stackClearFlag)
{
	switch (stackClearFlag)
	{
	case Scene::StackPopFlag::NON:
		break;
	case Scene::StackPopFlag::POP:
		sceneStack_.pop();
		break;
	case Scene::StackPopFlag::ALL_CLEAR: 
		stackClear();
		break;
	default:
		break;
	}
	switch (scene)
	{
	case Scene::SceneName::TITLE:
		sceneStack_.push(std::make_unique<Scene::Title>(this, *parame, &entityManager_));
		break;
	case Scene::SceneName::GAME:
		sceneStack_.push(std::make_unique<Scene::Game>(this, *parame, &entityManager_));
		break;
	default:
		break;
	}
}

void GameController::stackClear()
{
	while (!sceneStack_.empty())
	{
		sceneStack_.pop();
	}
}

void GameController::update()
{
	entityManager_.refresh();
	Input::Get().updateKey();
	//シーン更新
	isSceneEmpty();
	sceneStack_.top()->update();
}

void GameController::draw()
{
	//シーン描画
	isSceneEmpty();
	sceneStack_.top()->draw();
}

void GameController::isSceneEmpty()
{
	assert(!sceneStack_.empty() && "シーンスタックが空です!");
}
