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
				Utility::SafeDeleteArray(it.second.first);
			}
			InitGraph();
		}
		/**
		* @brief  画像をロードします
		* @param  path ファイルパス
		* @param  name 登録名
		* @detail 既に登録した名前は使えません
		*/
		void load(const std::string& path, const std::string& name)
		{
			//名前の重複防止
			if (graphs_.count(name))
			{
				DOUT << "グラフィックハンドル" + name + "はもう登録されています" << std::endl;
				assert(false);
			}
			graphs_[name] = LoadGraph(path.c_str());
			if (graphs_[name] == -1)
			{
				DOUT << path + "の読み込みに失敗しました" << std::endl;
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
		void loadAsync(const std::string& path, const std::string& name)
		{
			//名前の重複防止
			if (graphs_.count(name))
			{
				DOUT << "グラフィックハンドル" + name + "はもう登録されています" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // 非同期読み込みフラグON
			graphs_[name] = LoadGraph(path.c_str());
			if (graphs_[name] == -1)
			{
				DOUT << path + "の読み込みに失敗しました" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(FALSE); // 非同期読み込みフラグOFF
		}
		/**
		* @brief  指定したハンドルの読み込みが完了しているか返します
		* @param  name 登録名
		* @return 読み込み済みならしたらture
		*/
		[[nodiscard]] bool isLoaded(const std::string& name)
		{
			switch (CheckHandleASyncLoad(graphs_[name]))
			{
			case -1:
				if (graphs_[name] = -1)
				{
					DOUT << name + "の非同期読み込みに失敗しています" << std::endl;
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
		void loadDiv(const std::string& path, const std::string& name,
			const int AllNum,
			const int XNum, const int YNum,
			const int XSize, const int YSize)
		{
			//名前の重複防止
			if (divGraphs_.count(name))
			{
				DOUT << "グラフィックハンドル" + name + "はもう登録されています" << std::endl;
				assert(false);
			}
			divGraphs_[name].first = new int[AllNum];
			divGraphs_[name].second = (size_t)AllNum;
			int isOk = LoadDivGraph(path.c_str(), AllNum, XNum, YNum, XSize, YSize, divGraphs_[name].first);
			if (isOk == -1)
			{
				DOUT << path + "の読み込みに失敗しました" << std::endl;
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
		void loadDivAsync(const std::string& path, const std::string& name,
			const int AllNum,
			const int XNum, const int YNum,
			const int XSize, const int YSize)
		{
			//名前の重複防止
			if (divGraphs_.count(name))
			{
				DOUT << "グラフィックハンドル" + name + "はもう登録されています" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // 非同期読み込みフラグON
			divGraphs_[name].first = new int[AllNum];
			divGraphs_[name].second = (size_t)AllNum;
			int isOk = LoadDivGraph(path.c_str(), AllNum, XNum, YNum, XSize, YSize, divGraphs_[name].first);
			if (isOk == -1)
			{
				DOUT << path + "の読み込みに失敗しました" << std::endl;
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
		[[nodiscard]] int getHandle(const std::string& name)
		{
			if (graphs_.find(name) == graphs_.end())
			{
				DOUT << "登録名" + name + "のグラフィックハンドルは存在しません" << std::endl;
				assert(false);
			}
			return graphs_[name];
		}
		/**
		* @brief メモリに読み込んだ分割画像のハンドルを返します
		* @param (name) 登録名
		* @param (index) 配列の要素数
		* @return 成功したらハンドルが返ります
		* @detail 存在しない名前にアクセスするか分割数を超えた値を指定するとエラーになります
		*/
		[[nodiscard]] int getDivHandle(const std::string& name, const int index)
		{
			if (divGraphs_.find(name) == divGraphs_.end())
			{
				DOUT << "登録名" + name + "のグラフィックハンドルは存在しません" << std::endl;
				assert(false);
			}
			if ((size_t)index >= divGraphs_[name].second)
			{
				DOUT << "登録名" + name + "の分割数を超えた値です" << std::endl;
				assert(false);
			}
			return divGraphs_[name].first[index];
		}
		/**
		* @brief メモリに読み込んだ画像のハンドルが存在するか返します
		* @param (name) 登録名
		* @return ハンドルが存在したらtrue
		*/
		[[nodiscard]] bool isExistenceHandle(const std::string& name)
		{
			if (graphs_.count(name))
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
		[[nodiscard]] bool isExistenceDivHandle(const std::string& name)
		{
			if (divGraphs_.count(name))
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
		void removeDivGraph(const std::string& name)
		{
			if (divGraphs_.find(name) == divGraphs_.end() || !divGraphs_[name].first)
			{
				return;
			}
			DeleteGraph(*divGraphs_[name].first);
			Utility::SafeDeleteArray(divGraphs_[name].first);
			divGraphs_.erase(name);
		}
		/**
		* @brief メモリに読み込んだ分割画像リソースを解放します
		* @param (name) 登録名
		* @return 登録名が存在しない場合何も起きません
		*/
		void removeGraph(const std::string& name)
		{
			if (graphs_.find(name) == graphs_.end() || !graphs_[name])
			{
				return;
			}
			DeleteGraph(graphs_[name]);
			graphs_.erase(name);
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
		void load(const std::string& path, const std::string& name)
		{
			//名前の重複防止
			if (sounds_.count(name))
			{
				DOUT << "サウンドハンドル" + name + "はもう登録されています" << std::endl;
				assert(false);
			}
			sounds_[name] = LoadSoundMem(path.c_str());
			if (sounds_[name] == -1)
			{
				DOUT << path + "の読み込みに失敗しました" << std::endl;
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
		void loadAsync(const std::string& path, const std::string& name)
		{
			//名前の重複防止
			if (sounds_.count(name))
			{
				DOUT << "サウンドハンドル" + name + "はもう登録されています" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // 非同期読み込みフラグON
			sounds_[name] = LoadSoundMem(path.c_str());
			if (sounds_[name] = -1)
			{
				DOUT << path + "の読み込みに失敗しました" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(FALSE); // 非同期読み込みフラグOFF
		}
		/**
		* @brief  指定したハンドルの読み込みが完了しているか返します
		* @param  name 登録名
		* @return 読み込み済みならしたらture
		*/
		[[nodiscard]] bool isLoaded(const std::string& name)
		{
			switch (CheckHandleASyncLoad(sounds_[name]))
			{
			case -1:
				if (sounds_[name] = -1)
				{
					DOUT << name + "の非同期読み込みに失敗しています" << std::endl;
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
		[[nodiscard]] int getHandle(const std::string& name)
		{
			if (sounds_.find(name) == sounds_.end())
			{
				DOUT << "登録名" + name + "のサウンドハンドルは存在しません" << std::endl;
				assert(false);
			}
			return sounds_[name];
		}
		/**
		* @brief メモリに読み込んだサウンドハンドルが存在するか返します
		* @param (name) 登録名
		* @return ハンドルが存在したらtrue
		*/
		[[nodiscard]] bool isExistenceHandle(const std::string& name)
		{
			if (sounds_.count(name))
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
		void remove(const std::string& name)
		{
			if (sounds_.find(name) == sounds_.end() || !sounds_[name])
			{
				return;
			}
			DeleteSoundMem(sounds_[name]);
			sounds_.erase(name);
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