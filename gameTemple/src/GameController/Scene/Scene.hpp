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
		//!�X�V�������s���܂�
		virtual void update() = 0;
		//!�`�揈�����s���܂�
		virtual void draw() = 0;
		//!���\�[�X�̊J�����s���܂�
		virtual void release() = 0;
	};
}

