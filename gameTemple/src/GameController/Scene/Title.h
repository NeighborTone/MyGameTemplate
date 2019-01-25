/**
* @file Title.hpp
* @brief タイトルシーンでの動作を記述します
* @author 
* @date 
*/
#pragma once
#include "../../ECS/ECS.hpp"
#include "Parameter.hpp"
#include "../Scene/SceneManager.hpp"


namespace Scene
{
	class Title : public AbstractScene
	{
	private:
		ECS::EntityManager* entitytManager_;
		ECS::Entity* p;
		ECS::Entity* pp;
		ECS::Entity* line;
		ECS::Entity* hogeCircle;
	public:
		~Title();
		Title(IOnSceneChangeCallback* sceneTitleChange, [[maybe_unused]] Parameter* parame, ECS::EntityManager* entityManager);
		virtual void initialize() override;
		virtual void update() override;
		virtual void draw() override;
	};

}