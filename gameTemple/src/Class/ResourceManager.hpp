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
	@class GraphicManager
	@brief Graphic�n���h�����Ǘ����܂�
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
		* @brief  �摜�����[�h���܂�
		* @param  path �t�@�C���p�X
		* @param  name �o�^��
		* @detail ���ɓo�^�������O�͎g���܂���
		*/
		void load(const std::string& path, const std::string& a)
		{
			//���O�̏d���h�~
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
		* @brief  �摜��񓯊��Ń��[�h���܂�
		* @param  path �t�@�C���p�X
		* @param  name �o�^��
		* @detail ���ɓo�^�������O�͎g���܂���B�񓯊��Ȃ̂ł��̃��\�b�h�ŏ������~�܂邱�Ƃ͂���܂���
		*
		*/
		void loadAsync(const std::string& path, const std::string& a)
		{
			//���O�̏d���h�~
			if (graphs_.count(a))
			{
				DOUT << "GraphicHandle :" + a + " add is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // �񓯊��ǂݍ��݃t���OON
			graphs_[a] = LoadGraph(path.c_str());
			if (graphs_[a] == -1)
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

			case FALSE: return true;	//�񓯊��ǂݍ��ݍς�
			case TRUE:  return false;	//�܂�
			
			}
		}
		/**
		* @brief �����摜�����[�h���܂�
		* @param (path) �t�@�C���p�X
		* @param (name) �o�^��
		* @param (AllNum) �摜�̕�������
		* @param (XNum) �������̐�
		* @param (YNum) �c�����̐�
		* @param (XSize) ���������摜�ꖇ���̉��̃T�C�Y
		* @param (YSize) ���������摜�ꖇ���̏c�̃T�C�Y
		* @return ����������ture
		* @detail ���ɓo�^�������O�͎g���܂���
		*/
		void loadDiv(const std::string& path, const std::string& a,
			const int AllNum,
			const int XNum, const int YNum,
			const int XSize, const int YSize)
		{
			//���O�̏d���h�~
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
		* @brief  �����摜��񓯊��Ń��[�h���܂�
		* @param  path	�t�@�C���p�X
		* @param  name	�o�^��
		* @param  AllNum �摜�̕�������
		* @param  XNum   �������̐�
		* @param  YNum   �c�����̐�
		* @param  XSize  ���������摜�ꖇ���̉��̃T�C�Y
		* @param  YSize  ���������摜�ꖇ���̏c�̃T�C�Y
		* @detail ���ɓo�^�������O�͎g���܂���B�񓯊��Ȃ̂ł��̃��\�b�h�ŏ������~�܂邱�Ƃ͂���܂���
		*/
		void loadDivAsync(const std::string& path, const std::string& a,
			const int AllNum,
			const int XNum, const int YNum,
			const int XSize, const int YSize)
		{
			//���O�̏d���h�~
			if (divGraphs_.count(a))
			{
				DOUT << "GraphicHandle :" + a + " add is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // �񓯊��ǂݍ��݃t���OON
			divGraphs_[a].first = new int[AllNum];
			divGraphs_[a].second = (size_t)AllNum;
			int isOk = LoadDivGraph(path.c_str(), AllNum, XNum, YNum, XSize, YSize, divGraphs_[a].first);
			if (isOk == -1)
			{
				DOUT << path + " is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(FALSE); // �񓯊��ǂݍ��݃t���OOFF
		}
		/**
		* @brief �������ɓǂݍ��񂾉摜�̃n���h����Ԃ��܂�
		* @param (name) �o�^��
		* @return ����������n���h�����Ԃ�܂�
		* @detail ���݂��Ȃ����O�ɃA�N�Z�X����ƃG���[�ɂȂ�܂�
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
		* @brief �������ɓǂݍ��񂾕����摜�̃n���h����Ԃ��܂�
		* @param (name) �o�^��
		* @param (index) �z��̗v�f��
		* @return ����������n���h�����Ԃ�܂�
		* @detail ���݂��Ȃ����O�ɃA�N�Z�X���邩�������𒴂����l���w�肷��ƃG���[�ɂȂ�܂�
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
		* @brief �������ɓǂݍ��񂾉摜�̃n���h�������݂��邩�Ԃ��܂�
		* @param (name) �o�^��
		* @return �n���h�������݂�����true
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
		* @brief �������ɓǂݍ��񂾕����摜�̃n���h�������݂��邩�Ԃ��܂�
		* @param (name) �o�^��
		* @return �n���h�������݂�����true
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
		* @brief �������ɓǂݍ��񂾉摜���\�[�X��������܂�
		* @param (name) �o�^��
		* @return �o�^�������݂��Ȃ��ꍇ�����N���܂���
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
		* @brief �������ɓǂݍ��񂾕����摜���\�[�X��������܂�
		* @param (name) �o�^��
		* @return �o�^�������݂��Ȃ��ꍇ�����N���܂���
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
	@brief �T�E���h�n���h�����Ǘ����܂�
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
		* @brief �T�E���h�����[�h���܂�
		* @param (path) �t�@�C���p�X
		* @param (name) �o�^��
		* @detail ���ɓo�^�������O�͎g���܂���
		*/
		void load(const std::string& path, const std::string& a)
		{
			//���O�̏d���h�~
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
		* @brief  �T�E���h��񓯊��Ń��[�h���܂�
		* @param  path �t�@�C���p�X
		* @param  name �o�^��
		* @detail ���ɓo�^�������O�͎g���܂���B�񓯊��Ȃ̂ł��̃��\�b�h�ŏ������~�܂邱�Ƃ͂���܂���
		*
		*/
		void loadAsync(const std::string& path, const std::string& a)
		{
			//���O�̏d���h�~
			if (sounds_.count(a))
			{
				DOUT << "SoundHandle :" + a + " add is failed" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // �񓯊��ǂݍ��݃t���OON
			sounds_[a] = LoadSoundMem(path.c_str());
			if (sounds_[a] = -1)
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

			case FALSE: return true;	//�񓯊��ǂݍ��ݍς�
			case TRUE:  return false;	//�܂�

			}
		}
		/**
		* @brief �������ɓǂݍ��񂾃T�E���h�n���h����Ԃ��܂�
		* @param (name) �o�^��
		* @return ����������n���h�����Ԃ�܂�
		* @detail ���݂��Ȃ����O�ɃA�N�Z�X����ƃG���[�ɂȂ�܂�
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
		* @brief �������ɓǂݍ��񂾃T�E���h�n���h�������݂��邩�Ԃ��܂�
		* @param (name) �o�^��
		* @return �n���h�������݂�����true
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
		* @brief �������ɓǂݍ��񂾃T�E���h���\�[�X��������܂�
		* @param (name) �o�^��
		* @return �o�^�������݂��Ȃ��ꍇ�����N���܂���
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