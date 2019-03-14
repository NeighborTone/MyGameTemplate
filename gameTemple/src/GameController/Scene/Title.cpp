
#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"


namespace Scene
{
	Title::~Title()
	{
		entityManager_->removeAll();
	}
	Title::Title(IOnSceneChangeCallback* sceneTitleChange, ECS::EntityManager* entityManager)
		: AbstractScene(sceneTitleChange)
		, entityManager_(entityManager)
	{
		
	}

	void Title::initialize()
	{
		json.load("Resource/entityData/easingTest.json");
		auto x = (float)json.getParameter<number>("obj", "posX");
		auto y = (float)json.getParameter<number>("obj", "posY");
		auto r = (float)json.getParameter<number>("obj", "radius");
		p = ECS::Primitive2D::CreateCircle(Vec2{ x, y }, r, *entityManager_);

	}

	void Title::update()
	{
		e.run(EasingFunctions::GetFunction(json.getParameter<std::string>("obj", "easing")), (float)json.getParameter<number>("obj", "durationTime"));
		p->getComponent<ECS::Position>().val.x = e.getVolume((float)json.getParameter<number>("obj", "start"), (float)json.getParameter<number>("obj", "end"));

		entityManager_->update();
		if (Input::Get().getKeyFrame(KEY_INPUT_X) == 1)
		{
			ON_SCENE_CHANGE(SceneName::GAME, StackPopFlag::POP, true);
		}		
	}

	void Title::draw()
	{
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		//グループ順に描画
		entityManager_->orderByDraw(ENTITY_GROUP::MAX);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}

}