/**
* @file Renderer.hpp
* @brief 描画関連のコンポーネントです。
*/
#pragma once
#include "../ECS/ECS.hpp"
#include "BasicComponents.hpp"
#include "../Collision/Collision.hpp"
#include "../Class/ResourceManager.hpp"
#include "../System/System.hpp"
#include <DxLib.h>


namespace ECS
{
	/*!
	@brief 色のデータです
	*RGBを扱います。データの型はintです
	*/
	struct Color : public ComponentData
	{
		int red, green, blue;

		Color() :
			red(255),
			green(255),
			blue(255)
		{}
		Color(const int r, const int g, const int b) :
			red(r),
			green(g),
			blue(b)
		{}
	};

	/*!
	@brief アルファブレンドに関するデータです
	*ブレンドモードとアルファ値を扱います。データの型はenum BlendStateとintです
	*/
	struct AlphaBlend : public ComponentData
	{
		//!DXライブラリのブレンドモードを簡潔にまとめたものです
		enum BlendMode
		{
			NOBLEND    = DX_BLENDMODE_NOBLEND,		//ノーブレンド（デフォルト）
			ALPHA      = DX_BLENDMODE_ALPHA,		//ブレンド
			ADD        = DX_BLENDMODE_ADD,			//加算ブレンド
			SUB        = DX_BLENDMODE_SUB,			//減算ブレンド
			MULA	   = DX_BLENDMODE_MULA,			//乗算ブレンド
			INVSRC     = DX_BLENDMODE_INVSRC,		//反転ブレンド
			PMA_ALPHA  = DX_BLENDMODE_PMA_ALPHA,	//乗算済みα用のαブレンド
			PMA_ADD    = DX_BLENDMODE_PMA_ADD,		//乗算済みα用の加算ブレンド
			PMA_SUB    = DX_BLENDMODE_PMA_SUB,		//乗算済みα用の減算ブレンド
			PMA_INVSRC = DX_BLENDMODE_PMA_INVSRC,   //乗算済みα用の反転ブレンド
		};
		BlendMode blendMode;
		int alpha;
		AlphaBlend() :
			blendMode(NOBLEND),
			alpha(255)
		{}
		AlphaBlend(const BlendMode& brend, const int alpha) :
			blendMode(brend),
			alpha(alpha)
		{}
	};

	//!Render系の処理に共通する処理をまとめたものです
	namespace RenderUtility
	{
		//!色を設定します
		void SetColor(const Color* color)
		{
			if (color != nullptr)
			{
				//RGBの設定
				SetDrawBright(color->red, color->green, color->blue);
			}
		}
		//!アルファブレンドを設定します
		void SetBlend(const AlphaBlend* blend)
		{
			if (blend != nullptr)
			{
				//ブレンドの設定
				SetDrawBlendMode(blend->blendMode, blend->alpha);
			}
		}
		//!描画の状態をもとに戻します。必ず描画終了時に呼び出してください
		void ResetRenderState()
		{
			//変更した色の情報を元に戻す
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			SetDrawBright(255, 255, 255);
		}
		//!エンティティにColorとAlphaBlendを安全に参照させます。
		void SatRenderDetail(const Entity* entity, Color** color, AlphaBlend** blend)
		{
			//色データがあれば反映する
			if (entity->hasComponent<Color>())
			{
				*color = &entity->getComponent<Color>();
			}
			//ブレンド用データがあれば反映する
			if (entity->hasComponent<AlphaBlend>())
			{
				*blend = &entity->getComponent<AlphaBlend>();
			}
		}
	}
	
