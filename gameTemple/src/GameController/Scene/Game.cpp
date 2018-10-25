#include "Game.h"
#include "SceneManager.hpp"
#include "../../ArcheType/TestArcheType.hpp"
#include "../../Input/Input.hpp"

namespace Scene
{
	Game::Game(IOnSceneChangeCallback* sceneTitleChange, const Parameter& parame, ECS::EntityManager* entityManager)
		: AbstractScene(sceneTitleChange),
		entityManager_(entityManager)
	{
		ResourceManager::GetGraph().loadDiv("Resource/image/Act_Chara2.png", "test", 48, 6, 8, 64, 64);
		ResourceManager::GetSound().load("Resource/sound/onion.ogg", "onion", SoundType::SE);
		ResourceManager::GetGraph().load("Resource/image/bb.png", "niconico");
		me = ECS::ArcheType::CreateTestEntity("niconico", Vec2{ 100.f,200.f}, *entityManager_);
		you = ECS::ArcheType::CreateTestEntity2("niconico", Vec2{ 96.f,0.f }, *entityManager_);
		auto aaa = ECS::ArcheType::CreateTestEntity2("niconico", Vec2{ 96.f,96.f }, *entityManager_);
		aaa->getComponent<ECS::Family>().setRoot(me);
		you->getComponent<ECS::Family>().setRoot(me);
		
	}

	void Game::update()
	{
		
		entityManager_->update();
		if (Input::Get().getKeyFrame(KEY_INPUT_A)== 1)
		{
			getCallBack().onSceneChange(SceneName::TITLE, nullptr, StackPopFlag::POP);
			return;
		}
		me->getComponent<ECS::Position>().val.x++;
		
	}

	void Game::draw()
	{
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		//グループ順に描画
		entityManager_->orderByDraw(ENTITY_GROUP::MAX);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawFormatString(0, 0, 0xffffffff, "ゲーム画面");
	}

	Game::~Game()
	{
		ResourceManager::GetGraph().removeDivGraph("test");
		ResourceManager::GetSound().remove("onion");
		entityManager_->allDestroy();
	}
}