
#include "Title.h"
#include "../../Input/Input.hpp"
#include "SceneManager.hpp"
#include "../GameController.h"
#include "../src/Utility/Parameter.hpp"
#include "../../Utility/Math.hpp"
//#include <filesystem>
namespace Scene
{
	using namespace ECS;

	namespace
	{
		struct Sphere
		{
			JsonRead json;

			Vec3 pos;
			float r = 0;
			Sphere()
			{
				json.load("data.json");
			}
			void draw()
			{
				MATERIALPARAM MatParam;
				auto d_r = json.getParameter<float>("mat", "Diffuse", 0);
				auto d_g = json.getParameter<float>("mat", "Diffuse", 1);
				auto d_b = json.getParameter<float>("mat", "Diffuse", 2);
				auto d_a = json.getParameter<float>("mat", "Diffuse", 3);

				auto a_r = json.getParameter<float>("mat", "Ambient", 0);
				auto a_g = json.getParameter<float>("mat", "Ambient", 1);
				auto a_b = json.getParameter<float>("mat", "Ambient", 2);
				auto a_a = json.getParameter<float>("mat", "Ambient", 3);

				auto s_r = json.getParameter<float>("mat", "Specular", 0);
				auto s_g = json.getParameter<float>("mat", "Specular", 1);
				auto s_b = json.getParameter<float>("mat", "Specular", 2);
				auto s_a = json.getParameter<float>("mat", "Specular", 3);

				auto e_r = json.getParameter<float>("mat", "Emissive", 0);
				auto e_g = json.getParameter<float>("mat", "Emissive", 1);
				auto e_b = json.getParameter<float>("mat", "Emissive", 2);
				auto e_a = json.getParameter<float>("mat", "Emissive", 3);

				MatParam.Diffuse = GetColorF(d_r, d_g, d_b, d_a);	// デフューズカラー
				MatParam.Ambient = GetColorF(a_r, a_g, a_b, a_a);	// アンビエントカラー
				MatParam.Specular = GetColorF(s_r, s_g, s_b, s_a);	// スペキュラカラー
				MatParam.Emissive = GetColorF(e_r, e_g, e_b, e_a);	// エミッシブカラー( 自己発光 )
				MatParam.Power = json.getParameter<float>("mat", "Power");						// スペキュラの強さ

				// マテリアルのパラメータをセット
				SetMaterialParam(MatParam);
				DrawSphere3D(
					pos.getVector<VECTOR>(),
					r,
					32,
					GetColor(int(d_r * 255), (int(d_g * 255)), (int(d_b * 255))),
					GetColor(int(d_r * 255), (int(d_g * 255)), (int(d_b * 255))),
					true);
			}
		};
		Vec3 velocity;
		Vec3 planeNormal{ 0,1,0 };//床
		Sphere s;

		struct Cube
		{
			JsonRead json{};
			Vec3 pos;
			Vec3 scale;
			Cube()
			{
				json.load("data.json");
			}
			void draw()
			{
				//posをキューブの中心として描画する
				auto radius = scale / 2;
				auto start = pos - radius;
				auto end = pos + radius;

				MATERIALPARAM MatParam;
				auto d_r = json.getParameter<float>("mat", "Diffuse", 0);
				auto d_g = json.getParameter<float>("mat", "Diffuse", 1);
				auto d_b = json.getParameter<float>("mat", "Diffuse", 2);
				auto d_a = json.getParameter<float>("mat", "Diffuse", 3);

				auto a_r = json.getParameter<float>("mat", "Ambient", 0);
				auto a_g = json.getParameter<float>("mat", "Ambient", 1);
				auto a_b = json.getParameter<float>("mat", "Ambient", 2);
				auto a_a = json.getParameter<float>("mat", "Ambient", 3);

				auto s_r = json.getParameter<float>("mat", "Specular", 0);
				auto s_g = json.getParameter<float>("mat", "Specular", 1);
				auto s_b = json.getParameter<float>("mat", "Specular", 2);
				auto s_a = json.getParameter<float>("mat", "Specular", 3);

				auto e_r = json.getParameter<float>("mat", "Emissive", 0);
				auto e_g = json.getParameter<float>("mat", "Emissive", 1);
				auto e_b = json.getParameter<float>("mat", "Emissive", 2);
				auto e_a = json.getParameter<float>("mat", "Emissive", 3);

				MatParam.Diffuse = GetColorF(d_r, d_g, d_b, d_a);	// デフューズカラー
				MatParam.Ambient = GetColorF(a_r, a_g, a_b, a_a);	// アンビエントカラー
				MatParam.Specular = GetColorF(s_r, s_g, s_b, s_a);	// スペキュラカラー
				MatParam.Emissive = GetColorF(e_r, e_g, e_b, e_a);	// エミッシブカラー( 自己発光 )
				MatParam.Power = json.getParameter<float>("mat", "Power");						// スペキュラの強さ

				// マテリアルのパラメータをセット
				SetMaterialParam(MatParam);
				DrawCube3D(
					start.getVector<VECTOR>(),
					end.getVector<VECTOR>(),
					GetColor(int(d_r * 255), (int(d_g * 255)), (int(d_b * 255))),
					GetColor(int(d_r * 255), (int(d_g * 255)), (int(d_b * 255))),
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

		// 壁ずりベクトル
		//
		// out : 正規化壁ずりベクトル（戻り値）
		// front : 進行ベクトル
		// normal: 衝突点での法線ベクトル
		//
		Vec3* calcWallScratchVector(Vec3* out, const Vec3& front, const Vec3& normal) {
			Vec3 normal_n;
			normal_n = normal.Normalize();
			auto nom = front - normal_n * Vec3::Dot(front, normal_n);
			*out = nom.Normalize();
			return out;
		}
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

		//速度ベクトル
		velocity.z = 1;
		velocity.y = -1;
		velocity.x = -1;
		ResourceManager::GetGraph().load("Resource/image/bb.png","p");
	}

	void Title::update()
	{
		for (size_t i = 0; i < std::size(c); ++i)
		{
			//if (s.pos.getDistanceToPlain(c[i].pos, NORMALS[i]) <= 5)
			{
			//	velocity.calcWallScratchVector(NORMALS[i]);
				//velocity.calcReflection(NORMALS[i]);
			}
		}
		if (s.pos.getDistanceToPlain(c[0].pos, NORMALS[0]) <= 5)
		{
			velocity.calcWallScratchVector(NORMALS[0]);
			
		}
		//手前(透明な壁)
		if (s.pos.getDistanceToPlain(Vec3{ 0,0,-80 }, NORMALS[5]) <= 5)
		{
			velocity.calcReflection(NORMALS[5]);
		}

		s.pos += velocity * 1;
		static float x = 0, y = 0, z = -90;
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
	//	DrawBillboard3D(VGet(0,0,0), 0.5f, 0.5f, 1, 0, ResourceManager::GetGraph().getHandle("p"), true,false,false);
		DrawExtendGraph3D(0, 0, 0, 0.1f, 0.1f,ResourceManager::GetGraph().getHandle("p"), true);
		entityManager_->draw3D();
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}

}