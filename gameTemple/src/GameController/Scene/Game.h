/**
* @file Game.hpp
* @brief ゲームシーンでの動作を記述します
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