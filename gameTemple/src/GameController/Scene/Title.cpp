
#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"
#include "../src/Utility/Parameter.hpp"
#include "../../Utility/Math.hpp"
namespace Scene
{
	using namespace ECS;

	namespace
	{
		Entity* circle;
		Entity* line1;
		Entity* line2;
		Entity* line3;
		Entity* line4;

		Entity* circle2;
		Position* c;
		float speed = 16.2f;
		Easing ease;
	}

	Title::~Title()
	{

	}
	Title::Title(IOnSceneChangeCallback* sceneTitleChange, ECS::EntityManager* entityManager)
		: AbstractScene(sceneTitleChange)
		, entityManager_(entityManager)
	{
		//ResourceManager::GetGraph().load("Resource/image/bb.png","p");
	}

	void Title::initialize()
	{
		circle = Primitive2D::CreateCircle(Vec2{ 100.f,50.f }, 30.f, *entityManager_);
		circle2 = Primitive2D::CreateCircle(Vec2{ 15.f,50.f }, 30.f, *entityManager_);
		ease.init(EasingFunctions::GetFunction("SineIn"),0.f,705.f,60.f);
		ease.loopEnable(true);
		auto nom = Vec2(2.f, 2.f).normalize();

		circle->addComponent<Velocity>(nom);
		c = &circle->getComponent<Position>();
		line1 = Primitive2D::CreateLine(Vec2{ 0.f,200.f }, Vec2{ 800.f,700.f }, *entityManager_);
		line2 = Primitive2D::CreateLine(Vec2{ 700.f,700.f }, Vec2{ 1280.f,0.f }, *entityManager_);
		line3 = Primitive2D::CreateLine(Vec2{ 0.f,2.f }, Vec2{ 1280.f,2.f }, *entityManager_);
		line4 = Primitive2D::CreateLine(Vec2{ 2.f,0.f }, Vec2{ 2.f,720.f }, *entityManager_);
	}

	void Title::update()
	{
		circle2->getComponent<Position>().val.y = ease.getVolume();
		c->val += circle->getComponent<Velocity>().val * speed;
		if (Collision::CirecleAndLine(circle, line1))
		{
			circle->getComponent<Velocity>().val = 
				Math::GetReflect
				(
					circle->getComponent<Velocity>().val, Math::GetLineNormal
					(
						line1->getComponent<LineData>().p1, 
						line1->getComponent<LineData>().p2
					)
				);
		}
		if (Collision::CirecleAndLine(circle, line2))
		{
			circle->getComponent<Velocity>().val = 
				Math::GetReflect
				(
					circle->getComponent<Velocity>().val,
					Math::GetLineNormal
					(
						line2->getComponent<LineData>().p1, 
						line2->getComponent<LineData>().p2
					)
				);
		}
		if (Collision::CirecleAndLine(circle, line3))
		{
			circle->getComponent<Velocity>().val = 
				Math::GetReflect(
					circle->getComponent<Velocity>().val,
					Math::GetLineNormal(
						line3->getComponent<LineData>().p1,
						line3->getComponent<LineData>().p2
					)
				);
		}
		if (Collision::CirecleAndLine(circle, line4))
		{
			circle->getComponent<Velocity>().val = 
				Math::GetReflect
				(
					circle->getComponent<Velocity>().val, 
					Math::GetLineNormal
					(
						line4->getComponent<LineData>().p1, 
						line4->getComponent<LineData>().p2
					)
				);
		}

		entityManager_->update();
	}

	void Title::draw()
	{
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		//グループ順に描画
		entityManager_->orderByDraw(ENTITY_GROUP::MAX);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}

}