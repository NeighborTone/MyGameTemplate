/**
* @file SceneManager.hpp
* @brief Sceneオブジェクトに必要な基底クラスや列挙型です
* @author tonarinohito
* @date 2018/10/14
*/
#pragma once
#include "../../ECS/ECS.hpp"
#include "../../Utility/Utility.hpp"
#include "../Scene/Parameter.hpp"
#include <map>
#include <any>

namespace Scene
{
	//!シーンの状態
	enum class SceneName
	{
		TITLE,
		GAME,
		BACK_TO_SCENE	//前のシーンに戻る
	};

	//!シーン変更時のコールバックです
	class IOnSceneChangeCallback
	{
	public:
		IOnSceneChangeCallback() = default;
		virtual ~IOnSceneChangeCallback() = default;
		virtual void onSceneChange(const SceneName& scene, const Parameter* parame, const bool stackClear) = 0;
		virtual void stackClear() = 0;
	};

	//!シーンの基底クラスです
	class AbstractScene
	{
	public:
		AbstractScene(IOnSceneChangeCallback* sceneCallback)
		{
			callBack = sceneCallback;
		}
		virtual ~AbstractScene() = default;
		virtual void update() = 0;
		virtual void draw() = 0;
		IOnSceneChangeCallback& getCallBack() const { return *callBack; }
	private:
		IOnSceneChangeCallback* callBack;
	};
}