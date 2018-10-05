#pragma once
#include "../ECS/ECS.hpp"
#define ENTITY_GROUP (ECS::Group)GameController::GameGroup
class GameController final
{
private:
	ECS::EntityManager entityManager_;
	void resourceLoad();
public:
	enum class GameGroup : ECS::Group
	{
		//OrderByDraw使用時、番号が大きいほど手前に描画される
		MAX,		//Group最大数
	};
	GameController();
	//!EntityおよびEventの更新処理を行います
	void update();
	//!Entityの描画を行います
	void draw();
};