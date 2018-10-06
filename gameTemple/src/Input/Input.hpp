/**
* @file Input.hpp
* @brief ���͊֘A�̏������܂Ƃ߂܂�
* @author tonarinohito
* @date 2018/10/05
*/
#pragma once
#include <memory>
#include <DxLib.h>
/*!
@brief �L�[�C�x���g�N���X�ł�
*/
class Input final
{
private:
	class Singleton final
	{
	private:
		//�L�[�̓��͏�Ԃ��i�[����
		int key_[256];
	public:
		Singleton() = default;
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;

		/**
		* @brief �L�[�̓��͏�Ԃ��X�V���܂�
		*/
		void updateKey()
		{
			char tmpKey[256];
			GetHitKeyStateAll(tmpKey);	//���݂̃L�[�̏�Ԃ��i�[
			for (int i = 0; i < 256; ++i)
			{
				if (tmpKey[i] != 0)
				{
					++key_[i];
				}
				else  //������Ă��Ȃ����
				{
					key_[i] = 0;
				}
			}
		}
		/**
		* @brief �L�[�̓��͏�Ԃ��擾���܂�
		* @param keycode ���ׂ����L�[�R�[�h
		* @return �����Ă���t���[�����B������Ă��Ȃ��ꍇ0���Ԃ�܂�
		*/
		[[nodiscard]] int getKeyFrame(int keycode)
		{
			return key_[keycode];	
		}
	};
public:
	inline static Singleton& Get()
	{
		static std::unique_ptr<Singleton> inst =
			std::make_unique<Singleton>();
		return *inst;
	}
};
