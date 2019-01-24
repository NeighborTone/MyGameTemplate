#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"
#include "../../System/System.hpp"
#include "../../Components/Collider.hpp"

namespace Scene
{
	Title::Title(IOnSceneChangeCallback* sceneTitleChange, [[maybe_unused]] Parameter* parame, ECS::EntityManager* entityManager)
		: AbstractScene(sceneTitleChange)
		, entitytManager_(entityManager)
	{
		
	}

	void Title::initialize()
	{
		p = (&entitytManager_->addEntity());
		p->addComponent<ECS::Transform>().setPosition(0.f, 100.f);
		p->addComponent<ECS::CircleCollider>(20.f).setColor(255,0,0);	
		p->addGroup(ENTITY_GROUP::LAYER1);

		pp = (&entitytManager_->addEntity());
		pp->addComponent<ECS::Transform>().setPosition(100.f, 100.f);
		pp->addComponent<ECS::CircleCollider>(20.f).setColor(0, 255, 0);
		pp->addGroup(ENTITY_GROUP::LAYER1);

		line = (&entitytManager_->addEntity());
		line->addComponent<ECS::LineData>(Vec2{ 0.f,100.f }, Vec2{ 100.f,0.f });
		line->addComponent<ECS::LineCollider>();
		line->addGroup(ENTITY_GROUP::LAYER1);
	}

	void Title::update()
	{
		entitytManager_->update();
		line->getComponent<ECS::LineData>().p1 = p->getComponent<ECS::Position>().val;
		line->getComponent<ECS::LineData>().p2 = pp->getComponent<ECS::Position>().val;
		if (Input::Get().getKeyFrame(KEY_INPUT_X) == 1)
		{
			ON_SCENE_CHANGE(SceneName::GAME, nullptr, StackPopFlag::POP,true);
		}
		
	}

	void Title::draw()
	{
		entitytManager_->orderByDraw(ENTITY_GROUP::MAX);
	}

}