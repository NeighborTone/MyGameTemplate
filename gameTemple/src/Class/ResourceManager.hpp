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
//SetUseASyncLoadFlag( TRUE ); // �񓯊��ǂݍ��݃t���OON
//int a = LoadGraph("a.png"); // �񓯊��ǂݍ��ݏI���܂ł͖����ȃn���h�����Ԃ�
//SetUseASyncLoadFlag(FALSE); // �񓯊��ǂݍ��݃t���OOFF
//int b = LoadGraph("b.png"); // �����ǂݍ��݂Ȃ̂ŗL���ȃn���h�����Ԃ�


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
				DOUT << "�O���t�B�b�N�n���h��" + name + "�͂����o�^����Ă��܂�" << std::endl;
				assert(false);
			}
			graphs_[name] = LoadGraph(path.c_str());
			if (graphs_[name] == -1)
			{
				DOUT << path + "�̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
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
				DOUT << "�O���t�B�b�N�n���h��" + name + "�͂����o�^����Ă��܂�" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // �񓯊��ǂݍ��݃t���OON
			graphs_[name] = LoadGraph(path.c_str());
			if (graphs_[name] == -1)
			{
				DOUT << path + "�̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
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
					DOUT << name + "�̔񓯊��ǂݍ��݂Ɏ��s���Ă��܂�" << std::endl;
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
		void loadDiv(const std::string& path, const std::string& name,
			const int AllNum,
			const int XNum, const int YNum,
			const int XSize, const int YSize)
		{
			//���O�̏d���h�~
			if (divGraphs_.count(name))
			{
				DOUT << "�O���t�B�b�N�n���h��" + name + "�͂����o�^����Ă��܂�" << std::endl;
				assert(false);
			}
			divGraphs_[name].first = new int[AllNum];
			divGraphs_[name].second = (size_t)AllNum;
			int isOk = LoadDivGraph(path.c_str(), AllNum, XNum, YNum, XSize, YSize, divGraphs_[name].first);
			if (isOk == -1)
			{
				DOUT << path + "�̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
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
		void loadDivAsync(const std::string& path, const std::string& name,
			const int AllNum,
			const int XNum, const int YNum,
			const int XSize, const int YSize)
		{
			//���O�̏d���h�~
			if (divGraphs_.count(name))
			{
				DOUT << "�O���t�B�b�N�n���h��" + name + "�͂����o�^����Ă��܂�" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // �񓯊��ǂݍ��݃t���OON
			divGraphs_[name].first = new int[AllNum];
			divGraphs_[name].second = (size_t)AllNum;
			int isOk = LoadDivGraph(path.c_str(), AllNum, XNum, YNum, XSize, YSize, divGraphs_[name].first);
			if (isOk == -1)
			{
				DOUT << path + "�̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
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
		[[nodiscard]] int getHandle(const std::string& name)
		{
			if (graphs_.find(name) == graphs_.end())
			{
				DOUT << "�o�^��" + name + "�̃O���t�B�b�N�n���h���͑��݂��܂���" << std::endl;
				assert(false);
			}
			return graphs_[name];
		}
		/**
		* @brief �������ɓǂݍ��񂾕����摜�̃n���h����Ԃ��܂�
		* @param (name) �o�^��
		* @param (index) �z��̗v�f��
		* @return ����������n���h�����Ԃ�܂�
		* @detail ���݂��Ȃ����O�ɃA�N�Z�X���邩�������𒴂����l���w�肷��ƃG���[�ɂȂ�܂�
		*/
		[[nodiscard]] int getDivHandle(const std::string& name, const int index)
		{
			if (divGraphs_.find(name) == divGraphs_.end())
			{
				DOUT << "�o�^��" + name + "�̃O���t�B�b�N�n���h���͑��݂��܂���" << std::endl;
				assert(false);
			}
			if ((size_t)index >= divGraphs_[name].second)
			{
				DOUT << "�o�^��" + name + "�̕������𒴂����l�ł�" << std::endl;
				assert(false);
			}
			return divGraphs_[name].first[index];
		}
		/**
		* @brief �������ɓǂݍ��񂾉摜�̃n���h�������݂��邩�Ԃ��܂�
		* @param (name) �o�^��
		* @return �n���h�������݂�����true
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
		* @brief �������ɓǂݍ��񂾕����摜�̃n���h�������݂��邩�Ԃ��܂�
		* @param (name) �o�^��
		* @return �n���h�������݂�����true
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
		* @brief �������ɓǂݍ��񂾉摜���\�[�X��������܂�
		* @param (name) �o�^��
		* @return �o�^�������݂��Ȃ��ꍇ�����N���܂���
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
		* @brief �������ɓǂݍ��񂾕����摜���\�[�X��������܂�
		* @param (name) �o�^��
		* @return �o�^�������݂��Ȃ��ꍇ�����N���܂���
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
		void load(const std::string& path, const std::string& name)
		{
			//���O�̏d���h�~
			if (sounds_.count(name))
			{
				DOUT << "�T�E���h�n���h��" + name + "�͂����o�^����Ă��܂�" << std::endl;
				assert(false);
			}
			sounds_[name] = LoadSoundMem(path.c_str());
			if (sounds_[name] == -1)
			{
				DOUT << path + "�̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
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
				DOUT << "�T�E���h�n���h��" + name + "�͂����o�^����Ă��܂�" << std::endl;
				assert(false);
			}
			SetUseASyncLoadFlag(TRUE); // �񓯊��ǂݍ��݃t���OON
			sounds_[name] = LoadSoundMem(path.c_str());
			if (sounds_[name] = -1)
			{
				DOUT << path + "�̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
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
					DOUT << name + "�̔񓯊��ǂݍ��݂Ɏ��s���Ă��܂�" << std::endl;
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
		[[nodiscard]] int getHandle(const std::string& name)
		{
			if (sounds_.find(name) == sounds_.end())
			{
				DOUT << "�o�^��" + name + "�̃T�E���h�n���h���͑��݂��܂���" << std::endl;
				assert(false);
			}
			return sounds_[name];
		}
		/**
		* @brief �������ɓǂݍ��񂾃T�E���h�n���h�������݂��邩�Ԃ��܂�
		* @param (name) �o�^��
		* @return �n���h�������݂�����true
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
		* @brief �������ɓǂݍ��񂾃T�E���h���\�[�X��������܂�
		* @param (name) �o�^��
		* @return �o�^�������݂��Ȃ��ꍇ�����N���܂���
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