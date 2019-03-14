/**
* @file Title.hpp
* @brief タイトルシーンでの動作を記述します
* @author 
* @date 
*/
#pragma once
#include "../../ECS/ECS.hpp"
#include "../Scene/SceneManager.hpp"

namespace Scene
{
	class Title : public AbstractScene
	{
	private:
		ECS::EntityManager* entitytManager_;
		ECS::Entity* player = nullptr;
		ECS::Entity* child01 = nullptr;
		ECS::Entity* child02 = nullptr;
	public:
		~Title();
		Title(IOnSceneChangeCallback* sceneTitleChange, ECS::EntityManager* entityManager);
		virtual void initialize() override;
		virtual void update() override;
		virtual void draw() override;
	};

}