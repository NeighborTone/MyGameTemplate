#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"
#include "../../System/System.hpp"
#include "../../Components/Collider.hpp"
#include "../../Utility/Parameter.hpp"
namespace Scene
{
	Title::~Title()
	{
		entitytManager_->removeAll();
	}
	Title::Title(IOnSceneChangeCallback* sceneTitleChange, ECS::EntityManager* entityManager)
		: AbstractScene(sceneTitleChange)
		, entitytManager_(entityManager)
	{
		Parameter::Get().add<float>("speed", 5.0f);
	}

	void Title::initialize()
	{
		p = (&entitytManager_->addEntity());
		p->addComponent<ECS::Transform>(Vec2{ 20.f,20.f });
		p->addComponent<ECS::CircleCollider>(20.f).setColor(255,0,0);	
		class InputMove : public ECS::ComponentSystem
		{
		private:
			float speed;
			ECS::Position* pos_ = nullptr;
		public:
			void initialize() override
			{
				speed = Parameter::Get().get<float>("speed");
				pos_ = &entity->getComponent<ECS::Position>();
			}
			void update() override
			{
				if (Input::Get().getKeyFrame(KEY_INPUT_RIGHT) >= 1)
				{
					pos_->val.x += speed;
				}
				if (Input::Get().getKeyFrame(KEY_INPUT_LEFT) >= 1)
				{
					pos_->val.x -= speed;
				}
				if (Input::Get().getKeyFrame(KEY_INPUT_UP) >= 1)
				{
					pos_->val.y -= speed;
				}
				if (Input::Get().getKeyFrame(KEY_INPUT_DOWN) >= 1)
				{
					pos_->val.y += speed;
				}
			}
		};
		p->addComponent<InputMove>();
		p->addGroup(ENTITY_GROUP::DEFAULT);

		pp = (&entitytManager_->addEntity(ENTITY_GROUP::DEFAULT));
		pp->addComponent<ECS::Transform>().setParent(p);
		pp->getComponent<ECS::Transform>().setRelativePosition(50.f, 50.f);
		pp->addComponent<ECS::CircleCollider>(20.f).setColor(255, 255, 0);

		ppp = (&entitytManager_->addEntity(ENTITY_GROUP::DEFAULT));
		ppp->addComponent<ECS::Transform>().setParent(pp);
		ppp->getComponent<ECS::Transform>().setRelativePosition(50.f, 50.f);
		ppp->addComponent<ECS::CircleCollider>(20.f).setColor(0, 255, 0);

		auto pppp = (&entitytManager_->addEntity(ENTITY_GROUP::DEFAULT));
		pppp->addComponent<ECS::Transform>().setParent(pp);
		pppp->getComponent<ECS::Transform>().setRelativePosition(-50.f, 50.f);
		pppp->addComponent<ECS::CircleCollider>(20.f).setColor(0, 255, 255);

	}

	void Title::update()
	{
		entitytManager_->update();
		if (Input::Get().getKeyFrame(KEY_INPUT_Z) == 1)
		{
			pp->getComponent<ECS::Transform>().translatePosition(Vec2{ 5.f,0.f });
		}
		if (Input::Get().getKeyFrame(KEY_INPUT_X) == 1)
		{
			ON_SCENE_CHANGE(SceneName::GAME, StackPopFlag::POP, true);
		}
		
	}

	void Title::draw()
	{
		entitytManager_->orderByDraw(ENTITY_GROUP::MAX);
	}

}