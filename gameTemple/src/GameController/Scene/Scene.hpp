/**
* @file Scene.hpp
* @brief Scene�̊��N���X�ł�
* @author tonarinohito
* @date 2018/10/06
*/
#pragma once
namespace Scene
{
	//!Scene�̊��N���X�ł�
	class IScene
	{
	public:
		virtual ~IScene() = default;
		virtual void update() = 0;
		virtual void draw() = 0;
	};
}

