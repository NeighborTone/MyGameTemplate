/**
 * @file GameController.hpp
 * @brief �A�v���P�[�V�����̏������s���܂�
 * @author tonarinohito
 * @date 2018/10/06
 */
#pragma once
#include "../ECS/ECS.hpp"
#define ENTITY_GROUP (ECS::Group)GameController::GameGroup
class GameController final
{
private:
	ECS::EntityManager entityManager_;
	void resourceLoad();
public:

	/**
	*  @brief �G���e�B�e�B������̃O���[�v�ł�
	* - �`�惌�C���[�A�������A�G���e�B�e�B�̎擾�Ɏg���܂�
	* - OrderByDraw�g�p���A�ԍ����傫���قǎ�O�ɕ`�悳��܂�
	*/
	enum class GameGroup : ECS::Group
	{
		LAYER0,
		LAYER1,
		MAX,
	};
	GameController();
	//!Entity�����Event�̍X�V�������s���܂�
	void update();
	//!Entity�̕`����s���܂�
	void draw();
};