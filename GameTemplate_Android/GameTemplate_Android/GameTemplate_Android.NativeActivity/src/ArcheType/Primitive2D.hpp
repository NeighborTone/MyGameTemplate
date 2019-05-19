/**
* @file Primitive2D.hpp
* @brief 基本図形を作る
* @author tonarinohito
* @date 2019/03/14
*/
#pragma once
#include "../GameController/GameController.h"
#include "../Components/Collider.hpp"
namespace ECS
{
	struct Primitive2D
	{
		static Entity* CreateBox(const Vec2& pos, const Vec2& size, EntityManager& entityManager)
		{
			auto* entity = &entityManager.addEntity();
			entity->addComponent<Transform2D>(pos);
			entity->addComponent<BoxCollider>(size);
			entity->addGroup(ENTITY_GROUP::DEFAULT);
			return entity;
		}

		static Entity* CreateCircle(const Vec2& pos, const float& radius, EntityManager& entityManager)
		{
			auto* entity = &entityManager.addEntity();
			entity->addComponent<Transform2D>(pos);
			entity->addComponent<CircleCollider>(radius);
			entity->addGroup(ENTITY_GROUP::DEFAULT);
			return entity;
		}

		static Entity* CreateLine(Entity* p1, Entity* p2,EntityManager& entityManager)
		{
			auto* entity = &entityManager.addEntity();
			entity->addComponent<Transform2D>();
			entity->addComponent<LineCollider>().setJoint(p1,p2);
			entity->addGroup(ENTITY_GROUP::DEFAULT);
			return entity;
		}

		static Entity* CreateLine(const Vec2& pos1, const Vec2& pos2, EntityManager& entityManager)
		{
			auto* entity = &entityManager.addEntity();
			entity->addComponent<Transform2D>();
			entity->addComponent<LineData2D>(pos1, pos2);
			entity->addComponent<LineCollider>();
			entity->addGroup(ENTITY_GROUP::DEFAULT);
			return entity;
		}
	};
}