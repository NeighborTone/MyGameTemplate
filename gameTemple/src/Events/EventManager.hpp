/**
* @file EventManager.hpp
* @brief �C�x���g�������Ǘ�����N���X�ł�
* @author tonarinohito
* @date 2018/10/05
*/
#pragma once
#include <string>
#include <iostream>
#include <functional>
#include "../ECS/ECS.hpp"
#include "../GameController/Scene/SceneManager.hpp"
namespace Event
{
	//!�V�[�����Ƃ̃C�x���g�������Ǘ�����N���X�ł�
	class EventManager final
	{
	private:
		class Singleton final
		{
		private:
			using SceneManager = Scene::SceneManager;
			std::vector<std::pair<SceneManager::State, std::function<void(ECS::EntityManager&)>>> events_;
		public:
			/**
			* @brief  �C�x���g�֐���ǉ����܂�
			* @param  state �������s���V�[��
			* @param  func �C�x���g����
			*/
			void addEvent(const SceneManager::State state, std::function<void(ECS::EntityManager&)> func)
			{
				events_.emplace_back(std::make_pair(state, func));
			}
			//!�C�x���g�����s���܂�
			void update(ECS::EntityManager& entityManager)
			{
				for (auto& it : events_)
				{
					if (SceneManager::Get().getCurrentScene() == it.first)
					{
						it.second(entityManager);
					}
				}
			}
		};
	public:
		static Singleton& Get()
		{
			static auto inst = std::make_unique<Singleton>();
			return *inst;
		}
	};
}
