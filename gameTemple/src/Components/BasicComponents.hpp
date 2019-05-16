/**
* @file BasicComponents.hpp
* @brief 座標や速度などの基本的なコンポーネント群です。
* @author tonarinohito
* @date 2018/10/05
*/
#pragma once

#include "../ECS/ECS.hpp"
#include "../Utility/Vec.hpp"
#include "../Utility/Math.hpp"
#include <DxLib.h>
#include <functional>

namespace ECS
{
	/*!
	@brief  座標です。データの型はVec2です
	*/
	struct Position final : public ComponentData
	{
		Vec2 val;
		Position() = default;
		explicit Position(const Vec2& v) :val(v) {}
		explicit Position(const float& x, const float& y) :val(x, y) {}
	};
	/*!
	@brief  回転値です。データの型はfloatです
	*/
	struct Rotation final : public ComponentData
	{
		float val;
		Rotation() = default;
		explicit Rotation(const float& r) : val(r) {}
	};
	/*!
	@brief  x,y方向の拡大率です。データの型はVec2です
	*/
	struct Scale final : public ComponentData
	{
		Vec2 val;
		Scale() = default;
		explicit Scale(const Vec2& scale) : val(scale) {}
		explicit Scale(const float& scale) : val(scale, scale) {}
		explicit Scale(const float& scaleX, const float& scaleY) : val(scaleX, scaleY) {}
	};
	/*!
	@brief  速度です。データの型はVec2です
	*/
	struct Velocity final : public ComponentData
	{
		Vec2 val;
		Velocity() = default;
		explicit Velocity(const Vec2& v) :val(v) {}
		explicit Velocity(const float& x, const float& y) : val(x, y) {}
	};
	/*!
	@brief  向きです。データの型はenum class Dirです
	*/
	struct Direction final : public ComponentData
	{
		enum class Dir : short
		{
			RIGHT,
			LEFT,
			UP,
			DOWN
		};
		Dir val;
		explicit Direction() : val(Dir::RIGHT) {};
	};
	/*!
	@brief 重力です。データの型はfloatです
	*/
	struct Gravity final : public ComponentData
	{
		static constexpr float DEFAULT = 9.8f / 60 / 60 * 32 * 3;
		float val;
		Gravity() :val(DEFAULT) {};
		explicit Gravity(const float g) :val(g) {}
	};
	/*!
	@brief  線分です。データの型は始点、終点ともにVec2です
	*/
	struct LineData final : public ComponentData
	{
		Vec2 p1;
		Vec2 p2;
		LineData() = default;
		explicit LineData(const Vec2& start, const Vec2& end) :
			p1(start),
			p2(end)
		{}
	};

