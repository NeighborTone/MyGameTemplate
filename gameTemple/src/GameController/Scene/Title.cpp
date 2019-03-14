#include "../../Utility/JsonIO.hpp"
#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"
#include "../../System/System.hpp"
#include "../../ArcheType/Primitive2D.hpp"
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

	}

	void Title::initialize()
	{
		JsonWrite w;
		w.insert<std::string>("Test","foo!");
		w.insert<bool>("Flag", true);
		w.insert<number>("Value", 100);
		w.output("hoge.json");
		auto createPlayer = [=]()->ECS::Entity*
		{
			JsonRead json;
			json.load("Resource/entityData/test.json");
			auto x = (float)json.getParameter<number>("Player", "posX");
			auto y = (float)json.getParameter<number>("Player", "posY");
			auto r = (float)json.getParameter<number>("Player", "radius");
			auto speed = (float)json.getParameter<number>("Player", "speed");
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
		p = createPlayer();

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