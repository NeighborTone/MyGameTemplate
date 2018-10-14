/**
* @file Parameter.hpp
* @brief Scene間で渡すことのできるコンテナクラスです
* @author tonarinohito
* @date 2018/10/14
*/
#pragma once
#include <any>
#include <map>

//!あらゆる型を自由に扱えるコンテナクラスです
class Parameter final
{
public:
	Parameter() = default;
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
	//!指定したキーの値を取得します
	template<typename ValueType>
	 [[nodiscard]] const ValueType get(const std::string& key) const
	{
		auto it = map.find(key);
		assert(map.end() != it && "キーのパラメータが存在しません");
		
		return std::any_cast<ValueType>(it->second);
	}
private:
	std::map<std::string, std::any> map;
};

