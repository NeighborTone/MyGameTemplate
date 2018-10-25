/**
* @file TestArcheType.hpp
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
		//!エンティティの生成テスト
		Entity* CreateTestEntity(const char* graphicName, const Vec2 pos, EntityManager& entityManager_)
		{
			auto* entity = &entityManager_.addEntity();
			entity->addComponent<Transform>().setPosition(pos.x,pos.y);
			entity->addComponent<Color>();
			entity->addComponent<AlphaBlend>();
			entity->addComponent<SpriteDraw>(graphicName);
			entity->getComponent<SpriteDraw>().doCenter(true);
			entity->addGroup(ENTITY_GROUP::LAYER1);
			return entity;
		}

		//!子
		Entity* CreateTestEntity2(const char* graphicName, const Vec2 pos, EntityManager& entityManager_)
		{
			auto* entity = &entityManager_.addEntity();
			entity->addComponent<Transform>().setPosition(pos.x, pos.y);
			entity->addComponent<Family>();
			entity->addComponent<Color>(255,0,0);
			entity->addComponent<AlphaBlend>();
			entity->addComponent<SpriteDraw>(graphicName);
			entity->getComponent<SpriteDraw>().doCenter(true);
			entity->addGroup(ENTITY_GROUP::LAYER1);
			return entity;
		}
	}
}