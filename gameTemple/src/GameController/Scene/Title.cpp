#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"
#include "../../System/System.hpp"
#include "../../Components/Collider.hpp"

namespace Scene
{
	Title::~Title()
	{
		entitytManager_->removeAll();
	}
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
		class InputMove : public ECS::ComponentSystem
		{
		private:
			float speed;
			ECS::Position* pos_ = nullptr;
		public:
			void initialize() override
			{
				pos_ = &entity->getComponent<ECS::Position>();
			}
			void update() override
			{
				if (Input::Get().getKeyFrame(KEY_INPUT_RIGHT) >= 1)
				{
					pos_->val.x += 5;
				}
				if (Input::Get().getKeyFrame(KEY_INPUT_LEFT) >= 1)
				{
					pos_->val.x -= 5;
				}
				if (Input::Get().getKeyFrame(KEY_INPUT_UP) >= 1)
				{
					pos_->val.y -= 5;
				}
				if (Input::Get().getKeyFrame(KEY_INPUT_DOWN) >= 1)
				{
					pos_->val.y += 5;
				}
			}
		};
		p->addComponent<InputMove>();
		p->addGroup(ENTITY_GROUP::LAYER1);

		pp = (&entitytManager_->addEntity());
		pp->addComponent<ECS::Transform>().setPosition(100.f, 100.f);
		pp->addComponent<ECS::CircleCollider>(20.f).setColor(0, 255, 0);
		pp->addComponent<InputMove>();
		pp->addGroup(ENTITY_GROUP::LAYER1);

		hogeCircle = &entitytManager_->addEntity();
		hogeCircle->addComponent<ECS::Transform>().setPosition(Vec2{200.f,200.f});
		hogeCircle->addComponent<ECS::CircleCollider>(30.f).setColor(0,0,255);
		hogeCircle->addGroup(ENTITY_GROUP::LAYER1);

		line = (&entitytManager_->addEntity());
		line->addComponent<ECS::LineData>(p->getComponent<ECS::Position>().val, pp->getComponent<ECS::Position>().val);
		line->addComponent<ECS::LineCollider>().setJoint(p,pp);
		line->addGroup(ENTITY_GROUP::LAYER1);

	}

	void Title::update()
	{
		entitytManager_->update();
		
		if (Collision::CirecleAndLine(hogeCircle, line))
		{
			hogeCircle->getComponent<ECS::CircleCollider>().setColor(255, 0, 0);
		}
		else
		{
			hogeCircle->getComponent<ECS::CircleCollider>().setColor(0, 0, 255);
		}
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