	/*
	@brief Entityに重力を加えます。
	また簡易的な衝突応答処理も含まれますが、これは明示的に呼び出してください
	@details Gravity, Velocity, Positionが必要です。衝突応答を行う場合はColliderが必要です
	@TODO 現状だと1つのグループとの衝突応答しかできないのでこれを別のコンポーネントにするかもしれない
	*/
	class Physics final : public ComponentSystem
	{
	private:
		Gravity* gravity_ = nullptr;
		Velocity* velocity_ = nullptr;
		Position* pos_ = nullptr;
		std::vector<Entity*> otherEntity_{};
		std::function<bool(const Entity&, const Entity&)> collisionFunc_;
		void checkMove(Vec2& pos, Vec2& velocity)
		{
			Vec2 pointEntityMove{ velocity };
			//横軸に対する移動
			while (pointEntityMove.x != 0.f)
			{
				float preX = pos.x;

				if (pointEntityMove.x >= 1)
				{
					pos.x += 1; pointEntityMove.x -= 1;
				}
				else if (pointEntityMove.x <= -1)
				{
					pos.x -= 1; pointEntityMove.x += 1;
				}
				else
				{
					pos.x += pointEntityMove.x;
					pointEntityMove.x = 0;
				}
				for (const auto& it : otherEntity_)
				{
					if (collisionFunc_(*owner, *it))
					{
						velocity_->val.x = 0;
						pos.x = preX;		//移動をキャンセル
						break;
					}
				}

			}
			//縦軸に対する移動
			while (pointEntityMove.y != 0.f)
			{
				float preY = pos.y;
				if (pointEntityMove.y >= 1)
				{
					pos.y += 1; pointEntityMove.y -= 1;
				}
				else if (pointEntityMove.y <= -1)
				{
					pos.y -= 1; pointEntityMove.y += 1;
				}
				else
				{
					pos.y += pointEntityMove.y;
					pointEntityMove.y = 0;
				}
				for (const auto& it : otherEntity_)
				{
					if (collisionFunc_(*owner, *it))
					{
						velocity_->val.y = 0;
						pos.y = preY;		//移動をキャンセル
						break;
					}
				}
			}
		}
	public:
		void initialize() override
		{
			if (!owner->hasComponent<Gravity>())
			{
				owner->addComponent<Gravity>();
			}
			if (!owner->hasComponent<Velocity>())
			{
				owner->addComponent<Velocity>();
			}
			velocity_ = &owner->getComponent<Velocity>();
			gravity_ = &owner->getComponent<Gravity>();
			pos_ = &owner->getComponent<Position>();
		}
		void update() override
		{
			velocity_->val.y += gravity_->val;
			checkMove(pos_->val, velocity_->val);
		}
		void setVelocity(const float& x, const float& y)
		{
			velocity_->val.x = x;
			velocity_->val.y = y;
		}
		void setGravity(const float& g = Gravity::DEFAULT)
		{
			gravity_->val = g;
		}
		//!あたり判定の関数をセットする
		void setCollisionFunction(std::function<bool(const Entity&, const Entity&)> func)
		{
			collisionFunc_ = func;
		}
		//!引数に指定したEntityにめり込まないようにする
		void pushOutEntity(std::vector<Entity*>&  e)
		{
			otherEntity_ = e;
		}
	};

	/*!
	@brief PositionとRotationとScaleの親子を作ります
	@detail 親子関係を作ると生のPosition等のデータを直接変更できなくなります
	- このコンポーネントがある場合は、translate系メソッドで動かすことができます
	*/ 
	class Transform final : public ComponentSystem
	{
	private:
		Vec2 initPos_;
		Vec2 initScale_{1.f,1.f};
		Vec2 localPos_;
		Vec2 localScale_;
		float initRota_ = 0;
		float localRota_ = 0;
		Position* globalPos_ = nullptr;
		Rotation* globalRota_ = nullptr;
		Scale* globalScale_ = nullptr;
		Transform* parent_ = nullptr;
		std::vector<Transform*> childs_{};

	public:
		Transform() = default;
		Transform(const Vec2& pos):
			initPos_(pos)
		{}
		Transform(const Vec2& pos, const Vec2& scale) :
			initPos_(pos),
			initRota_(0.f),
			initScale_(scale)
		{}
		Transform(const Vec2& pos, const Vec2& scale, const float& rotation) :
			initPos_(pos),
			initRota_(rotation),
			initScale_(scale)
		{}

		void initialize() override
		{
			if (!owner->hasComponent<Position>())
			{
				owner->addComponent<Position>(initPos_);
			}
			if (!owner->hasComponent<Rotation>())
			{
				owner->addComponent<Rotation>(initRota_);
			}
			if (!owner->hasComponent<Scale>())
			{
				owner->addComponent<Scale>(initScale_);
			}
			globalPos_ = &owner->getComponent<Position>();
			globalRota_ = &owner->getComponent<Rotation>();
			globalScale_ = &owner->getComponent<Scale>();
		}

		void update() override
		{
			if (parent_ != nullptr)
			{
				globalPos_->val = parent_->globalPos_->val.offsetCopy(localPos_);
				globalRota_->val = parent_->globalRota_->val + localRota_;
				{
					const float angle = atan2(
						parent_->globalPos_->val.y - globalPos_->val.y,
						parent_->globalPos_->val.x - globalPos_->val.x);
					const float global_angle = parent_->globalRota_->val + (Math::ToDegree(angle));
					globalPos_->val.x = parent_->globalPos_->val.x + cosf(Math::ToRadian(global_angle)) * localPos_.x;
					globalPos_->val.y = parent_->globalPos_->val.y + sinf(Math::ToRadian(global_angle)) * localPos_.y;
				}
				globalScale_->val = parent_->globalScale_->val.offsetCopy(localScale_);
			}
		}

