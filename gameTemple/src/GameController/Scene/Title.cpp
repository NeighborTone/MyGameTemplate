
#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"
#include "../src/Utility/Parameter.hpp"

namespace Scene
{
	Title::~Title()
	{
		
	}
	Title::Title(IOnSceneChangeCallback* sceneTitleChange, ECS::EntityManager* entityManager)
		: AbstractScene(sceneTitleChange)
		, entityManager_(entityManager)
	{
		ResourceManager::GetGraph().load("Resource/image/bb.png","p");
	}

	void Title::initialize()
	{
		parent = ECS::ArcheType::CreateEntity("p", Vec2{ 100.f,100.f }, *entityManager_, ENTITY_GROUP::DEFAULT);
		child1 = ECS::ArcheType::CreateEntity("p", Vec2{ 900.f,500.f },*entityManager_,ENTITY_GROUP::DEFAULT);

		auto pos = Vec2::Lerp(
			parent->getComponent<ECS::Position>().val,
			child1->getComponent<ECS::Position>().val,
			t);
		entity = ECS::ArcheType::CreateEntity("p", Vec2{ pos }, *entityManager_, ENTITY_GROUP::DEFAULT);

	}

	void Title::update()
	{
		t += 0.01f;
		if (t >= 1) { t = 1; }
		auto pos = Vec2::Lerp(
			parent->getComponent<ECS::Position>().val,
			child1->getComponent<ECS::Position>().val,
			t);
		
		entity->getComponent<ECS::Position>().val = pos;
		entityManager_->update();
	}

	void Title::draw()
	{
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		//グループ順に描画
		entityManager_->orderByDraw(ENTITY_GROUP::MAX);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}

}