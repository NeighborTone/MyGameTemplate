/**
* @file ResourceManager.hpp
* @brief DXライブラリのLoadGraphやLoadSoundMemから取得したハンドルを管理するクラスです
* @author tonarinohito
* @date 2018/10/05
*/
#pragma once
#include <DxLib.h>
#include <memory>
#include <unordered_map>
#include <string>
#include <assert.h>
#include "../Utility/Utility.hpp"

//!グラフィックやサウンドのハンドル管理をします
class ResourceManager final
{
private:
	/*!
	@class GraphicManager
	@brief Graphicハンドルを管理します
	*/
	class GraphicManager final
	{
	private:
		std::unordered_map<std::string, int> graphs_;
		std::unordered_map<std::string, std::pair<int*, size_t>> divGraphs_;
	public:
		~GraphicManager()
		{
			for (auto& it : divGraphs_)
			{
				RenderUtility::SafeDeleteArray(it.second.first);
			}
			InitGraph();
		}
		/**
		* @brief  画像をロードします
		* @param  path ファイルパス
		* @param  name 登録名
		* @detail 既に登録した名前は使えません
		*/
		void load(const std::string& path, const std::string& a)
		{
			//名前の重複防止
			if (graphs_.count(a))
			{
				DOUT << "GraphicHandle :" + a + " add is failed" << std::endl;
				assert(false);
			}
			graphs_[a] = LoadGraph(path.c_str());
			if (graphs_[a] == -1)
			{
				DOUT << path + "load is failed" << std::endl;
				assert(false);
			}
		}
		/**
		* @brief  画像を非同期でロードします
		* @param  path ファイルパス
		* @param  name 登録名
		* @detail 既に登録した名前は使えません。非同期なのでこのメソッドで処理が止まることはありません
		*
		*/
		void loadAsync(const std::string& path, const std::string& a)
		{
			//名前の重複防止
			if (graphs_.count(a))
			{
				DOUT << "GraphicHandle :" + a + " add is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // 非同期読み込みフラグON
			graphs_[a] = LoadGraph(path.c_str());
			if (graphs_[a] == -1)
			{
				DOUT << path + "load is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(FALSE); // 非同期読み込みフラグOFF
		}
		/**
		* @brief  指定したハンドルの読み込みが完了しているか返します
		* @param  name 登録名
		* @return 読み込み済みならしたらture
		*/
		[[nodiscard]] bool isLoaded(const std::string& a)
		{
			switch (CheckHandleASyncLoad(graphs_[a]))
			{
			case -1:
				if (graphs_[a] = -1)
				{
					DOUT << a + "loadAsync is failed" << std::endl;
					assert(false);
				}
				break;

			case FALSE: return true;	//非同期読み込み済み
			case TRUE:  return false;	//まだ
			
			}
		}
		/**
		* @brief 分割画像をロードします
		* @param (path) ファイルパス
		* @param (name) 登録名
		* @param (AllNum) 画像の分割総数
		* @param (XNum) 横方向の数
		* @param (YNum) 縦方向の数
		* @param (XSize) 分割した画像一枚分の横のサイズ
		* @param (YSize) 分割した画像一枚分の縦のサイズ
		* @return 成功したらture
		* @detail 既に登録した名前は使えません
		*/
		void loadDiv(const std::string& path, const std::string& a,
			const int AllNum,
			const int XNum, const int YNum,
			const int XSize, const int YSize)
		{
			//名前の重複防止
			if (divGraphs_.count(a))
			{
				DOUT << "GraphicHandle :" + a + " add is failed" << std::endl;
				assert(false);
			}
			divGraphs_[a].first = new int[AllNum];
			divGraphs_[a].second = (size_t)AllNum;
			int isOk = LoadDivGraph(path.c_str(), AllNum, XNum, YNum, XSize, YSize, divGraphs_[a].first);
			if (isOk == -1)
			{
				DOUT << path + " is failed" << std::endl;
				assert(false);
			}
		}
		/**
		* @brief  分割画像を非同期でロードします
		* @param  path	ファイルパス
		* @param  name	登録名
		* @param  AllNum 画像の分割総数
		* @param  XNum   横方向の数
		* @param  YNum   縦方向の数
		* @param  XSize  分割した画像一枚分の横のサイズ
		* @param  YSize  分割した画像一枚分の縦のサイズ
		* @detail 既に登録した名前は使えません。非同期なのでこのメソッドで処理が止まることはありません
		*/
		void loadDivAsync(const std::string& path, const std::string& a,
			const int AllNum,
			const int XNum, const int YNum,
			const int XSize, const int YSize)
		{
			//名前の重複防止
			if (divGraphs_.count(a))
			{
				DOUT << "GraphicHandle :" + a + " add is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // 非同期読み込みフラグON
			divGraphs_[a].first = new int[AllNum];
			divGraphs_[a].second = (size_t)AllNum;
			int isOk = LoadDivGraph(path.c_str(), AllNum, XNum, YNum, XSize, YSize, divGraphs_[a].first);
			if (isOk == -1)
			{
				DOUT << path + " is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(FALSE); // 非同期読み込みフラグOFF
		}
		/**
		* @brief メモリに読み込んだ画像のハンドルを返します
		* @param (name) 登録名
		* @return 成功したらハンドルが返ります
		* @detail 存在しない名前にアクセスするとエラーになります
		*/
		[[nodiscard]] int getHandle(const std::string& a)
		{
			if (graphs_.find(a) == graphs_.end())
			{
				DOUT << "Registered name :" + a + " is not found" << std::endl;
				assert(false);
			}
			return graphs_[a];
		}
		/**
		* @brief メモリに読み込んだ分割画像のハンドルを返します
		* @param (name) 登録名
		* @param (index) 配列の要素数
		* @return 成功したらハンドルが返ります
		* @detail 存在しない名前にアクセスするか分割数を超えた値を指定するとエラーになります
		*/
		[[nodiscard]] int getDivHandle(const std::string& a, const int index)
		{
			if (divGraphs_.find(a) == divGraphs_.end())
			{
				DOUT << "Registered name :" + a + " is not found" << std::endl;
				assert(false);
			}
			if ((size_t)index >= divGraphs_[a].second)
			{
				DOUT << "Registered name :" + a + " is out of range" << std::endl;
				assert(false);
			}
			return divGraphs_[a].first[index];
		}
		/**
		* @brief メモリに読み込んだ画像のハンドルが存在するか返します
		* @param (name) 登録名
		* @return ハンドルが存在したらtrue
		*/
		[[nodiscard]] bool isExistenceHandle(const std::string& a)
		{
			if (graphs_.count(a))
			{
				return true;
			}
			return false;
		}
		/**
		* @brief メモリに読み込んだ分割画像のハンドルが存在するか返します
		* @param (name) 登録名
		* @return ハンドルが存在したらtrue
		*/
		[[nodiscard]] bool isExistenceDivHandle(const std::string& a)
		{
			if (divGraphs_.count(a))
			{
				return true;
			}
			return false;
		}
		/**
		* @brief メモリに読み込んだ画像リソースを解放します
		* @param (name) 登録名
		* @return 登録名が存在しない場合何も起きません
		*/
		void removeDivGraph(const std::string& a)
		{
			if (divGraphs_.find(a) == divGraphs_.end() || !divGraphs_[a].first)
			{
				return;
			}
			DeleteGraph(*divGraphs_[a].first);
			RenderUtility::SafeDeleteArray(divGraphs_[a].first);
			divGraphs_.erase(a);
		}
		/**
		* @brief メモリに読み込んだ分割画像リソースを解放します
		* @param (name) 登録名
		* @return 登録名が存在しない場合何も起きません
		*/
		void removeGraph(const std::string& a)
		{
			if (graphs_.find(a) == graphs_.end() || !graphs_[a])
			{
				return;
			}
			DeleteGraph(graphs_[a]);
			graphs_.erase(a);
		}
	};

	/*!
	@class SoundManager
	@brief サウンドハンドルを管理します
	*/
	class SoundManager final
	{
	private:
		std::unordered_map<std::string, int> sounds_;
	public:
		~SoundManager()
		{
			InitSoundMem();
		}
		/**
		* @brief サウンドをロードします
		* @param (path) ファイルパス
		* @param (name) 登録名
		* @detail 既に登録した名前は使えません
		*/
		void load(const std::string& path, const std::string& a)
		{
			//名前の重複防止
			if (sounds_.count(a))
			{
				DOUT << "SoundHandle :" + a + " add is failed" << std::endl;
				assert(false);
			}
			sounds_[a] = LoadSoundMem(path.c_str());
			if (sounds_[a] == -1)
			{
				DOUT << path + " is failed" << std::endl;
				assert(false);
			}
		}
		/**
		* @brief  サウンドを非同期でロードします
		* @param  path ファイルパス
		* @param  name 登録名
		* @detail 既に登録した名前は使えません。非同期なのでこのメソッドで処理が止まることはありません
		*
		*/
		void loadAsync(const std::string& path, const std::string& a)
		{
			//名前の重複防止
			if (sounds_.count(a))
			{
				DOUT << "SoundHandle :" + a + " add is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // 非同期読み込みフラグON
			sounds_[a] = LoadSoundMem(path.c_str());
			if (sounds_[a] = -1)
			{
				DOUT << path + " is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(FALSE); // 非同期読み込みフラグOFF
		}
		/**
		* @brief  指定したハンドルの読み込みが完了しているか返します
		* @param  name 登録名
		* @return 読み込み済みならしたらture
		*/
		[[nodiscard]] bool isLoaded(const std::string& a)
		{
			switch (CheckHandleASyncLoad(sounds_[a]))
			{
			case -1:
				if (sounds_[a] = -1)
				{
					DOUT << a + "loadAsync is failed" << std::endl;
					assert(false);
				}
				break;

			case FALSE: return true;	//非同期読み込み済み
			case TRUE:  return false;	//まだ

			}
		}
		/**
		* @brief メモリに読み込んだサウンドハンドルを返します
		* @param (name) 登録名
		* @return 成功したらハンドルが返ります
		* @detail 存在しない名前にアクセスするとエラーになります
		*/
		[[nodiscard]] int getHandle(const std::string& a)
		{
			if (sounds_.find(a) == sounds_.end())
			{
				DOUT << "Registered name :" + a + " is not found" << std::endl;
				assert(false);
			}
			return sounds_[a];
		}
		/**
		* @brief メモリに読み込んだサウンドハンドルが存在するか返します
		* @param (name) 登録名
		* @return ハンドルが存在したらtrue
		*/
		[[nodiscard]] bool isExistenceHandle(const std::string& a)
		{
			if (sounds_.count(a))
			{
				return true;
			}
			return false;
		}
		/**
		* @brief メモリに読み込んだサウンドリソースを解放します
		* @param (name) 登録名
		* @return 登録名が存在しない場合何も起きません
		*/
		void remove(const std::string& a)
		{
			if (sounds_.find(a) == sounds_.end() || !sounds_[a])
			{
				return;
			}
			DeleteSoundMem(sounds_[a]);
			sounds_.erase(a);
		}
	};


public:
	/**
	* @brief 非同期読み込み中の処理数を返します
	* @return 非同期処理中の数
	*/
	static int GetAsyncLoadNum()
	{
		return GetASyncLoadNum();
	}
	/** @brief GraphicManagerを取得します*/
	static GraphicManager& GetGraph()
	{
		static std::unique_ptr<GraphicManager> pGraph =
			std::make_unique<GraphicManager>();
		return *pGraph;
	}
	/** @brief SoundManagerを取得します*/
	static SoundManager& GetSound()
	{
		static std::unique_ptr<SoundManager> pSound =
			std::make_unique<SoundManager>();
		return *pSound;
	}
};