
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
		Vec2 right_down{ 900.f, 700.f };
		Vec2 center_down{ 520.f, 290.f };
		std::vector<Vec2> points{ left_down, left_top ,right_top ,right_down ,center_down};
		//movepoints

		ECS::Entity* pointOnCurve = nullptr;

		//lines

		//points
		ECS::Entity* p1 = nullptr;
		ECS::Entity* p2 = nullptr;
		ECS::Entity* p3 = nullptr;
		ECS::Entity* p4 = nullptr;
		ECS::Entity* p5 = nullptr;
		ECS::Position* curvePos = nullptr;

		Counter_f t;

		const Vec2 GetPointOnBezierCurve(Vec2& p0, Vec2& p1, Vec2& p2, Vec2& p3, const float& t)
		{
			float u = 1.f - t;
			float t2 = t * t;
			float u2 = u * u;
			float u3 = u2 * u;
			float t3 = t2 * t;

			const Vec2 result =
				p0 * (u3) +
				p1 * (3.f * u2 * t) +
				p2 * (3.f * u * t2) +
				p3 * (t3);

			return result;
		}

		//2次
		const Vec2 GetBezier2(float b, std::vector<Vec2> points)
		{
			auto a = 1 - b;
			auto x = b * b * points[2].x + 2 * b * a * points[1].x + a * a * points[0].x;
			auto y = b * b * points[2].y + 2 * b * a * points[1].y + a * a * points[0].y;
			Vec2 res{ x, y };
			return res;
		}
		//3次
		const Vec2 GetBezier3(float t, std::vector<Vec2> points)
		{
			auto tp = 1 - t;
			auto x = t * t * t * points[3].x + 3 * t * t * tp * points[2].x + 3 * t * tp * tp * points[1].x + tp * tp * tp * points[0].x;
			auto y = t * t * t * points[3].y + 3 * t * t * tp * points[2].y + 3 * t * tp * tp * points[1].y + tp * tp * tp * points[0].y;
			Vec2 res{ x, y };
			return res;
		}
		//4次
		const Vec2 GetBezier4(float t, std::vector<Vec2> points)
		{
			auto tp = 1 - t;
			auto x = t * t * t * t * points[4].x + 4 * t * t * t * tp * points[3].x + 4 * t * t * tp * tp *points[2].x + 3 * t * tp * tp * tp * points[1].x + tp * tp * tp * tp * points[0].x;
			auto y = t * t * t * t * points[4].y + 4 * t * t * t * tp * points[3].y + 4 * t * t * tp * tp * points[2].y + 3 * t * tp * tp * tp * points[1].y + tp * tp * tp * tp * points[0].y;
			Vec2 res{ x, y };
			return res;
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
		p5 = ECS::Primitive2D::CreateCircle(Vec2{ center_down }, 12.f, *entityManager_);
		p5->getComponent<ECS::CircleCollider>().setColor(32, 255, 255);
		
		t.setCounter(0, 0.005f, 0.f, 1.f);
	}

	void Title::update()
	{
		t.roundTrip();
		pointOnCurve->getComponent<ECS::Position>().val = GetBezier4(t.getCurrentCount(), points);
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