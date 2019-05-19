/**
* @file FPS.hpp
* @brief FPSを扱うクラスです
* 参考元 https://dixq.net/g/03_14.html
* @author tonarinohito
* @date 2018/10/05
*/
#pragma once
#include <memory>
#include <DxLib.h>
#include "../Utility/Utility.hpp"
//!フレームレート固定用クラスです
class Fps final
{
private:
	Fps() = delete;
	class Singleton final
	{
	private:
		int startTime_;         //測定開始時刻
		int count_;             //カウンタ
		float fps_;             //fps
		static constexpr int AVE = 60;//平均を取るサンプル数
		static constexpr int FPS = 60;	//設定したFPS
	public:
		Singleton() :
			startTime_(0),
			count_(0),
			fps_(0)
		{}
		//!計測
		void update()
		{
			if (count_ == 0)
			{
				startTime_ = GetNowCount();
			}
			if (count_ == AVE)
			{
				int t = GetNowCount();
				fps_ = 1000.f / ((t - startTime_) / (float)AVE);
				count_ = 0;
				startTime_ = t;
			}
			++count_;
		}
		//!指定したfpsになるまで待つ
		void wait()
		{
			int tookTime = GetNowCount() - startTime_;	//かかった時間
			int waitTime = count_ * 1000 / FPS - tookTime;	//待つべき時間
			if (waitTime > 0)
			{
				WaitTimer(waitTime);	//待機
			}
		}
		void debugOut()
		{
			DOUT << fps_ << std::endl;
		}
	};

public:
	static Singleton& Get()
	{
		static std::unique_ptr<Singleton> instance = std::make_unique<Singleton>();
		return *instance;
	}
};