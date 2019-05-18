/**
 * @file System.hpp
 * @brief Dxlibの初期化とシステムのチェックを行います
 * @author tonarinohito
 * @date 2018/10/05
 */
#pragma once
#include <DxLib.h>
#include <cassert>
#include "../Utility/JsonIO.hpp"
#include "../Input/Input.hpp"
#ifndef __ANDROID__
#include "../Utility/DXFileRead.hpp"
#include <Windows.h>
namespace
{
	static bool IsFullScreen()
	{
		int flag;
		flag = MessageBox(
			NULL,
			TEXT("フルスクリーンモードで起動しますか？"),
			TEXT("スクリーン設定"),
			MB_YESNO | MB_ICONQUESTION);
		if (flag == IDNO)
		{
			return true;
		}
		return false;
	}
}
#endif
 /*!
 @brief DXlibの処理を隠蔽します
 */
class System final
{
private:
	int w_;
	int h_;
	void systemInit()
	{
#if defined(_WIN64) || defined(_WIN32)
		JsonRead json("systemconf.json");
#endif
#if defined(__ANDROID__)
		JsonRead json(DXFileRead().GetPath("", "/systemconf.json"));
#endif
		//ウィンドウを常にアクティブにするか？
		SetAlwaysRunFlag(json.getParameter<bool>("RunFlag"));
		//ログ消し
		SetOutApplicationLogValidFlag(json.getParameter<bool>("Log"));
		//縦横比維持
		SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
#if defined(_WIN64) || defined(_WIN32)
		// Windows版のコンパイルだったら ChangeWindowMode を実行する
		ChangeWindowMode(IsFullScreen());
		//XAudio2を使用する
		SetEnableXAudioFlag(true);
		SetUseDirect3D11(true);
		//ウインドウタイトルを変更
		SetMainWindowText(json.getParameter<std::string>("Title").c_str());
#endif
		//画面サイズ変更
		w_ = json.getParameter<int>("Width");
		h_ = json.getParameter<int>("Height");
		SetGraphMode(w_, h_, 32);
		
		//ウィンドウモード変更
		//初期化
		DxLib_Init();
		assert(DxLib_IsInit());
		//裏画面設定
		SetDrawScreen(DX_SCREEN_BACK);
		//以下の処理群はモデルの描画には影響しない
		//Ｚバッファを有効にする
		SetUseZBuffer3D(true);
		//Ｚバッファへの書き込みを有効にする
		SetWriteZBuffer3D(true);
		//カリングをON
		SetUseBackCulling(true);
	}
	const bool processLoop() const
	{
		if (ScreenFlip() != 0) return false;
		if (ProcessMessage() != 0) return false;
		if (ClearDrawScreen() != 0) return false;
		Input::Get().updateKey();
		return true;
	}
public:
	//!画面サイズ
	const int getWidth() const { return w_; }
	const int getHeight() const { return h_; }
	System()
	{
		systemInit();
	}
	~System()
	{
		DxLib_End();
	}
	//!@brief Dxlibの更新処理を行います
	[[nodiscard]] const bool isOk() const
	{
		return processLoop();
	}
};