/**
* @file Vec.hpp
* @brief ベクトルを扱うクラスです
* @author tonarinohito
* @date 2018/5/11
* @par History
- 2018/08/20 tonarinohito
-# 適切にconstをつけた
- 2018/10/04 tonarinohito
-# 静的でないメソッド名をキャメルケースに変更
- 2018/10/07 tonarinohito
-# TVecからVec_Tにリネーム
-# テンプレートコンストラクタ追加
*/
#pragma once

/**
*   @brief 2次元ベクトルを扱います
*/
template <class T> class Vec2_T
{
public:
	T x, y;
	Vec2_T() :
		x(0),
		y(0)
	{};

	template<class U>
	Vec2_T(const Vec2_T<U>& v)
	{
		x = v.x;
		y = v.y;
	}
	Vec2_T(const T setX, const T setY)
	{
		x = setX;
		y = setY;
	};
	Vec2_T(const Vec2_T& v)
	{
		x = v.x;
		y = v.y;
	}
	~Vec2_T() {};
	/*!
	* @brief オフセット値を返します
	* @return Vec2
	*/
	[[nodiscard]] const Vec2_T offSetCopy(const T setX, const T setY) const
	{
		Vec2_T ret(*this);
		ret.x += setX;
		ret.y += setY;
		return ret;
	}
	//! @brief すべてのパラメーターを0にします
	void zero()
	{
		x = 0;
		y = 0;
	}

	/*!
	* @brief 内積を返します
	* @return 内積
	*/
	[[nodiscard]] const T dot(const Vec2_T& v) const
	{
		return x * v.x + y * v.y;
	}

	/*!
	* @brief 外積を返します
	* @return 外積
	*/
	[[nodiscard]] const T cross(const Vec2_T& v) const
	{
		return x * v.y - v.x * y;
	}

	/*!
	* @brief 内積を返します
	* @return 内積
	*/
	[[nodiscard]] static T Dot(const Vec2_T& v1, const Vec2_T& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	/*!
	* @brief 外積を返します
	* @return 外積
	*/
	[[nodiscard]] static T Cross(const Vec2_T& v1, const Vec2_T& v2)
	{
		return v1.x * v2.y - v2.x * v1.y;
	}
	/*!
	* @brief 2点間の距離を返します
	* @return 距離
	*/
	[[nodiscard]] const T getDistance(const Vec2_T& v) const
	{
		const T dx = x - v.x;
		const T dy = y - v.y;

		return hypot(dx, dy);
	}

	/*!
	* @brief 長さを返します
	* @return 長さ
	*/
	[[nodiscard]] const T length() const
	{
		return sqrtf(x * x + y * y);
	}
	/*!
	* @brief 自分自身を正規化した値を返します
	* @return Vec2
	*/
	[[nodiscard]] const Vec2_T&  normalize()
	{
		T tmp = length();
		x /= tmp;
		y /= tmp;
		return *this;
	}
	/*!
	* @brief 自分自身を正規化した値のコピーを返します。自身の値は変わりません
	* @return Vec2
	*/
	[[nodiscard]] const Vec2_T&  getNormalize() const
	{
		Vec2_T result = *this;
		result.normalize();
		return result;
	}

	Vec2_T operator+() const
	{
		return Vec2_T(*this);
	}

	Vec2_T operator-() const
	{
		return Vec2_T(-x, -y);
	}

	Vec2_T operator+(const Vec2_T& v) const
	{
		Vec2_T ret(*this);
		ret += v;
		return ret;
	}

	Vec2_T operator+(const T& t)
	{
		Vec2_T ret(*this);
		ret += t;
		return ret;
	}

	Vec2_T operator-(const Vec2_T& v) const
	{
		Vec2_T ret(*this);
		ret -= v;
		return ret;
	}

	Vec2_T operator-(const T& t)
	{
		Vec2_T ret(*this);
		ret -= t;
		return ret;
	}

	Vec2_T operator*(const Vec2_T& v)
	{
		Vec2_T ret(*this);
		ret *= v;
		return ret;
	}

	Vec2_T operator*(const T& t)
	{
		Vec2_T ret(*this);
		ret *= t;
		return ret;
	}

	Vec2_T operator/(const Vec2_T& v)
	{
		Vec2_T ret(*this);
		ret /= v;
		return ret;
	}

	Vec2_T operator/(const T& t)
	{
		Vec2_T ret(*this);
		ret /= t;
		return ret;
	}

	Vec2_T& operator=(const Vec2_T& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	Vec2_T& operator=(const T& v)
	{
		x = v;
		y = v;
		return *this;
	}

	Vec2_T& operator+=(const Vec2_T& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vec2_T& operator+=(const T& v)
	{
		x += v;
		y += v;
		return *this;
	}

	Vec2_T& operator-=(const Vec2_T& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vec2_T& operator-=(const T& v)
	{
		x -= v;
		y -= v;
		return *this;
	}

	Vec2_T& operator*=(const Vec2_T& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	Vec2_T& operator*=(const T& v)
	{
		x *= v;
		y *= v;
		return *this;
	}

	Vec2_T& operator/=(const Vec2_T& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	Vec2_T& operator/=(const T& v)
	{
		x /= v;
		y /= v;
		return *this;
	}

	[[nodiscard]] const T operator()(const int index) const
	{
		if (index == 0) return x;
		if (index == 1) return y;

	}

	bool operator==(const Vec2_T &v) const
	{
		return x == v.x && y == v.y;
	}
	bool operator!=(const Vec2_T &v) const
	{
		return !(*this == v);
	}

};
typedef Vec2_T<int>Vec2_i;
typedef Vec2_T<float>Vec2;
typedef Vec2_T<double>Vec2_d;


/**
*   @brief 3次元ベクトルを扱います
*/
template <class T> class Vec3_T
{
public:
	T x, y, z;
	Vec3_T() :
		x(0),
		y(0),
		z(0)
	{}
	template<class U>
	Vec3_T(const Vec3_T<U>& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	Vec3_T(const T setX, const T setY, const T setZ)
	{
		x = setX;
		y = setY;
		z = setZ;
	}
	Vec3_T(const Vec3_T& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	
	~Vec3_T() {};
	/*!
	* @brief オフセット値を返します
	* @return Vec3
	*/
	[[nodiscard]] const Vec3_T offSetCopy(const T setX, const T setY, const T setZ) const
	{
		Vec3_T ret(*this);
		ret.x += setX;
		ret.y += setY;
		ret.z += setZ;
		return ret;
	}
	/*!
	* @brief 内積を返します
	* @return float
	*/
	[[nodiscard]] const T dot(const Vec3_T& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	/*!
	* @brief 外積を返します
	* @return Vec3
	*/
	[[nodiscard]] const Vec3_T cross(const Vec3_T& v) const
	{
		Vec3_T result;
		result.x = y * v.z - z * v.y;
		result.y = z * v.x - x * v.z;
		result.z = x * v.y - y * v.x;
		return result;
	}
	/*!
	* @brief 内積を返します
	* @return 内積
	*/
	[[nodiscard]] static T Dot(const Vec3_T& v1, const Vec3_T& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	/*!
	* @brief 外積を返します
	* @return 外積
	*/
	[[nodiscard]] static Vec3_T Cross(const Vec3_T& v1, const Vec3_T& v2)
	{
		Vec3_T result;
		result.x = v1.y * v2.z - v1.z * v2.y;
		result.y = v1.z * v2.x - v1.x * v2.z;
		result.z = v1.x * v2.y - v1.y * v2.x;
		return result;
	}
	//! @brief すべてのパラメーターを0にします
	void zero()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	/*!
	* @brief 長さを返します
	* @return float
	*/
	[[nodiscard]] const T length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	/*!
	* @brief 自分自身を正規化した値を返します
	* @return Vec3
	*/
	[[nodiscard]] const Vec3_T& normalize()
	{
		T tmp = length();
		x /= tmp;
		y /= tmp;
		z /= tmp;
		return *this;
	}
	/*!
	* @brief 自分自身を正規化した値のコピーを返します。自身の値は変わりません
	* @return Vec3
	*/
	[[nodiscard]] const Vec3_T& getNormalize() const
	{
		Vec3_T result = *this;
		result.normalize();
		return result;
	}
	/*!
	* @brief 2点間の距離を返します
	* @note C++17でないとエラー
	* @return 距離
	*/
	[[nodiscard]] const T getDistance(const Vec3_T& v) const
	{
		const T dx = x - v.x;
		const T dy = y - v.y;
		const T dz = z - v.z;
		return std::hypot(dx, dy, dz);
	}

	Vec3_T& operator=(const  Vec3_T& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	Vec3_T& operator=(const  T& v)
	{
		x = v;
		y = v;
		z = v;
		return *this;
	}

	Vec3_T operator+() const
	{
		return Vec3_T(*this);
	}

	Vec3_T operator-() const
	{
		return Vec3_T(-this->x, -this->y, -this->z);
	}

	Vec3_T operator+(const Vec3_T& v) const
	{
		Vec3_T ret(*this);
		ret += v;
		return ret;
	}

	Vec3_T operator+(const T& t)
	{
		Vec3_T ret(*this);
		ret += t;
		return ret;
	}

	Vec3_T operator-(const Vec3_T& v) const
	{
		Vec3_T ret(*this);
		ret -= v;
		return ret;
	}

	Vec3_T operator-(const T& t)
	{
		Vec3_T ret(*this);
		ret -= t;
		return ret;
	}

	Vec3_T operator*(const Vec3_T& v)
	{
		Vec3_T ret(*this);
		ret *= v;
		return ret;
	}

	const Vec3_T operator*(const T& t) const
	{
		Vec3_T ret(*this);
		ret *= t;
		return ret;
	}

	Vec3_T operator/(const Vec3_T& v)
	{
		Vec3_T ret(*this);
		ret /= v;
		return ret;
	}

	Vec3_T operator/(const T& t)
	{
		Vec3_T ret(*this);
		ret /= t;
		return ret;
	}

	Vec3_T& operator+=(const Vec3_T& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vec3_T& operator+=(const T& v)
	{
		x += v;
		y += v;
		z += v;
		return *this;
	}

	Vec3_T& operator-=(const Vec3_T& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vec3_T& operator-=(const T& v)
	{
		x -= v;
		y -= v;
		z -= v;
		return *this;
	}

	Vec3_T& operator*=(const Vec3_T& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vec3_T& operator*=(const T& v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	Vec3_T& operator/=(const Vec3_T& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	Vec3_T& operator/=(const T& v)
	{
		x /= v;
		y /= v;
		z /= v;
		return *this;
	}

	[[nodiscard]] const T operator()(const int idx) const
	{
		if (idx == 0) return x;
		if (idx == 1) return y;
		if (idx == 2) return z;
	}

	bool operator==(const Vec3_T &v) const
	{
		return (x == v.x && y == v.y && v.z == z);
	}
	bool operator!=(const Vec3_T &v) const
	{
		return !(*this == v);
	}

};
typedef Vec3_T<int>Vec3_i;
typedef Vec3_T<float>Vec3;
typedef Vec3_T<double>Vec3_d;
