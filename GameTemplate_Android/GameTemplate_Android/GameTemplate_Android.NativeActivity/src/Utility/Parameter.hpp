/**
* @file Parameter.hpp
* @brief あらゆる型を自由に扱えるコンテナクラスです
* -UnityのPlayerPrefsに相当するものです
* @author tonarinohito
* @date 2018/10/14
*/
#pragma once
#include <iostream>
#include <unordered_map>
#if defined(_WIN64) || defined(_WIN32)
#include <any>
//!あらゆる型を自由に扱えるコンテナクラスです
class Parameter final
{
private:
	Parameter() = delete;
	class Singleton final
	{
	private:
		std::unordered_map<std::string, std::any> map;
	public:
		/*!
		* @brief Parameterコンテナに要素の追加をします。
		* - テンプレート引数に挿入したい型を指定してください
		* @param key キー
		* @param value 挿入したい値
		*/
		template<typename ValueType>
		void add(const std::string& key, const ValueType& value)
		{
			map[key] = value;
		}
		//!引数に指定したキーのパラメータを削除します
		void remove(const std::string& key)
		{
			assert(map_.count(key) != 0 && "キーのパラメータが存在しません");
			map.erase(key);
		}
		//!すべてのパラメーターを消去します
		void clear()
		{
			map.clear();
		}
		//!指定したキーの値を取得します
		template<typename ValueType>
		[[nodiscard]] const ValueType get(const std::string& key) const
		{
			assert(map_.count(key) != 0 && "キーのパラメータが存在しません");
			return std::any_cast<ValueType>(map_.at(key));
		}
	};
public:
	inline static Singleton& Get()
	{
		static auto inst = std::make_unique<Singleton>();
		return *inst;
	}
};
#else
class Any
{
private:
	//非テンプレート基本クラス
	struct AnyBase
	{
		virtual ~AnyBase() {}
		virtual const std::type_info& type() const = 0;
		virtual AnyBase* clone() const = 0;
	};

	//テンプレート派生クラス
	template<class T>
	struct any : public AnyBase
	{
		T m_value;

		any(T value)
		{
			m_value = value;
		}

		const std::type_info& type() const
		{
			return typeid(T);
		}

		AnyBase* clone() const
		{
			return new any<T>(m_value);
		}

		virtual ~any() {}
	};

	AnyBase* obj_;

public:
	Any() : obj_(nullptr) {};
	template<class T>
	Any(const T& value)
	{
		obj_ = new any<T>(value);
	}

	Any(const Any& obj)
	{
		if (obj.obj_)
		{
			obj_ = obj.obj_->clone();
		}
		else
		{
			obj_ = 0;
		}
	}

	Any& operator=(const Any& obj)
	{
		delete obj_;
		if (obj.obj_) {
			obj_ = obj.obj_->clone();
		}
		else {
			obj_ = 0;
		}
		return *this;
	}

	template<class T>
	Any& operator=(const T& value)
	{
		delete obj_;
		obj_ = new any<T>(value);
		return *this;
	}

	template<class T>
	const T& cast() const
	{
		return dynamic_cast<any<T>&>(*obj_).m_value;
	}

	const std::type_info& type() const
	{
		return obj_->type();
	}
	~Any()
	{
		delete obj_;
	}
};

class Parameter final
{
private:
	Parameter() = delete;
	class Singleton final
	{
	private:
		std::unordered_map<std::string, Any> map_;
	public:
		/*!
		* @brief Parameterコンテナに要素の追加をします。
		* - テンプレート引数に挿入したい型を指定してください
		* @param key キー
		* @param value 挿入したい値
		*/
		template<typename ValueType>
		void add(const std::string& key, const ValueType& value)
		{
			map_[key] = value;
		}
		//!引数に指定したキーのパラメータを削除します
		void remove(const std::string& key)
		{
			assert(map_.count(key) != 0 "キーのパラメータが存在しません");
			map_.erase(key);
		}
		//!すべてのパラメーターを消去します
		void clear()
		{
			map_.clear();
		}
		//!指定したキーの値を取得します
		template<typename ValueType>
		[[nodiscard]] const ValueType& get(const std::string& key) const
		{
			assert(map_.count(key) != 0 && "キーのパラメータが存在しません");
			return map_.at(key).cast<ValueType>();
		}
	};
public:
	inline static Singleton& Get()
	{
		static auto inst = std::make_unique<Singleton>();
		return *inst;
	}
};
#endif
