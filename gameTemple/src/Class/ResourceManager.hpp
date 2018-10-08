/**
* @file ResourceManager.hpp
* @brief DX���C�u������LoadGraph��LoadSoundMem����擾�����n���h�����Ǘ�����N���X�ł�
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

//!�O���t�B�b�N��T�E���h�̃n���h���Ǘ������܂�
class ResourceManager final
{
private:
	/*!
	@brief Graphic�n���h�����Ǘ����܂�
	*/
	class GraphicManager final
	{
	private:
		typedef std::unordered_map<std::string, int> GraphMap;
		typedef std::unordered_map<std::string, std::pair<int*, size_t>> DivGraphMap;
		GraphMap graphs_;
		DivGraphMap divGraphs_;
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
		* @brief  �摜�����[�h���܂�
		* @param  path �t�@�C���p�X
		* @param  name �o�^��
		* @detail ���ɓo�^�������O�͎g���܂���
		*/
		void load(const std::string& path, const std::string& name)
		{
			//���O�̏d���h�~
			if (graphs_.count(name))
			{
				DOUT << "GraphicHandle :" + name + " add is failed" << std::endl;
				assert(false);
			}
			graphs_[name] = LoadGraph(path.c_str());
			if (graphs_[name] == -1)
			{
				DOUT << path + "load is failed" << std::endl;
				assert(false);
			}
		}
		/**
		* @brief  �摜��񓯊��Ń��[�h���܂�
		* @param  path �t�@�C���p�X
		* @param  name �o�^��
		* @detail ���ɓo�^�������O�͎g���܂���B�񓯊��Ȃ̂ł��̃��\�b�h�ŏ������~�܂邱�Ƃ͂���܂���
		*
		*/
		void loadAsync(const std::string& path, const std::string& name)
		{
			//���O�̏d���h�~
			if (graphs_.count(name))
			{
				DOUT << "GraphicHandle :" + name + " add is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // �񓯊��ǂݍ��݃t���OON
			graphs_[name] = LoadGraph(path.c_str());
			if (graphs_[name] == -1)
			{
				DOUT << path + "load is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(FALSE); // �񓯊��ǂݍ��݃t���OOFF
		}
		/**
		* @brief  �w�肵���n���h���̓ǂݍ��݂��������Ă��邩�Ԃ��܂�
		* @param  name �o�^��
		* @return �ǂݍ��ݍς݂Ȃ炵����ture
		*/
		[[nodiscard]] bool isLoaded(const std::string& name)
		{
			switch (CheckHandleASyncLoad(graphs_[name]))
			{
			case -1:
				if (graphs_[name] = -1)
				{
					DOUT << name + "loadAsync is failed" << std::endl;
					assert(false);
				}
				break;

			case FALSE: return true;	//�񓯊��ǂݍ��ݍς�
			case TRUE:  return false;	//�܂�
			
			}
		}
		/**
		* @brief  �w�肵���n���h���̓ǂݍ��݂��������Ă��邩�Ԃ��܂�
		* @param  name �o�^��
		* @return �ǂݍ��ݍς݂Ȃ炵����ture
		*/
		[[nodiscard]] bool isLoadedDiv(const std::string& name)
		{
			switch (CheckHandleASyncLoad(*divGraphs_[name].first))
			{
			case -1:
				if (*divGraphs_[name].first = -1)
				{
					DOUT << name + "loadAsync is failed" << std::endl;
					assert(false);
				}
				break;

			case FALSE: return true;	//�񓯊��ǂݍ��ݍς�
			case TRUE:  return false;	//�܂�

			}
		}
		/**
		* @brief  �����摜�����[�h���܂�
		* @param  path �t�@�C���p�X
		* @param  name �o�^��
		* @param  allNum �摜�̕�������
		* @param  xNum �������̐�
		* @param  yNum �c�����̐�
		* @param  xSize ���������摜�ꖇ���̉��̃T�C�Y
		* @param  ySize ���������摜�ꖇ���̏c�̃T�C�Y
		* @return ����������ture
		* @detail ���ɓo�^�������O�͎g���܂���
		*/
		void loadDiv(const std::string& path, const std::string& name,
			const int allNum,
			const int xNum, const int yNum,
			const int xSize, const int ySize)
		{
			//���O�̏d���h�~
			if (divGraphs_.count(name))
			{
				DOUT << "GraphicHandle :" + name + " add is failed" << std::endl;
				assert(false);
			}
			divGraphs_[name].first = new int[allNum];
			divGraphs_[name].second = (size_t)allNum;
			int isOk = LoadDivGraph(path.c_str(), allNum, xNum, yNum, xSize, ySize, divGraphs_[name].first);
			if (isOk == -1)
			{
				DOUT << path + " is failed" << std::endl;
				assert(false);
			}
		}
		/**
		* @brief  �����摜��񓯊��Ń��[�h���܂�
		* @param  path	�t�@�C���p�X
		* @param  name	�o�^��
		* @param  allNum �摜�̕�������
		* @param  xNum �������̐�
		* @param  yNum �c�����̐�
		* @param  xSize ���������摜�ꖇ���̉��̃T�C�Y
		* @param  ySize ���������摜�ꖇ���̏c�̃T�C�Y
		* @detail ���ɓo�^�������O�͎g���܂���B�񓯊��Ȃ̂ł��̃��\�b�h�ŏ������~�܂邱�Ƃ͂���܂���
		*/
		void loadDivAsync(const std::string& path, const std::string& name,
			const int allNum,
			const int xNum, const int yNum,
			const int xSize, const int ySize)
		{
			//���O�̏d���h�~
			if (divGraphs_.count(name))
			{
				DOUT << "GraphicHandle :" + name + " add is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // �񓯊��ǂݍ��݃t���OON
			divGraphs_[name].first = new int[allNum];
			divGraphs_[name].second = (size_t)allNum;
			int isOk = LoadDivGraph(path.c_str(), allNum, xNum, yNum, xSize, ySize, divGraphs_[name].first);
			if (isOk == -1)
			{
				DOUT << path + " is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(FALSE); // �񓯊��ǂݍ��݃t���OOFF
		}
		/**
		* @brief  �������ɓǂݍ��񂾉摜�̃n���h����Ԃ��܂�
		* @param  name �o�^��
		* @return ����������n���h�����Ԃ�܂�
		* @detail ���݂��Ȃ����O�ɃA�N�Z�X����ƃG���[�ɂȂ�܂�
		*/
		[[nodiscard]] int getHandle(const std::string& name)
		{
			if (graphs_.find(name) == graphs_.end())
			{
				DOUT << "Registered name :" + name + " is not found" << std::endl;
				assert(false);
			}
			return graphs_[name];
		}
		/**
		* @brief  �������ɓǂݍ��񂾕����摜�̃n���h����Ԃ��܂�
		* @param  name �o�^��
		* @param  index �z��̗v�f��
		* @return ����������n���h�����Ԃ�܂�
		* @detail ���݂��Ȃ����O�ɃA�N�Z�X���邩�������𒴂����l���w�肷��ƃG���[�ɂȂ�܂�
		*/
		[[nodiscard]] int getDivHandle(const std::string& name, const int index)
		{
			if (divGraphs_.find(name) == divGraphs_.end())
			{
				DOUT << "Registered name :" + name + " is not found" << std::endl;
				assert(false);
			}
			if ((size_t)index >= divGraphs_[name].second)
			{
				DOUT << "Registered name :" + name + " is out of range" << std::endl;
				assert(false);
			}
			return divGraphs_[name].first[index];
		}
		/**
		* @brief  �������ɓǂݍ��񂾉摜�̃n���h�������݂��邩�Ԃ��܂�
		* @param  name �o�^��
		* @return �n���h�������݂�����true
		*/
		[[nodiscard]] bool hasHandle(const std::string& name)
		{
			if (graphs_.count(name))
			{
				return true;
			}
			return false;
		}
		/**
		* @brief  �������ɓǂݍ��񂾕����摜�̃n���h�������݂��邩�Ԃ��܂�
		* @param  name �o�^��
		* @return �n���h�������݂�����true
		*/
		[[nodiscard]] bool hasDivHandle(const std::string& name)
		{
			if (divGraphs_.count(name))
			{
				return true;
			}
			return false;
		}
		/**
		* @brief  �������ɓǂݍ��񂾉摜���\�[�X��������܂�
		* @param  name �o�^��
		* @return �o�^�������݂��Ȃ��ꍇ�����N���܂���
		*/
		void removeDivGraph(const std::string& name)
		{
			if (divGraphs_.find(name) == divGraphs_.end() || !divGraphs_[name].first)
			{
				DOUT << "Registered name :" + name + " is remove failed" << std::endl;
				return;
			}
			DeleteGraph(*divGraphs_[name].first);
			Utility::SafeDeleteArray(divGraphs_[name].first);
			divGraphs_.erase(name);
		}
		/**
		* @brief  �������ɓǂݍ��񂾕����摜���\�[�X��������܂�
		* @param  name �o�^��
		* @return �o�^�������݂��Ȃ��ꍇ�����N���܂���
		*/
		void removeGraph(const std::string& name)
		{
			if (graphs_.find(name) == graphs_.end() || !graphs_[name])
			{
				DOUT << "Registered name :" + name + " is remove failed" << std::endl;
				return;
			}
			DeleteGraph(graphs_[name]);
			graphs_.erase(name);
		}
	};

	/*!
	@class SoundManager
	@brief �T�E���h�n���h�����Ǘ����܂�
	*/
	class SoundManager final
	{
	private:
		typedef std::unordered_map<std::string, int> SoundMap;
		SoundMap sounds_;
	public:
		~SoundManager()
		{
			InitSoundMem();
		}
		/**
		* @brief �T�E���h�����[�h���܂�
		* @param  path �t�@�C���p�X
		* @param  name �o�^��
		* @detail ���ɓo�^�������O�͎g���܂���
		*/
		void load(const std::string& path, const std::string& name)
		{
			//���O�̏d���h�~
			if (sounds_.count(name))
			{
				DOUT << "SoundHandle :" + name + " add is failed" << std::endl;
				assert(false);
			}
			sounds_[name] = LoadSoundMem(path.c_str());
			if (sounds_[name] == -1)
			{
				DOUT << path + " is failed" << std::endl;
				assert(false);
			}
		}
		/**
		* @brief  �T�E���h��񓯊��Ń��[�h���܂�
		* @param  path �t�@�C���p�X
		* @param  name �o�^��
		* @detail ���ɓo�^�������O�͎g���܂���B�񓯊��Ȃ̂ł��̃��\�b�h�ŏ������~�܂邱�Ƃ͂���܂���
		*
		*/
		void loadAsync(const std::string& path, const std::string& name)
		{
			//���O�̏d���h�~
			if (sounds_.count(name))
			{
				DOUT << "SoundHandle :" + name + " add is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // �񓯊��ǂݍ��݃t���OON
			sounds_[name] = LoadSoundMem(path.c_str());
			if (sounds_[name] = -1)
			{
				DOUT << path + " is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(FALSE); // �񓯊��ǂݍ��݃t���OOFF
		}
		/**
		* @brief  �w�肵���n���h���̓ǂݍ��݂��������Ă��邩�Ԃ��܂�
		* @param  name �o�^��
		* @return �ǂݍ��ݍς݂Ȃ炵����ture
		*/
		[[nodiscard]] bool isLoaded(const std::string& name)
		{
			switch (CheckHandleASyncLoad(sounds_[name]))
			{
			case -1:
				if (sounds_[name] = -1)
				{
					DOUT << name + "loadAsync is failed" << std::endl;
					assert(false);
				}
				break;

			case FALSE: return true;	//�񓯊��ǂݍ��ݍς�
			case TRUE:  return false;	//�܂�

			}
		}
		/**
		* @brief  �������ɓǂݍ��񂾃T�E���h�n���h����Ԃ��܂�
		* @param  name �o�^��
		* @return ����������n���h�����Ԃ�܂�
		* @detail ���݂��Ȃ����O�ɃA�N�Z�X����ƃG���[�ɂȂ�܂�
		*/
		[[nodiscard]] int getHandle(const std::string& name)
		{
			if (sounds_.find(name) == sounds_.end())
			{
				DOUT << "Registered name :" + name + " is not found" << std::endl;
				assert(false);
			}
			return sounds_[name];
		}
		/**
		* @brief �������ɓǂݍ��񂾃T�E���h�n���h�������݂��邩�Ԃ��܂�
		* @param name �o�^��
		* @return �n���h�������݂�����true
		*/
		[[nodiscard]] bool hasHandle(const std::string& name)
		{
			if (sounds_.count(name))
			{
				return true;
			}
			return false;
		}
		/**
		* @brief �������ɓǂݍ��񂾃T�E���h���\�[�X��������܂�
		* @param name �o�^��
		* @return �o�^�������݂��Ȃ��ꍇ�����N���܂���
		*/
		void remove(const std::string& name)
		{
			if (sounds_.find(name) == sounds_.end() || !sounds_[name])
			{
				DOUT << "Registered name :" + name + " is remove failed" << std::endl;
				return;
			}
			DeleteSoundMem(sounds_[name]);
			sounds_.erase(name);
		}
		//!���ׂẴn���h����unordered_map�ŕԂ��܂�
		[[nodiscard]] const SoundMap& getSoundMap() const
		{
			return sounds_;
		}
	};


public:
	/**
	* @brief �񓯊��ǂݍ��ݒ��̏�������Ԃ��܂�
	* @return �񓯊��������̐�
	*/
	static int GetAsyncLoadNum()
	{
		return GetASyncLoadNum();
	}
	/** @brief GraphicManager���擾���܂�*/
	static GraphicManager& GetGraph()
	{
		static std::unique_ptr<GraphicManager> pGraph =
			std::make_unique<GraphicManager>();
		return *pGraph;
	}
	/** @brief SoundManager���擾���܂�*/
	static SoundManager& GetSound()
	{
		static std::unique_ptr<SoundManager> pSound =
			std::make_unique<SoundManager>();
		return *pSound;
	}
};