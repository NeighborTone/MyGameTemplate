
#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"
#include "../src/Utility/Parameter.hpp"

namespace Scene
{
	namespace
	{
		Vec2 left_down{ 100.f, 500.f };
		Vec2 left_top{ 100.f, 100.f };
		Vec2 right_top{ 900.f, 100.f };
		Vec2 right_down{ 900.f, 400.f };

		//movepoints
		ECS::Entity* a = nullptr;
		ECS::Entity* b = nullptr;
		ECS::Entity* c = nullptr;
		ECS::Entity* d = nullptr;
		ECS::Entity* e = nullptr;
		ECS::Entity* pointOnCurve = nullptr;

		//lines
		ECS::Entity* p1_p2 = nullptr;
		ECS::Entity* p2_p3 = nullptr;
		ECS::Entity* p3_p4 = nullptr;
		ECS::Entity* a_b = nullptr;
		ECS::Entity* b_c = nullptr;
		ECS::Entity* d_e = nullptr;

		//points
		ECS::Entity* p1 = nullptr;
		ECS::Entity* p2 = nullptr;
		ECS::Entity* p3 = nullptr;
		ECS::Entity* p4 = nullptr;


		ECS::Position* aPos = nullptr;
		ECS::Position* bPos = nullptr;
		ECS::Position* cPos = nullptr;
		ECS::Position* dPos = nullptr;
		ECS::Position* ePos = nullptr;
		ECS::Position* curvePos = nullptr;
		Counter_f t;

		const Vec2& GetPointOnBezierCurve(Vec2& p0, Vec2& p1, Vec2& p2, Vec2& p3, const float& t)
		{
			float u = 1.f - t;
			float t2 = t * t;
			float u2 = u * u;
			float u3 = u2 * u;
			float t3 = t2 * t;

			Vec2 result =
				p0 * (u3) +
				p1 * (3.f * u2 * t) +
				p2 * (3.f * u * t2) +
				p3 * (t3);

			return result;
		}
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
		//movepoints
		a = ECS::Primitive2D::CreateCircle(Vec2{ left_down }, 8.f, *entityManager_);
		b = ECS::Primitive2D::CreateCircle(Vec2{ left_top }, 8.f, *entityManager_);
		c = ECS::Primitive2D::CreateCircle(Vec2{ right_top }, 8.f, *entityManager_);
		d = ECS::Primitive2D::CreateCircle(Vec2{ left_down }, 8.f, *entityManager_);
		e = ECS::Primitive2D::CreateCircle(Vec2{ left_top }, 8.f, *entityManager_);
		pointOnCurve = ECS::Primitive2D::CreateCircle(Vec2{ left_top }, 20.f, *entityManager_);
		pointOnCurve->getComponent<ECS::CircleCollider>().fillEnable();
		//points
		p1 = ECS::Primitive2D::CreateCircle(Vec2{ left_down }, 12.f, *entityManager_);//left_down
		p1->getComponent<ECS::CircleCollider>().setColor(0, 128, 255);
		p2 = ECS::Primitive2D::CreateCircle(Vec2{ left_top }, 12.f, *entityManager_);//left_top
		p2->getComponent<ECS::CircleCollider>().setColor(255, 32, 0);
		p3 = ECS::Primitive2D::CreateCircle(Vec2{ right_top }, 12.f, *entityManager_);//right_top
		p3->getComponent<ECS::CircleCollider>().setColor(200, 128, 0);
		p4 = ECS::Primitive2D::CreateCircle(Vec2{ right_down }, 12.f, *entityManager_);//right_down
		p4->getComponent<ECS::CircleCollider>().setColor(0, 255, 64);
		//lines
		p1_p2 = ECS::Primitive2D::CreateLine(p1, p2, *entityManager_);
		p2_p3 = ECS::Primitive2D::CreateLine(p2, p3, *entityManager_);
		p3_p4 = ECS::Primitive2D::CreateLine(p3, p4, *entityManager_);

		a_b = ECS::Primitive2D::CreateLine(a, b, *entityManager_);
		b_c = ECS::Primitive2D::CreateLine(b, c, *entityManager_);
		d_e = ECS::Primitive2D::CreateLine(d, e, *entityManager_);
		t.setCounter(0, 0.005f, 0.f, 1.f);


		aPos = &a->getComponent<ECS::Position>();
		bPos = &b->getComponent<ECS::Position>();
		cPos = &c->getComponent<ECS::Position>();
		dPos = &d->getComponent<ECS::Position>();
		ePos = &e->getComponent<ECS::Position>();
		curvePos = &pointOnCurve->getComponent<ECS::Position>();
	}

	void Title::update()
	{

		t.roundTrip();
		//auto a_pos = Vec2::Lerp(
		//	left_down,
		//	left_top,
		//	t.getCurrentCount()
		//);
		//auto b_pos = Vec2::Lerp(
		//	left_top,
		//	right_top,
		//	t.getCurrentCount()
		//);
		//auto c_pos = Vec2::Lerp(
		//	right_top,
		//	right_down,
		//	t.getCurrentCount()
		//);
		//auto d_pos = Vec2::Lerp(
		//	a_pos,
		//	b_pos,
		//	t.getCurrentCount()
		//);
		//auto e_pos = Vec2::Lerp(
		//	b_pos,
		//	c_pos,
		//	t.getCurrentCount()
		//);
		//auto curve_pos = Vec2::Lerp(
		//	d_pos,
		//	e_pos,
		//	t.getCurrentCount()
		//);
	/*	aPos->val = a_pos;
		bPos->val = b_pos;
		cPos->val = c_pos;
		dPos->val = d_pos;
		ePos->val = e_pos;
		curvePos->val = curve_pos;*/

		curvePos->val = GetPointOnBezierCurve(
			left_down,
			left_top,
			right_top,
			right_down,
			t.getCurrentCount());
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