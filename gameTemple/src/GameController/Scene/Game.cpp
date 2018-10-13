﻿#include "Game.h"
#include "SceneManager.hpp"
#include "../../ArcheType/TestArcheType.hpp"
#include "../../Input/Input.hpp"

namespace Scene
{
	Game::Game(IOnSceneChangeCallback* sceneTitleChange, const Parameter& parame, ECS::EntityManager* entityManager)
		: AbstractScene(sceneTitleChange),
		entityManager_(entityManager),
		playerDetail(parame)	//前のシーンの情報を取得
	{
		ResourceManager::GetGraph().loadDiv("Resource/image/Act_Chara2.png", "test", 48, 6, 8, 64, 64);
		ResourceManager::GetSound().load("Resource/sound/onion.ogg", "onion", SoundType::SE);

		if (playerDetail.get<std::string>("名前") == "たかし")
		{
			ECS::ArcheType::CreateTestEntity("test", Vec2{ 100.f,300.f }, *entityManager_);
		}
		if (playerDetail.get<std::string>("名前") == "まゆみ")
		{
			ECS::ArcheType::CreateTestEntity2("test", Vec2{ 100.f,300.f }, *entityManager_);
		}
		if (playerDetail.get<std::string>("名前") == "みつひこ")
		{
			ECS::ArcheType::CreateTestEntity3("test", Vec2{ 100.f,300.f }, *entityManager_);
		}
	}

	void Game::update()
	{
		entityManager_->update();
		if (Input::Get().getKeyFrame(KEY_INPUT_A)== 1)
		{
			getCallBack().onSceneChange(SceneName::TITLE, nullptr, true);
		}
	}

	void Game::draw()
	{
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		//グループ順に描画
		entityManager_->orderByDraw(ENTITY_GROUP::MAX);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawFormatString(0, 0, 0xffffffff, "ゲーム画面");
		DrawFormatString(300, 50, 0xffffffff, "%s\n", playerDetail.get<std::string>("名前").c_str());
	}

	Game::~Game()
	{
		ResourceManager::GetGraph().removeDivGraph("test");
		ResourceManager::GetSound().remove("onion");
	}
}