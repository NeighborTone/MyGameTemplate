/**
* @file Game.hpp
* @brief �Q�[���V�[���ł̓�����L�q���܂�
* @author 
* @date 
*/
#pragma once
#include "../../ECS/ECS.hpp"
#include "Scene.hpp"

namespace Scene
{
	class Game final : public IScene
	{
	private:
		ECS::EntityManager& entityManager_;
	public:
		Game(ECS::EntityManager& manager); 
		void update() override;
		void draw() override;
	};
}