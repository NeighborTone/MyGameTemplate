#pragma once 
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "Vec.hpp"


class Math
{
public:
	inline static const float ToRadian(const float& degree)
	{
		return degree * (static_cast<float>(M_PI)) / 180.f;
	}
	inline static const float ToDegree(const float& radian)
	{
		return radian * (static_cast<float>(180.0f / M_PI));
	}
	//1、向きベクトル2、衝突点
	inline static const Vec2 GetReflectVec(const Vec2& direction, Vec2& pointNormal)
	{
		auto velocity_vector = -direction.getNormalize();
		auto reflect_vector = 2.0f * velocity_vector.dot(pointNormal);

		return (pointNormal * reflect_vector - velocity_vector).getNormalize();
	}
	//線分の法線を求める
	inline static const Vec2 GetLineNormal(const Vec2& p1, const Vec2& p2)
	{
		auto dirVec = p1 - p2;
		auto normal = Vec2{ -dirVec.y, dirVec.x };

		return normal.normalize();
	}
	//反射ベクトルを求める
	inline static const Vec2 GetReflect(const Vec2 & velocity, const Vec2 & normal)
	{
		auto n = (velocity.dot(normal) >= 0) ?
			normal :
			-normal;

		return GetReflectVec(velocity, n);
	}
	inline static const Vec2 GetPointOnBezierCurve(Vec2 & p0, Vec2 & p1, Vec2 & p2, Vec2 & p3, const float& t)
	{
		float u = 1.f - t;
		float t2 = t * t;
		float u2 = u * u;
		float u3 = u2 * u;
		float t3 = t2 * t;

		const Vec2 result =
			p0 * (u3)+
			p1 * (3.f * u2 * t) +
			p2 * (3.f * u * t2) +
			p3 * (t3);

		return result;
	}

	//2次
	inline static const Vec2 GetBezier2(float b, std::vector<Vec2> points)
	{
		auto a = 1 - b;
		auto x = b * b * points[2].x + 2 * b * a * points[1].x + a * a * points[0].x;
		auto y = b * b * points[2].y + 2 * b * a * points[1].y + a * a * points[0].y;
		Vec2 res{ x, y };
		return res;
	}
	//3次
	inline static const Vec2 GetBezier3(float t, std::vector<Vec2> points)
	{
		auto tp = 1 - t;
		auto x =
			t * t * t * points[3].x + 3 *
			t * t * tp * points[2].x + 3 *
			t * tp * tp * points[1].x +
			tp * tp * tp * points[0].x;
		auto y =
			t * t * t * points[3].y + 3 *
			t * t * tp * points[2].y + 3 *
			t * tp * tp * points[1].y +
			tp * tp * tp * points[0].y;
		Vec2 res{ x, y };
		return res;
	}
	//4次
	inline static const Vec2 GetBezier4(float t, std::vector<Vec2> points)
	{
		auto tp = 1 - t;
		auto x =
			t * t * t * t * points[4].x + 4 *
			t * t * t * tp * points[3].x + 4 *
			t * t * tp * tp * points[2].x + 4 *
			t * tp * tp * tp * points[1].x +
			tp * tp * tp * tp * points[0].x;
		auto y =
			t * t * t * t * points[4].y + 4 *
			t * t * t * tp * points[3].y + 4 *
			t * t * tp * tp * points[2].y + 4 *
			t * tp * tp * tp * points[1].y +
			tp * tp * tp * tp * points[0].y;
		Vec2 res{ x, y };
		return res;
	}
};