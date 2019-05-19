/**
* @file Collider.hpp
* @brief コリジョンに必要なコンポーネント群です。
* @author tonarinohito
* @date 2018/10/05
*/
#pragma once
#include "../ECS/ECS.hpp"
#include "BasicComponents.hpp"
#include <DxLib.h>

namespace ECS
{
	class IBoxCollider
	{
	public:
		IBoxCollider() = default;
		virtual ~IBoxCollider() = default;
		/** @brief コリジョンの色を指定します*/
		virtual void setColor(const int r, const int g, const int b) = 0;
		/** @brief コリジョンの位置を変更します*/
		virtual void setOffset(const float x, const float y) = 0;
		/** @brief コリジョンを塗りつぶします*/
		virtual void fillEnable() = 0;
		/** @brief コリジョンの塗りつぶしを解除します*/
		virtual void fillDisable() = 0;
		/** @brief コリジョンの描画を有効にします*/
		virtual void drawEnable() = 0;
		/** @brief コリジョンの描画を無効にします*/
		virtual void drawDisable() = 0;
		/** @brief 幅を返します*/
		virtual float w() const = 0;
		/** @brief 高さを返します*/
		virtual float h() const = 0;
		/** @brief x座標を返します、この値はオフセットされた値です*/
		virtual float x() const = 0;
		/** @brief y座標を返します、この値はオフセットされた値です*/
		virtual float y() const = 0;
	};

	class ICircleCollider
	{
	public:
		ICircleCollider() = default;
		virtual ~ICircleCollider() = default;
		/** @brief コリジョンの色を指定します*/
		virtual void setColor(const int r, const int g, const int b) = 0;
		/** @brief コリジョンの位置を変更します*/
		virtual void setOffset(const float x, const float y) = 0;
		/** @brief コリジョンを塗りつぶします*/
		virtual void fillEnable() = 0;
		/** @brief コリジョンの塗りつぶしを解除します*/
		virtual void fillDisable() = 0;
		/** @brief コリジョンの描画を有効にします*/
		virtual void drawEnable() = 0;
		/** @brief コリジョンの描画を無効にします*/
		virtual void drawDisable() = 0;
		/** @brief 半径を返します*/
		virtual float radius() const = 0;
		/** @brief x座標を返します、この値はオフセットされた値です*/
		virtual float x() const = 0;
		/** @brief y座標を返します、この値はオフセットされた値です*/
		virtual float y() const = 0;
	};

	/*!
	@brief 2D矩形です.
	@details  Positionが必要です
	*/
	class BoxCollider final : public ComponentSystem, public IBoxCollider
	{
	private:
		Position2D* pos_ = nullptr;
		Vec2 offSetPos_;
		float w_, h_;
		unsigned int color_ = 4294967295;
		bool isFill_ = false;
		bool isDraw_ = true;
	public:
		explicit BoxCollider(const Vec2& size)
		{
			w_ = size.x;
			h_ = size.y;
		}
		explicit BoxCollider(const float ww, const float hh)
		{
			w_ = ww;
			h_ = hh;
		}
		~BoxCollider()
		{
			pos_ = nullptr;
		}
		void initialize() override
		{
			pos_ = &owner->getComponent<Position2D>();
		}
		void draw2D() override
		{
			if (isDraw_)
			{
				auto convert = pos_->val.offsetCopy(offSetPos_.x, offSetPos_.y);
				DrawBoxAA(
					convert.x,
					convert.y,
					convert.x + w(),
					convert.y + h(),
					color_, isFill_, 2);
			}
		}
		void setColor(const int r, const int g, const int b) override
		{
			color_ = GetColor(r, g, b);
		}
		void setOffset(const float x, const float y) override
		{
			offSetPos_.x = x;
			offSetPos_.y = y;
		}
		void fillEnable() override { isFill_ = true; }
		void fillDisable() override { isFill_ = false; }
		void drawEnable() override { isDraw_ = true; }
		void drawDisable() override { isDraw_ = false; }
		float w() const override { return w_; }
		float h() const override { return h_; }
		float x() const override { return pos_->val.x + offSetPos_.x; }
		float y() const override { return pos_->val.y + offSetPos_.y; }
	};
	
