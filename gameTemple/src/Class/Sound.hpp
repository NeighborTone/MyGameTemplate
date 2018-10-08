/**
* @file Sound.hpp
* @brief DX���C�u�����̃T�E���h�֐������b�v���܂�
* @author tonarinohito
* @date 2018/10/08
*/
#pragma once
#include "ResourceManager.hpp"

//!�T�E���h����N���X�ł�
class Sound final
{
private:
	std::string name_;
	int handle_;
public:
	//!�R���X�g���N�^�œo�^�����T�E���h�n���h�������w�肵�܂�
	Sound(const std::string& soundName)
	{
		assert(ResourceManager::GetSound().hasHandle(soundName));
		handle_ = ResourceManager::GetSound().getHandle(soundName);
		name_ = soundName;
	}
	//!�T�E���h���Đ����܂�
	void play(bool isLoop)
	{
		if (isLoop)
		{
			PlaySoundMem(handle_, DX_PLAYTYPE_LOOP);
		}
		else
		{
			PlaySoundMem(handle_, DX_PLAYTYPE_BACK);
		}
	}
	//!�T�E���h�̍Đ������~�߂܂�
	void stop()
	{
		StopSoundMem(handle_);
	}
	//!�T�E���h���Đ������擾���܂�
	[[nodiscard]] const bool isPlay() const
	{
		switch (CheckSoundMem(handle_))
		{
		case 0: return false;
		case 1: return true;
		}
	}
	//!�T�E���h�̌��݂̍Đ��ʒu���~���b�P�ʂŎ擾���܂�
	[[nodiscard]] const int getCurrentTime() const
	{
		return GetSoundCurrentTime(handle_);
	}
	//!�T�E���h�̑����Ԃ��~���b�P�ʂŎ擾���܂�
	[[nodiscard]] const int getTotalTime() const 
	{
		return GetSoundTotalTime(handle_);
	}
	/**
	* @brief �T�E���h�̃p����ݒ肵�܂�
	* @param  panPosition ���̈ʒu(-255~255)
	* @return �n���h�������݂�����true
	*/
	void setPan(const int panPosition)
	{
		ChangePanSoundMem(panPosition,handle_);
	}
	//!���̃T�E���h�̉��ʂ�0.0f~1.f�Ŏw��
	void setGain(float gain)
	{
		ChangeVolumeSoundMem(int(255 * gain), handle_);
	}
	//!���ׂẴT�E���h�̉��ʂ�0.0f~1.f�Ŏw��
	static void SetAllGain(float gain)
	{
		auto& sounds = ResourceManager::GetSound().getSoundMap();
		for (auto&[key, val] : sounds)
		{
			ChangeVolumeSoundMem(int(255 * gain), val);
		}
	}
	
};