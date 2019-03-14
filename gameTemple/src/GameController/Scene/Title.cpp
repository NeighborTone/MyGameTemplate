#include "../../Utility/JsonIO.hpp"
#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"
#include "../../System/System.hpp"
#include "../../ArcheType/Primitive2D.hpp"
#include "../../Utility/Parameter.hpp"
#include "../../Utility/String.hpp"

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

	}

	void Title::initialize()
	{
		auto createPlayer = [=]()->ECS::Entity*
		{
			JsonRead json;
			json.load("Resource/entityData/player.json");
			auto x = (float)json.getParameter<number>("player", "posX");
			auto y = (float)json.getParameter<number>("player", "posY");
			auto r = (float)json.getParameter<number>("player", "radius");
			auto speed = (float)json.getParameter<number>("player", "speed");
			auto entity = ECS::Primitive2D::CreateCircle(Vec2{ x, y }, r, *entitytManager_);
			class InputMove final : public ECS::ComponentSystem
			{
			private:
				float speed_;
				ECS::Position* pos_ = nullptr;
			public:
				InputMove(const float& setSpeed) :
					speed_(setSpeed)
				{}
				void initialize() override
				{
					pos_ = &owner->getComponent<ECS::Position>();
				}
				void update() override
				{
					if (Input::Get().getKeyFrame(KEY_INPUT_RIGHT) >= 1)
					{
						pos_->val.x += speed_;
					}
					if (Input::Get().getKeyFrame(KEY_INPUT_LEFT) >= 1)
					{
						pos_->val.x -= speed_;
					}
					if (Input::Get().getKeyFrame(KEY_INPUT_UP) >= 1)
					{
						pos_->val.y -= speed_;
					}
					if (Input::Get().getKeyFrame(KEY_INPUT_DOWN) >= 1)
					{
						pos_->val.y += speed_;
					}
				}
			};
			entity->addComponent<InputMove>(speed);
			return entity;
		};
		player = createPlayer();

		child01 = (&entitytManager_->addEntity(ENTITY_GROUP::DEFAULT));
		child01->addComponent<ECS::Transform>().setParent(player);
		child01->getComponent<ECS::Transform>().setRelativePosition(50.f, 50.f);
		child01->addComponent<ECS::CircleCollider>(20.f).setColor(255, 255, 0);

		child02 = (&entitytManager_->addEntity(ENTITY_GROUP::DEFAULT));
		child02->addComponent<ECS::Transform>().setParent(child01);
		child02->getComponent<ECS::Transform>().setRelativePosition(50.f, 50.f);
		child02->addComponent<ECS::CircleCollider>(20.f).setColor(0, 255, 0);

		auto child03 = (&entitytManager_->addEntity(ENTITY_GROUP::DEFAULT));
		child03->addComponent<ECS::Transform>().setParent(child01);
		child03->getComponent<ECS::Transform>().setRelativePosition(-50.f, 50.f);
		child03->addComponent<ECS::CircleCollider>(20.f).setColor(0, 255, 255);

	}

	void Title::update()
	{
		
		if (Input::Get().getKeyFrame(KEY_INPUT_Z) >= 1)
		{
			child01->getComponent<ECS::Transform>().translatePosition(Vec2{ 5.f,0.f });
		}
		if (Input::Get().getKeyFrame(KEY_INPUT_A) == 1)
		{
			child01->getComponent<ECS::Transform>().setParent(nullptr);
		}

		entitytManager_->update();
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