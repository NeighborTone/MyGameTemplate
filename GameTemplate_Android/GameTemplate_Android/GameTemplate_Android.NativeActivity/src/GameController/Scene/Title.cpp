
#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"
#include "../../Utility/DXFileRead.hpp"
#include "../../Utility/JsonIO.hpp"
#include "../../Utility/Math.hpp"
//#include <filesystem>
namespace Scene
{
	using namespace ECS;

	namespace
	{
		struct Sphere
		{
			Vec3 pos;
			float r = 0;

			void draw()
			{
				
				MATERIALPARAM MatParam;
				MatParam.Diffuse = GetColorF(0.3, 0.6, 0.7, 1);	// デフューズカラー
				MatParam.Ambient = GetColorF(0.3, 0, 0.3, 1);	// アンビエントカラー
				MatParam.Specular = GetColorF(0.6, 0.3, 0.4, 1);// スペキュラカラー
				MatParam.Emissive = GetColorF(0, 0.2, 0.4, 1);	// エミッシブカラー( 自己発光 )
				MatParam.Power = 10;// スペキュラの強さ

				// マテリアルのパラメータをセット
				SetMaterialParam(MatParam);
				DrawSphere3D(
					pos.getVector<VECTOR>(),
					r,
					32,
					GetColor(int(0.3 * 255), (int(0.6 * 255)), (int(0.7 * 255))),
					GetColor(int(0.6 * 255), (int(0.3 * 255)), (int(0.4 * 255))),
					true);
			}
		};
		Vec3 velocity;
		Vec3 planeNormal{ 0,1,0 };//床
		Sphere s;

		struct Cube
		{
			Vec3 pos;
			Vec3 scale;
			void draw()
			{
				//posをキューブの中心として描画する
				auto radius = scale / 2;
				auto start = pos - radius;
				auto end = pos + radius;
				DrawCube3D(
					start.getVector<VECTOR>(),
					end.getVector<VECTOR>(),
					GetColor(int(1 * 255), (int(1 * 255)), (int(1 * 255))),
					GetColor(int(1 * 255), (int(1 * 255)), (int(1 * 255))),
					true);

			}
		};
		Cube c[5];

		const Vec3 NORMALS[6] =
		{
			Vec3{0,1,0},
			Vec3{0,-1,0},
			Vec3{-1,0,0},
			Vec3{1,0,0},
			Vec3{0,0,-1},
			Vec3{0,0,1}
		};
	}

	Title::~Title()
	{

	}
	Title::Title(IOnSceneChangeCallback* sceneTitleChange, ECS::EntityManager* entityManager)
		: AbstractScene(sceneTitleChange)
		, entityManager_(entityManager)
	{
		
	}

	void Title::initialize()
	{
		//ディレクショナルライトの設定
		CreateDirLightHandle(VGet(0.0f, 1.0f, 0.0f));
		CreateDirLightHandle(VGet(0.0f, -1.0f, 0.0f));
		CreateDirLightHandle(VGet(1.0f, 0.0f, 0.0f));
		CreateDirLightHandle(VGet(-1.0f, 0.0f, 0.0f));
		CreateDirLightHandle(VGet(0.0f, 0.0f, 1.0f));
		CreateDirLightHandle(VGet(0.0f, 0.0f, -1.0f));

		//カメラ設定
		SetCameraNearFar(0.1f, 10000.0f);

		s.pos = Vec3{ 0.f,0.f,0.f };
		s.r = 5;
		c[0].pos = Vec3{ 0,-50,0 };
		c[0].scale = Vec3{ 100,5,100 };

		c[1].pos = Vec3{ 0,60,0 };
		c[1].scale = Vec3{ 100,5,100 };

		c[2].pos = Vec3{ 56,0,0 };
		c[2].scale = Vec3{ 5,100,100 };

		c[3].pos = Vec3{ -70,0,0 };
		c[3].scale = Vec3{ 5,100,100 };

		c[4].pos = Vec3{ 0,0,70 };
		c[4].scale = Vec3{ 100,100,5 };

		velocity.z = 1;
		velocity.y = -1;
		velocity.x = -1;

	}

	void Title::update()
	{
		for (size_t i = 0; i < 5; ++i)
		{
			if (s.pos.getDistanceToPlain(c[i].pos, NORMALS[i]) <= 5)
			{
				velocity.calcReflection(NORMALS[i]);
			}
		}
		//手前(透明な壁)
		if (s.pos.getDistanceToPlain(Vec3{ 0,0,-80 }, NORMALS[5]) <= 5)
		{
			velocity.calcReflection(NORMALS[5]);
		}

		s.pos += velocity * 1;
		static float x = 0, y = 0, z = -120;
		if (Input::Get().getKeyFrame(KEY_INPUT_UP) > 0) { ++z; }
		if (Input::Get().getKeyFrame(KEY_INPUT_DOWN) > 0) { --z; }
		if (Input::Get().getKeyFrame(KEY_INPUT_LEFT) > 0) { --x; }
		if (Input::Get().getKeyFrame(KEY_INPUT_RIGHT) > 0) { ++x; }
		if (Input::Get().getKeyFrame(KEY_INPUT_Q) > 0) { ++y; }
		if (Input::Get().getKeyFrame(KEY_INPUT_E) > 0) { --y; }
		SetCameraPositionAndAngle(VGet(x, y, z), Math::ToRadian(0.f), 0.0f, 0.0f);
		entityManager_->update();
	}

	void Title::draw()
	{
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		//グループ順に描画
		entityManager_->orderByDraw(ENTITY_GROUP::MAX);

		s.draw();
		for (auto& it : c) { it.draw(); }

		entityManager_->draw3D();
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}

}