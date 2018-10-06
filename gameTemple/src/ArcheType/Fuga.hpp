/**
* @file Test.hpp
* @brief エンティティの原型を作るテスト
* @author tonarinohito
* @date 2018/10/05
*/
#pragma once
#include "../GameController/GameController.h"
#include "../Components/Renderer.hpp"
namespace ECS
{
	namespace ArcheType
	{
		Entity* CreateFuga(const char* graphicName, const Vec2 pos, EntityManager& entityManager_)
		{
			auto* fuga = &entityManager_.addEntity();
			fuga->addComponent<Transform>().setPosition(pos.x,pos.y);
			fuga->addComponent<Color>();
			fuga->addComponent<AlphaBlend>();
			fuga->addComponent<SpriteAnimationDraw>(graphicName).setIndex(1);
			fuga->getComponent<SpriteAnimationDraw>().setPivot(Vec2{ 32,32 });
			fuga->addGroup(ENTITY_GROUP::LAYER1);
			return fuga;
		}
	}
}