		/*このEntityに親を設定します
		@details 親のEntityにもTransformが必要です
		- 親を設定するとこのEntityは生のPosition等のデータを直接変更できなくなります
		- 親との縁を切る場合はnullptrを指定してください
		- 設定後はsetLocal系のメソッドやtranslate系のメソッドで動かしてください
		*/
		void setParent(const Entity* const pEntity)
		{	
			if (pEntity == nullptr)
			{
				parent_ = nullptr;
				return;
			}

			if (pEntity->hasComponent<Transform>())
			{
				parent_ = &pEntity->getComponent<Transform>();
				localPos_ = globalPos_->val - parent_->globalPos_->val;
				localRota_ = globalRota_->val - parent_->globalRota_->val;
				localScale_ = globalScale_->val - parent_->globalScale_->val;
				parent_->childs_.emplace_back(this);
			}
			else
			{
				DOUT << "parent has not Transform" << std::endl;
			}
		}
		/*このEntityに子を設定します
		@details 子のEntityにもTransformが必要です
		- 子を設定すると子のEntityは生のPosition等のデータを直接変更できなくなります
		- 設定後はsetLocal系のメソッドやtranslate系のメソッドで動かしてください
		*/
		void addChild(const Entity* const child)
		{
			assert(child != nullptr);
			child->getComponent<Transform>().setParent(owner);
		}
		//!指定した子を取得します
		Transform* getChild(const size_t& id)
		{
			return childs_.at(id);
		}
		/*Entityをtranslation分移動します
		@param translation 移動量
		*/
		void translatePosition(const Vec2& translation)
		{
			if (parent_)
			{
				localPos_ += translation;
			}
			else
			{
				globalPos_->val += translation;
			}
		}

		/*Entityをtranslation分回転します
		@param translation 回転量
		*/
		void translateRotation(const float& translation)
		{
			if (parent_)
			{
				localRota_ += translation;
			}
			else
			{
				globalRota_->val += translation;
			}
		}

		/*Entityをtranslation分拡大します
		@param translation 拡大量
		*/
		void translateScale(const Vec2& translation)
		{
			if (parent_)
			{
				localScale_ += translation;
			}
			else
			{
				globalScale_->val += translation;
			}
		}

		//!Entityの相対座標を設定します
		void setLocalPosition(const float& x, const float& y)
		{
			localPos_.x = x;
			localPos_.y = y;
		}
		//!Entityの相対座標を設定します
		void setLocalPosition(const Vec2& setPos)
		{
			localPos_.x = setPos.x;
			localPos_.y = setPos.y;
		}
		//!Entityの相対回転率を設定します
		void setLocalRotation(const float& r)
		{
			localRota_ = r;
		}
		//!Entityの相対拡大率を設定します
		void setLocalScale(const float& scaleX, const float& scaleY)
		{
			localScale_.x = scaleX;
			localScale_.y = scaleY;
		}
		//!Entityの相対拡大率を設定します
		void setLocalScale(const Vec2& scale)
		{
			localScale_.x = scale.x;
			localScale_.y = scale.y;
		}
	};

	/*!
	@brief コンストラクタで指定したフレーム後にEntityを殺します
	*/
	class KillEntity final : public ComponentSystem
	{
	private:
		int cnt_;
	public:
		KillEntity(const int span) :cnt_(span) {}

		void update() override
		{
			--cnt_;
			if (cnt_ <= 0)
			{
				owner->destroy();
			}
		}
		void kill()
		{
			cnt_ = 0;
		}
		void setKillLimit(const int limit)
		{
			cnt_ = limit;
		}
	};

	/*!
	@brief このコンポーネントがついているEntityにイベント(関数)を追加し,マネージャーから呼び出せるようにします
	* テンプレート引数   1戻り値,2タグとして扱う型(ただの識別子なので重複しなければなんでもよい、Defaultでvoid)
	*/
	template<class T, class Tag = void>
	class EventFunctionSystem final : public ComponentSystem
	{
	private:
		std::function<T(Entity*)> func_;
	public:
		EventFunctionSystem(std::function<T(Entity*)> addFunc) :func_(addFunc) {}

		void update() override
		{
			func_(owner);
		}
	};
}