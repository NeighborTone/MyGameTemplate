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
		//OrderByDraw�g�p���A�ԍ����傫���قǎ�O�ɕ`�悳���
		MAX,		//Group�ő吔
	};
	GameController();
	//!Entity�����Event�̍X�V�������s���܂�
	void update();
	//!Entity�̕`����s���܂�
	void draw();
};