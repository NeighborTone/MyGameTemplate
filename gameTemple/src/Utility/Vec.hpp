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
*/
#pragma once

/**
*   @brief 2次元ベクトルを扱います
*/
template <class T> class TVec2
{
public:
	T x, y;
	TVec2() :
		x(0),
		y(0)
	{};
	TVec2(const T setX, const T setY)
	{
		x = setX;
		y = setY;
	};
	TVec2(const TVec2& v)
	{
		x = v.x;
		y = v.y;
	}
	~TVec2() {};
	/*!
	* @brief オフセット値を返します
	* @return Vec2
	*/
	[[nodiscard]] const TVec2 offSetCopy(const T setX, const T setY) const
	{
		TVec2 ret(*this);
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
	[[nodiscard]] const T dot(const TVec2& v) const
	{
		return x * v.x + y * v.y;
	}

	/*!
	* @brief 外積を返します
	* @return 外積
	*/
	[[nodiscard]] const T cross(const TVec2& v) const
	{
		return x * v.y - v.x * y;
	}

	/*!
	* @brief 内積を返します
	* @return 内積
	*/
	[[nodiscard]] static T Dot(const TVec2& v1, const TVec2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	/*!
	* @brief 外積を返します
	* @return 外積
	*/
	[[nodiscard]] static T Cross(const TVec2& v1, const TVec2& v2)
	{
		return v1.x * v2.y - v2.x * v1.y;
	}
	/*!
	* @brief 2点間の距離を返します
	* @return 距離
	*/
	[[nodiscard]] const T getDistance(const TVec2& v) const
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
	[[nodiscard]] const TVec2&  normalize()
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
	[[nodiscard]] const TVec2&  getNormalize() const
	{
		TVec2 result = *this;
		result.normalize();
		return result;
	}

	TVec2 operator+() const
	{
		return TVec2(*this);
	}

	TVec2 operator-() const
	{
		return TVec2(-x, -y);
	}

	TVec2 operator+(const TVec2& v) const
	{
		TVec2 ret(*this);
		ret += v;
		return ret;
	}

	TVec2 operator+(const T& t)
	{
		TVec2 ret(*this);
		ret += t;
		return ret;
	}

	TVec2 operator-(const TVec2& v) const
	{
		TVec2 ret(*this);
		ret -= v;
		return ret;
	}

	TVec2 operator-(const T& t)
	{
		TVec2 ret(*this);
		ret -= t;
		return ret;
	}

	TVec2 operator*(const TVec2& v)
	{
		TVec2 ret(*this);
		ret *= v;
		return ret;
	}

	TVec2 operator*(const T& t)
	{
		TVec2 ret(*this);
		ret *= t;
		return ret;
	}

	TVec2 operator/(const TVec2& v)
	{
		TVec2 ret(*this);
		ret /= v;
		return ret;
	}

	TVec2 operator/(const T& t)
	{
		TVec2 ret(*this);
		ret /= t;
		return ret;
	}

	TVec2& operator=(const TVec2& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	TVec2& operator=(const T& v)
	{
		x = v;
		y = v;
		return *this;
	}

	TVec2& operator+=(const TVec2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	TVec2& operator+=(const T& v)
	{
		x += v;
		y += v;
		return *this;
	}

	TVec2& operator-=(const TVec2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	TVec2& operator-=(const T& v)
	{
		x -= v;
		y -= v;
		return *this;
	}

	TVec2& operator*=(const TVec2& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	TVec2& operator*=(const T& v)
	{
		x *= v;
		y *= v;
		return *this;
	}

	TVec2& operator/=(const TVec2& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	TVec2& operator/=(const T& v)
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

	bool operator==(const TVec2 &v) const
	{
		return x == v.x && y == v.y;
	}
	bool operator!=(const TVec2 &v) const
	{
		return !(*this == v);
	}

};
typedef TVec2<int>Vec2_i;
typedef TVec2<float>Vec2;
typedef TVec2<double>Vec2_d;


/**
*   @brief 3次元ベクトルを扱います
*/
template <class T> class TVec3
{
public:
	T x, y, z;
	TVec3() :
		x(0),
		y(0),
		z(0)
	{}
	TVec3(const T setX, const T setY, const T setZ)
	{
		x = setX;
		y = setY;
		z = setZ;
	}
	TVec3(const TVec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	
	~TVec3() {};
	/*!
	* @brief オフセット値を返します
	* @return Vec3
	*/
	[[nodiscard]] const TVec3 offSetCopy(const T setX, const T setY, const T setZ) const
	{
		TVec3 ret(*this);
		ret.x += setX;
		ret.y += setY;
		ret.z += setZ;
		return ret;
	}
	/*!
	* @brief 内積を返します
	* @return float
	*/
	[[nodiscard]] const T dot(const TVec3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	/*!
	* @brief 外積を返します
	* @return Vec3
	*/
	[[nodiscard]] const TVec3 cross(const TVec3& v) const
	{
		TVec3 result;
		result.x = y * v.z - z * v.y;
		result.y = z * v.x - x * v.z;
		result.z = x * v.y - y * v.x;
		return result;
	}
	/*!
	* @brief 内積を返します
	* @return 内積
	*/
	[[nodiscard]] static T Dot(const TVec3& v1, const TVec3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	/*!
	* @brief 外積を返します
	* @return 外積
	*/
	[[nodiscard]] static TVec3 Cross(const TVec3& v1, const TVec3& v2)
	{
		TVec3 result;
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
	[[nodiscard]] const TVec3& normalize()
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
	[[nodiscard]] const TVec3& getNormalize() const
	{
		TVec3 result = *this;
		result.normalize();
		return result;
	}
	/*!
	* @brief 2点間の距離を返します
	* @note C++17でないとエラー
	* @return 距離
	*/
	[[nodiscard]] const T getDistance(const TVec3&& v) const
	{
		const T dx = x - v.x;
		const T dy = y - v.y;
		const T dz = z - v.z;
		return std::hypot(dx, dy, dz);
	}

	TVec3& operator=(const  TVec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	TVec3& operator=(const  T& v)
	{
		x = v;
		y = v;
		z = v;
		return *this;
	}

	TVec3 operator+() const
	{
		return TVec3(*this);
	}

	TVec3 operator-() const
	{
		return TVec3(-this->x, -this->y, -this->z);
	}

	TVec3 operator+(const TVec3& v) const
	{
		TVec3 ret(*this);
		ret += v;
		return ret;
	}

	TVec3 operator+(const T& t)
	{
		TVec3 ret(*this);
		ret += t;
		return ret;
	}

	TVec3 operator-(const TVec3& v) const
	{
		TVec3 ret(*this);
		ret -= v;
		return ret;
	}

	TVec3 operator-(const T& t)
	{
		TVec3 ret(*this);
		ret -= t;
		return ret;
	}

	TVec3 operator*(const TVec3& v)
	{
		TVec3 ret(*this);
		ret *= v;
		return ret;
	}

	const TVec3 operator*(const T& t) const
	{
		TVec3 ret(*this);
		ret *= t;
		return ret;
	}

	TVec3 operator/(const TVec3& v)
	{
		TVec3 ret(*this);
		ret /= v;
		return ret;
	}

	TVec3 operator/(const T& t)
	{
		TVec3 ret(*this);
		ret /= t;
		return ret;
	}

	TVec3& operator+=(const TVec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	TVec3& operator+=(const T& v)
	{
		x += v;
		y += v;
		z += v;
		return *this;
	}

	TVec3& operator-=(const TVec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	TVec3& operator-=(const T& v)
	{
		x -= v;
		y -= v;
		z -= v;
		return *this;
	}

	TVec3& operator*=(const TVec3& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	TVec3& operator*=(const T& v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	TVec3& operator/=(const TVec3& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	TVec3& operator/=(const T& v)
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

	bool operator==(const TVec3 &v) const
	{
		return (x == v.x && y == v.y && v.z == z);
	}
	bool operator!=(const TVec3 &v) const
	{
		return !(*this == v);
	}

};
typedef TVec3<int>Vec3_i;
typedef TVec3<float>Vec3;
typedef TVec3<double>Vec3_d;
