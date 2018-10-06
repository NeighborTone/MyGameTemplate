/**
* @file SceneManager.hpp
* @brief Scene�I�u�W�F�N�g���Ǘ����܂�	
* @author tonarinohito
* @date 2018/10/06
*/
#pragma once
#include "../../ECS/ECS.hpp"
#include "../../Utility/Utility.hpp"
#include "Title.h"
#include "Game.h"

namespace Scene
{
	//!�V�[���̊Ǘ����s���܂�
	class SceneManager final
	{
	public:
		//!�V�[���̏�Ԃł�
		enum class State : short
		{
			TITLE,
			SELECT,
			PAUSE,
			GAME,
			RESULT
		};
	private:
		class Singleton final
		{
		private:
			State state_;
			IScene* pScene_ = nullptr;
		public:
			~Singleton()
			{
				Utility::SafeDelete(pScene_);
			}
			/**
			* @brief �����������V�[�������肵�܂�
			* @param scene �w�肵�����V�[��
			* @param entityManager EntityManager
			*/
			void changeScene(const State& scene, ECS::EntityManager& entityManager)
			{
				Utility::SafeRelease(pScene_);
				Utility::SafeDelete(pScene_);
				switch (scene)
				{
				case State::TITLE:  pScene_ = new Title(entityManager); break;
				case State::SELECT:	break;
				case State::PAUSE:  break;
				case State::GAME:   pScene_ = new Game(entityManager); break;
				case State::RESULT: break;
				}
				state_ = scene;
			}
			//!���ݎw�肳��Ă���V�[���̍X�V���s���܂�
			void update()
			{
				pScene_->update();
			}
			//!���ݎw�肳��Ă���V�[���̕`����s���܂�
			void draw()
			{
				pScene_->draw();
			}
			//!���݂̃V�[����Ԃ��܂�
			const State& getCurrentScene() const
			{
				return state_;
			}
		};
	public:
		static Singleton& Get()
		{
			static std::unique_ptr<Singleton> inst =
				std::make_unique<Singleton>();
			return *inst;
		}
	};
}