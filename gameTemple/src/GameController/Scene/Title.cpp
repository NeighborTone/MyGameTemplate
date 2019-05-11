
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
		parent = ECS::ArcheType::CreateEntity("p", Vec2{ 200.f,200.f }, *entityManager_, ENTITY_GROUP::DEFAULT);
		child1 = ECS::ArcheType::CreateEntity("p",Vec2{100.f,100.f},*entityManager_,ENTITY_GROUP::DEFAULT);
		auto child2 = ECS::ArcheType::CreateEntity("p", Vec2{ 0.f,0.f }, *entityManager_, ENTITY_GROUP::DEFAULT);
		auto child3 = ECS::ArcheType::CreateEntity("p", Vec2{ -100.f,-100.f }, *entityManager_, ENTITY_GROUP::DEFAULT);
		parent->getComponent<ECS::Transform>().addChild(child1);
		parent->getComponent<ECS::Transform>().addChild(child2);
		parent->getComponent<ECS::Transform>().addChild(child3);
		child1->getComponent<ECS::Transform>().addChild(child2);
		
	}

	void Title::update()
	{
		parent->getComponent<ECS::Transform>().translatePosition(Vec2{ 1.f,1.f });
		child1->getComponent<ECS::Transform>().translateRotation(1.f);
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