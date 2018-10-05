/**
* @file Scene.hpp
* @brief Sceneの基底クラスです
* @author tonarinohito
* @date 2018/10/06
*/
#pragma once
namespace Scene
{
	//!Sceneの基底クラスです
	class IScene
	{
	public:
		virtual ~IScene() = default;
		virtual void update() = 0;
		virtual void draw() = 0;
	};
}