	/*!
	@brief 簡易画像描画機能です.
	* - Positionが必要です。
	* - 色を変えたい場合はColorが必要です
	* - アルファブレンドをしたい場合はAlphaBlendが必要です
	*/
	class SimpleDraw final : public ComponentSystem
	{
	private:
		Position* pos_ = nullptr;
		Color* color_ = nullptr;
		AlphaBlend* blend_ = nullptr;
		std::string name_;
		bool isDraw_ = true;
	public:
		SimpleDraw(const char* name)
		{
			assert(ResourceManager::GetGraph().isExistenceHandle(name));
			name_ = name;
		}
		void initialize() override
		{
			pos_ = &entity->getComponent<Position>();
			RenderUtility::SatRenderDetail(entity, &color_, &blend_);
		}
		void draw2D() override
		{
			if (ResourceManager::GetGraph().isExistenceHandle(name_) &&
				isDraw_)
			{
				RenderUtility::SetColor(color_);
				RenderUtility::SetBlend(blend_);
				DrawGraphF(pos_->val.x, pos_->val.y, ResourceManager::GetGraph().getHandle(name_), true);
				RenderUtility::ResetRenderState();
			}
			
		}
		//! @brief 描画を有効にします
		void drawEnable()
		{
			isDraw_ = true;
		}
		//! @brief 描画を無効にします
		void drawDisable()
		{
			isDraw_ = false;
		}
	};
	/*!
	@class RectDraw
	@brief 指定した範囲を描画する機能です。
	@note  Positionが必要です
	*/
	class RectDraw final : public ComponentSystem
	{
	private:
		Position* pos_ = nullptr;
		Color* color_ = nullptr;
		AlphaBlend* blend_ = nullptr;
		RECT rect;
		std::string name_;
		bool isDraw_ = true;
	public:
		RectDraw(const char* name, const int srcX, const int srcY, const int w, const int h)
		{
			assert(ResourceManager::GetGraph().isExistenceHandle(name));
			rect.left = srcX;
			rect.right = srcY;
			rect.bottom = w;
			rect.top = h;
			name_ = name;
		}
		void initialize() override
		{
			pos_ = &entity->getComponent<Position>();
			RenderUtility::SatRenderDetail(entity, &color_, &blend_);
		}
		void draw2D() override
		{
			if (ResourceManager::GetGraph().isExistenceHandle(name_) &&
				isDraw_)
			{
				RenderUtility::SetColor(color_);
				RenderUtility::SetBlend(blend_);
				DrawRectGraphF(
					pos_->val.x, pos_->val.y,
					rect.left, rect.right,
					rect.bottom,
					rect.top,
					ResourceManager::GetGraph().getHandle(name_),
					true);
				RenderUtility::ResetRenderState();
			}
		}
		//! @brief 描画を有効にします
		void drawEnable()
		{
			isDraw_ = true;
		}
		//! @brief 描画を無効にします
		void drawDisable()
		{
			isDraw_ = false;
		}
	};

	/*!
	@class AnimationDraw
	@brief 分割画像を描画する機能です。
	@note  PositionとDirectionが必要です、また向きによって反転します
	*/
	class AnimationDraw final : public ComponentSystem
	{
	private:
		Position* pos_ = nullptr;
		Direction* dir = nullptr;
		AlphaBlend* blend_ = nullptr;
		Color* color_ = nullptr;
		std::string name_;
		int index = 0;
		bool isTurn = false;
		bool isDraw_ = true;
	public:
		AnimationDraw(const char* name)
		{
			assert(ResourceManager::GetGraph().isExistenceDivHandle(name));
			name_ = name;
		}
		void initialize() override
		{
			if (entity->hasComponent<Direction>())
			{
				dir = &entity->getComponent<Direction>();
			}
			pos_ = &entity->getComponent<Position>();
			RenderUtility::SatRenderDetail(entity, &color_, &blend_);
		}
		void update() override
		{
			if (dir->val == Direction::Dir::R)
			{
				isTurn = false;
			}
			if (dir->val == Direction::Dir::L)
			{
				isTurn = true;
			}
		}
		void draw2D() override
		{
			if (ResourceManager::GetGraph().isExistenceDivHandle(name_) &&
				isDraw_)
			{
				RenderUtility::SetColor(color_);
				RenderUtility::SetBlend(blend_);
				if (!isTurn)
				{
					DrawGraphF(pos_->val.x, pos_->val.y, ResourceManager::GetGraph().getDivHandle(name_, index), true);
				}
				else
				{
					DrawTurnGraphF(pos_->val.x, pos_->val.y, ResourceManager::GetGraph().getDivHandle(name_, index), true);
				}
				RenderUtility::ResetRenderState();
			}
		}
		//! @brief 描画したい分割画像の要素番号を指定します
		void setIndex(const int index_)
		{
			index = index_;
		}
		//! @brief 描画を有効にします
		void drawEnable()
		{
			isDraw_ = true;
		}
		//! @brief 描画を無効にします
		void drawDisable()
		{
			isDraw_ = false;
		}

	};
}