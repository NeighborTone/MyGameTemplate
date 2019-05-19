/**
* @file Title.hpp
* @brief タイトルシーンでの動作を記述します
* @author 
* @date 
*/
#pragma once
#include "../../ECS/ECS.hpp"
#include "SceneManager.hpp"

namespace Scene
{
	class Title : public AbstractScene
	{
	private:
		ECS::EntityManager* entityManager_{};
	public:
		~Title();
		Title(IOnSceneChangeCallback* sceneTitleChange, ECS::EntityManager* entityManager);
		void initialize() override;
		void update() override;
		void draw() override;
	};

}