	class CubeCollider :public ComponentSystem
	{
	private:
		Position3D* pos_ = nullptr;
		Vec3 offSetPos_{ 0.f,0.f,0.f };
		Scale3D* scale_ = nullptr;
		MATERIALPARAM material_;
		bool isFill_ = false;
		bool isDraw_ = true;
	public:
		CubeCollider()
		{
			material_.Diffuse = GetColorF(1, 1, 1, 1);
			material_.Ambient = GetColorF(0, 0, 0, 1);
			material_.Specular = GetColorF(1, 1, 1, 1);
			material_.Emissive = GetColorF(0, 0, 0, 0);
		}
		void initialize() override
		{
			pos_ = &owner->getComponent<Position3D>();
			scale_ = &owner->getComponent<Scale3D>();
		}

		void draw3D() override
		{
			if (isDraw_)
			{
				//posをキューブの中心として描画する
				auto radius = scale_->val * 0.5f;
				auto start = pos_->val - radius;
				auto end = pos_->val + radius;
				//マテリアルのパラメータをセット
				SetMaterialParam(material_);
				DrawCube3D(
					start.getVector<VECTOR>(),
					end.getVector<VECTOR>(),
					GetColor(int(material_.Diffuse.r * 255), (int(material_.Diffuse.g * 255)), (int(material_.Diffuse.b * 255))),
					GetColor(int(material_.Specular.r * 255), (int(material_.Specular.g * 255)), (int(material_.Specular.b * 255))),
					isFill_);
			}
		}
		void setOffset(const float& x, const float& y, const float& z)
		{
			offSetPos_.x = x;
			offSetPos_.y = y;
			offSetPos_.z = z;
		}

		void setMaterial(const MATERIALPARAM& mat)
		{
			material_.Diffuse = mat.Diffuse;	// デフューズカラー
			material_.Ambient = mat.Ambient;	// アンビエントカラー
			material_.Specular = mat.Specular;	// スペキュラカラー
			material_.Emissive = mat.Emissive;	// エミッシブカラー( 自己発光 )
			material_.Power = mat.Power;		// スペキュラの強さ
		}
		void fillEnable() { isFill_ = true; }
		void fillDisable() { isFill_ = false; }
		void drawEnable() { isDraw_ = true; }
		void drawDisable() { isDraw_ = false; }
		const float x() const { return pos_->val.x + offSetPos_.x; }
		const float y() const { return pos_->val.y + offSetPos_.y; }
		const float z() const { return pos_->val.z + offSetPos_.z; }
	};

	/*!
	@brief 円です
	@details  Positionが必要です
	*/
	class CircleCollider final : public ComponentSystem, public ICircleCollider
	{
	private:
		Position2D* pos_ = nullptr;
		Vec2 offSetPos_;
		float r_;
		unsigned int color_ = 4294967295;
		bool isFill_ = false;
		bool isDraw_ = true;
	public:
		explicit CircleCollider(const float r)
		{
			r_ = r;
		}
		~CircleCollider()
		{
			pos_ = nullptr;
		}
		void initialize() override
		{
			pos_ = &owner->getComponent<Position2D>();
		}
		void draw2D() override
		{
			if (isDraw_)
			{
				auto convert = pos_->val.offsetCopy(offSetPos_.x, offSetPos_.y);
				DrawCircleAA(
					convert.x,
					convert.y,
					r_,
					24,
					color_, isFill_, 2);
			}
		}
		void setColor(const int r, const int g, const int b) override
		{
			color_ = GetColor(r, g, b);
		}
		void setOffset(const float x, const float y) override
		{
			offSetPos_.x = x;
			offSetPos_.y = y;
		}
		void fillEnable() override { isFill_ = true; }
		void fillDisable() override { isFill_ = false; }
		void drawEnable() override { isDraw_ = true; }
		void drawDisable() override { isDraw_ = false; }
		float radius() const override { return r_; }
		float x() const override { return pos_->val.x + offSetPos_.x; }
		float y() const override { return pos_->val.y + offSetPos_.y; }
	};

	class SphereCollider :public ComponentSystem
	{
	private:
		Position3D* pos_ = nullptr;
		Vec3 offSetPos_{0.f,0.f,0.f};
		float r_;
		MATERIALPARAM material_;
		bool isFill_ = false;
		bool isDraw_ = true;
	public:
		SphereCollider(const float& radius):
		r_(radius)
		{
			material_.Diffuse = GetColorF(1, 1, 1, 1);
			material_.Ambient = GetColorF(0, 0, 0, 1);
			material_.Specular = GetColorF(1, 1, 1, 1);
			material_.Emissive = GetColorF(0, 0, 0, 0);
		}
		void initialize() override
		{
			pos_ = &owner->getComponent<Position3D>();
		}

