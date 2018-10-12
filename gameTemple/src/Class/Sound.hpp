﻿/**
* @file Sound.hpp
* @brief DXライブラリのサウンド関数をラップします
* @detail ResourceManagerで読み込んだハンドルが対象です
* @author tonarinohito
* @date 2018/10/08
*/
#pragma once
#include "ResourceManager.hpp"

//!すべてのサウンドの音量に対しての処理を行います
class MasterSound final
{
private:
	class Singleton final
	{
	private:
		float seGain_ = 1.0f;
		float bgmGain_ = 1.0f;
	public:
		//!すべてのSEサウンドの音量を0.0f~1.fで指定
		void setAllSEGain(float gain)
		{
			seGain_ = gain;
		}
		//!すべてのBGMサウンドの音量を0.0f~1.fで指定
		void setAllBGMGain(float gain)
		{
			bgmGain_ = gain;
		}
		//!登録されているサウンドの更新を行います
		void update()
		{
			auto& sounds = ResourceManager::GetSound().getSoundMap();
			for (auto&[key, val] : sounds)
			{
				switch (val.second)
				{
				case SoundType::SE:
					ChangeVolumeSoundMem(int(255 * seGain_), val.first);
					break;
				case SoundType::BGM:
					ChangeVolumeSoundMem(int(255 * bgmGain_), val.first);
					break;
				}
			}
		}
	};
public:
	inline static Singleton& Get()
	{
		static auto inst = std::make_unique<Singleton>();
		return *inst;
	}
};

//!サウンド操作クラスです
class Sound final
{
private:
	std::string name_;
	int handle_;
	float gain_ = 1.f;
public:

	//!コンストラクタで登録したサウンドハンドル名を指定します
	Sound(const std::string& soundName)
	{
		assert(ResourceManager::GetSound().hasHandle(soundName));
		handle_ = ResourceManager::GetSound().getHandle(soundName);
		name_ = soundName;
	}
	/**
	* @brief サウンドを再生します
	* @param  isLoop ループ再生するかどうか
	* @param  isContinuation stop()で止めたサウンドを続きから再生するかどうか。falseで続きから再生する
	*/
	void play(const bool isLoop, bool isContinuation = false)
	{
		if (isLoop)
		{
			//trueなら最初から再生
			PlaySoundMem(handle_, DX_PLAYTYPE_LOOP, isContinuation);
		}
		else
		{
			PlaySoundMem(handle_, DX_PLAYTYPE_BACK, isContinuation);
		}
	}
	//!サウンドの再生を止めます
	void stop()
	{
		StopSoundMem(handle_);
	}
	//!サウンドが再生中か取得します
	[[nodiscard]] const bool isPlay() const
	{
		switch (CheckSoundMem(handle_))
		{
		case 0: return false;
		case 1: return true;
		}
	}
	//!サウンドの現在の再生位置をミリ秒単位で取得します
	[[nodiscard]] const int getCurrentTime() const
	{
		return GetSoundCurrentTime(handle_);
	}
	//!サウンドの総時間をミリ秒単位で取得します
	[[nodiscard]] const int getTotalTime() const 
	{
		return GetSoundTotalTime(handle_);
	}
	/**
	* @brief サウンドのパンを設定します
	* @param  panPosition 音の位置(-255~255)
	* @return ハンドルが存在したらtrue
	*/
	void setPan(const int panPosition)
	{
		ChangePanSoundMem(panPosition,handle_);
	}
};