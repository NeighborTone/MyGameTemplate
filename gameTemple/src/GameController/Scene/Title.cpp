#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"
#include "../../System/System.hpp"
#include "../../Components/Collider.hpp"

namespace Scene
{
	Title::Title(IOnSceneChangeCallback* sceneTitleChange, [[maybe_unused]] Parameter* parame, ECS::EntityManager* entityManager)
		: AbstractScene(sceneTitleChange)
		, entitytManager_(entityManager)
	{
		
	}

	void Title::initialize()
	{
	
	}

	void Title::update()
	{
		entitytManager_->update();

		if (Input::Get().getKeyFrame(KEY_INPUT_X) == 1)
		{
			ON_SCENE_CHANGE(SceneName::GAME, nullptr, StackPopFlag::POP,true);
		}
		
	}

	void Title::draw()
	{
		entitytManager_->orderByDraw(ENTITY_GROUP::MAX);
	}

}