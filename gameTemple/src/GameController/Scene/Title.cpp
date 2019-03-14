
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
		auto x = json.getParameter<float>("obj", "posX");
		auto y = json.getParameter<float>("obj", "posY");
		auto r = json.getParameter<float>("obj", "radius");
		e.init(
			EasingFunctions::GetFunction(json.getParameter<std::string>("obj", "easing")), 
			json.getParameter<float>("obj", "start"), 
			json.getParameter<float>("obj", "end"),
			json.getParameter<float>("obj", "durationTime"));
		p = ECS::Primitive2D::CreateCircle(Vec2{ x, y }, r, *entityManager_);
	}

	void Title::update()
	{
		p->getComponent<ECS::Position>().val.x = e.getVolume();

		entityManager_->update();
		if (Input::Get().getKeyFrame(KEY_INPUT_X) == 1)
		{
			ON_SCENE_CHANGE(SceneName::GAME, StackPopFlag::POP, true);
		}

		if (Input::Get().getPadFrame(Input::PadButton::DOWN)	    )DOUT << "down" << std::endl;
		if(Input::Get().getPadFrame(Input::PadButton::UP)			)DOUT << "up" << std::endl;
		if(Input::Get().getPadFrame(Input::PadButton::LEFT)			)DOUT << "left" << std::endl;
		if(Input::Get().getPadFrame(Input::PadButton::RIGHT)		)DOUT << "right" << std::endl;
		if(Input::Get().getPadFrame(Input::PadButton::Y)			)DOUT << "y" << std::endl;
		if(Input::Get().getPadFrame(Input::PadButton::B)			)DOUT << "b" << std::endl;
		if(Input::Get().getPadFrame(Input::PadButton::A)			)DOUT << "a" << std::endl;
		if(Input::Get().getPadFrame(Input::PadButton::X)			)DOUT << "x" << std::endl;
	}

	void Title::draw()
	{
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		//グループ順に描画
		entityManager_->orderByDraw(ENTITY_GROUP::MAX);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}

}