		void draw3D() override
		{
			if (isDraw_)
			{
				auto convert = pos_->val.offsetCopy(offSetPos_.x, offSetPos_.y, offSetPos_.z);
				//マテリアルのパラメータをセット
				SetMaterialParam(material_);
				DrawSphere3D(
					convert.getVector<VECTOR>(),
					r_,
					16,
					GetColor(int(material_.Diffuse.r * 255), (int(material_.Diffuse.g * 255)), (int(material_.Diffuse.b * 255))),
					GetColor(int(material_.Specular.r * 255), (int(material_.Specular.g * 255)), (int(material_.Specular.b * 255))),
					isFill_);
			}
		}
		void setOffset(const float& x, const float& y, const float& z)
		{
			offSetPos_.x = x;
			offSetPos_.y = y;
			offSetPos_.z = z;
		}

		void setMaterial(const MATERIALPARAM& mat)
		{
			material_.Diffuse = mat.Diffuse;	// デフューズカラー
			material_.Ambient = mat.Ambient;	// アンビエントカラー
			material_.Specular = mat.Specular;	// スペキュラカラー
			material_.Emissive = mat.Emissive;	// エミッシブカラー( 自己発光 )
			material_.Power = mat.Power;		// スペキュラの強さ
		}
		void fillEnable() { isFill_ = true; }
		void fillDisable() { isFill_ = false; }
		void drawEnable() { isDraw_ = true; }
		void drawDisable() { isDraw_ = false; }
		float radius() const  { return r_; }
		float x() const { return pos_->val.x + offSetPos_.x; }
		float y() const { return pos_->val.y + offSetPos_.y; }
		float z() const { return pos_->val.z + offSetPos_.z; }
	};

	/*!
	* @brief 2D線分です.
	* @details Position,LineData2Dが必要です
    * -線分の始点はPositionと同じ値になります
    */
	class LineCollider final : public ComponentSystem
	{
	private:
		LineData2D* line_ = nullptr;
		Entity* start_ = nullptr;
		Entity* end_ = nullptr;
		Vec2 offSetPos1_;
		Vec2 offSetPos2_;
		unsigned int color_ = 4294967295;
		bool isDraw_ = true;
		bool isJoint = false;
	public:
		void initialize() override
		{
			if (!owner->hasComponent<LineData2D>())
			{
				owner->addComponent<LineData2D>();
			}
			line_ = &owner->getComponent<LineData2D>();
		}
		void update() override
		{
			if (isJoint)
			{
				line_->p1 = start_->getComponent<Position2D>().val;
				line_->p2 = end_->getComponent<Position2D>().val;
			}
		}
		void draw2D() override
		{
			if (isDraw_)
			{
				auto convert_p1 = line_->p1.offsetCopy(offSetPos1_.x, offSetPos1_.y);
				auto convert_p2 = line_->p2.offsetCopy(offSetPos2_.x, offSetPos2_.y);
				DrawLineAA(convert_p1.x, convert_p1.y, convert_p2.x, convert_p2.y,color_,1);
			}
		}
		/** @brief 線分の色を指定します*/
		void setColor(const int r, const int g, const int b) 
		{
			color_ = GetColor(r, g, b);
		}
		/** @brief 始点座標をずらします*/
		void setOffsetStartPosition(const float x, const float y)
		{
			offSetPos1_.x = x;
			offSetPos1_.y = y;
		}
		/** @brief 終点座標をずらします*/
		void setOffsetEndPosition(const float x, const float y)
		{
			offSetPos2_.x = x;
			offSetPos2_.y = y;
		}
		//!引数に指定したエンティティ同士を線で結びます
		void setJoint(Entity* start, Entity* end)
		{
			isJoint = true;
			start_ = start;
			end_ = end;
		}
		/** @brief 線分の描画を有効にします*/
		void drawEnable() { isDraw_ = true; }
		/** @brief 線分の描画を無効にします*/
		void drawDisable() { isDraw_ = false; }
		/** @brief 始点座標を返します、この値はオフセットされた値です*/
		const Vec2 getStartPosition() const  { return line_->p1 + offSetPos1_; }
		/** @brief 終点座標を返します、この値はオフセットされた値です*/
		const Vec2 getEndPosition() const { return line_->p2 + offSetPos2_; }
	};


	
}