#pragma once
#pragma warning (disable : 4458)	//this���g�����ߏ���
#pragma warning (disable : 4715)	//�s���Ȓl�̏ꍇ���Ƃ�����
#include <DirectXMath.h>

template <typename T>
/*! @class Vec2
*   @brief 2�����x�N�g���������܂�
*   @detail ���ρA�O�ρA���K���A�����𑪂�@�\������܂�
*/
class TemplateVec2
{
public:
	T x, y;
	TemplateVec2() :
		x(0),
		y(0)
	{};
	TemplateVec2(const T x, const T y)
	{
		this->x = x;
		this->y = y;
	};
	TemplateVec2(const TemplateVec2& v)
	{
		x = v.x;
		y = v.y;
	}
	~TemplateVec2() {};
	/*!
	* @brief XMVECTOR��Ԃ��܂�
	* @return XMVECTOR
	*/
	const DirectX::XMVECTOR ToXMVECTOR() const
	{
		DirectX::XMVECTOR ret;
		DirectX::XMVectorSetX(ret, this->x);
		DirectX::XMVectorSetY(ret, this->y);
		return ret;
	}
	/*!
	* @brief �I�t�Z�b�g�l��Ԃ��܂�
	* @return Vec2
	*/
	const TemplateVec2 OffSetCopy(const T x, const T y) const
	{
		TemplateVec2 ret(*this);
		ret.x += x;
		ret.y += y;
		return ret;
	}
	//!0�x�N�g�������܂�
	void Zero()
	{
		x = 0;
		y = 0;
	}

	/*!
	* @brief ���ς�Ԃ��܂�
	* @return ����
	*/
	const T Dot(const TemplateVec2& v) const
	{
		return x * v.x + y * v.y;
	}

	/*!
	* @brief �O�ς�Ԃ��܂�
	* @return �O��
	*/
	const T Cross(const TemplateVec2& v) const
	{
		return x * v.y - v.x * y;
	}

	/*!
	* @brief ���ς�Ԃ��܂�
	* @return ����
	*/
	static T Dot(const TemplateVec2& v1, const TemplateVec2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	/*!
	* @brief �O�ς�Ԃ��܂�
	* @return �O��
	*/
	static T Cross(const TemplateVec2& v1, const TemplateVec2& v2)
	{
		return v1.x * v2.y - v2.x * v1.y;
	}
	/*!
	* @brief 2�_�Ԃ̋�����Ԃ��܂�
	* @return ����
	*/
	const T GetDistance(const TemplateVec2& v) const
	{
		const T dx = x - v.x;
		const T dy = y - v.y;

		return hypot(dx, dy);
	}

	/*!
	* @brief ������Ԃ��܂�
	* @return ����
	*/
	const T Length() const
	{
		return sqrtf(x * x + y * y);
	}
	/*!
	* @brief �������g�𐳋K�������l��Ԃ��܂�
	* @return Vec2
	*/
	const TemplateVec2&  Normalize()
	{
		T tmp = Length();
		x /= tmp;
		y /= tmp;
		return *this;
	}
	/*!
	* @brief �������g�𐳋K�������l�̃R�s�[��Ԃ��܂��B���g�̒l�͕ς��܂���
	* @return Vec2
	*/
	const TemplateVec2  GetNormalize() const
	{
		TemplateVec2 result = *this;
		result.Normalize();
		return result;
	}

	TemplateVec2 operator+() const
	{
		return TemplateVec2(*this);
	}

	TemplateVec2 operator-() const
	{
		return TemplateVec2(-x, -y);
	}

	TemplateVec2 operator+(const TemplateVec2& v) const
	{
		TemplateVec2 ret(*this);
		ret += v;
		return ret;
	}

	TemplateVec2 operator+(const T& t)
	{
		TemplateVec2 ret(*this);
		ret += t;
		return ret;
	}

	TemplateVec2 operator-(const TemplateVec2& v) const
	{
		TemplateVec2 ret(*this);
		ret -= v;
		return ret;
	}

	TemplateVec2 operator-(const T& t)
	{
		TemplateVec2 ret(*this);
		ret -= t;
		return ret;
	}

	TemplateVec2 operator*(const TemplateVec2& v)
	{
		TemplateVec2 ret(*this);
		ret *= v;
		return ret;
	}

	TemplateVec2 operator*(const T& t)
	{
		TemplateVec2 ret(*this);
		ret *= t;
		return ret;
	}

	TemplateVec2 operator/(const TemplateVec2& v)
	{
		TemplateVec2 ret(*this);
		ret /= v;
		return ret;
	}

	TemplateVec2 operator/(const T& t)
	{
		TemplateVec2 ret(*this);
		ret /= t;
		return ret;
	}

	TemplateVec2& operator=(const TemplateVec2& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	TemplateVec2& operator=(const T& v)
	{
		x = v;
		y = v;
		return *this;
	}

	TemplateVec2& operator+=(const TemplateVec2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	TemplateVec2& operator+=(const T& v)
	{
		x += v;
		y += v;
		return *this;
	}

	TemplateVec2& operator-=(const TemplateVec2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	TemplateVec2& operator-=(const T& v)
	{
		x -= v;
		y -= v;
		return *this;
	}

	TemplateVec2& operator*=(const TemplateVec2& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	TemplateVec2& operator*=(const T& v)
	{
		x *= v;
		y *= v;
		return *this;
	}

	TemplateVec2& operator/=(const TemplateVec2& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	TemplateVec2& operator/=(const T& v)
	{
		x /= v;
		y /= v;
		return *this;
	}

	const T operator()(const int idx) const
	{
		if (idx == 0) return x;
		if (idx == 1) return y;

		assert(0);
	}

	bool operator==(const TemplateVec2 &v) const
	{
		return x == v.x && y == v.y;
	}
	bool operator!=(const TemplateVec2 &v) const
	{
		return !(*this == v);
	}

};
typedef TemplateVec2<int>Vec2_i;
typedef TemplateVec2<float>Vec2;
typedef TemplateVec2<double>Vec2_d;


template <typename T>
/*! @class Vec3
*   @brief 3�����x�N�g���������܂�
*   @detail ���ρA�O�ρA���K���A�����𑪂�@�\������܂�
*/
class TemplateVec3
{
public:
	T x, y, z;
	TemplateVec3() :
		x(0),
		y(0),
		z(0)
	{}
	TemplateVec3(const T x, const T y, const T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	TemplateVec3(const TemplateVec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	/*!
	* @brief XMVECTOR��Ԃ��܂�
	* @return XMVECTOR
	*/
	const DirectX::XMVECTOR ToXMVECTOR() const
	{
		DirectX::XMVECTOR ret = {};
		DirectX::XMVectorSetX(ret, this->x);
		DirectX::XMVectorSetY(ret, this->y);
		DirectX::XMVectorSetZ(ret, this->z);
		return ret;
	}
	~TemplateVec3() {};
	/*!
	* @brief �I�t�Z�b�g�l��Ԃ��܂�
	* @return Vec3
	*/
	const TemplateVec3 OffSetCopy(const T x, const T y, const T z) const
	{
		TemplateVec3 ret(*this);
		ret.x += x;
		ret.y += y;
		ret.z += z;
		return ret;
	}
	/*!
	* @brief ���ς�Ԃ��܂�
	* @return float
	*/
	const T Dot(const TemplateVec3&& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	/*!
	* @brief �O�ς�Ԃ��܂�
	* @return Vec3
	*/
	const TemplateVec3 Cross(const TemplateVec3&& v) const
	{
		TemplateVec3 result;
		result.x = y * v.z - z * v.y;
		result.y = z * v.x - x * v.z;
		result.z = x * v.y - y * v.x;
		return result;
	}

	/*!
	* @brief 2�_�Ԃ̋�����Ԃ��܂�
	* @note C++17�łȂ��ƃG���[
	* @return ����
	*/
	const T GetDistance(const TemplateVec3&& v) const
	{
		const T dx = x - v.x;
		const T dy = y - v.y;
		const T dz = z - v.z;

		return std::hypot(dx, dy, dz);
	}
	//!���ׂẴp�����[�^�[��0�ɂ��܂�
	void Zero()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	/*!
	* @brief ������Ԃ��܂�
	* @return float
	*/
	const T Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	/*!
	* @brief �������g�𐳋K�������l��Ԃ��܂�
	* @return Vec3
	*/
	const TemplateVec3&  Normalize()
	{
		T tmp = Length();
		x /= tmp;
		y /= tmp;
		z /= tmp;
		return *this;
	}
	/*!
	* @brief �������g�𐳋K�������l�̃R�s�[��Ԃ��܂��B���g�̒l�͕ς��܂���
	* @return Vec3
	*/
	const TemplateVec3  GetNormalize() const
	{
		TemplateVec3 result = *this;
		result.Normalize();
		return result;
	}

	TemplateVec3&	operator=(const  TemplateVec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	TemplateVec3&	operator=(const  T& v)
	{
		x = v;
		y = v;
		z = v;
		return *this;
	}

	TemplateVec3 operator+() const
	{
		return TemplateVec3(*this);
	}

	TemplateVec3 operator-() const
	{
		return TemplateVec3(-this->x, -this->y, -this->z);
	}

	TemplateVec3 operator+(const TemplateVec3& v) const
	{
		TemplateVec3 ret(*this);
		ret += v;
		return ret;
	}

	TemplateVec3 operator+(const T& t)
	{
		TemplateVec3 ret(*this);
		ret += t;
		return ret;
	}

	TemplateVec3 operator-(const TemplateVec3& v) const
	{
		TemplateVec3 ret(*this);
		ret -= v;
		return ret;
	}

	TemplateVec3 operator-(const T& t)
	{
		TemplateVec3 ret(*this);
		ret -= t;
		return ret;
	}

	TemplateVec3 operator*(const TemplateVec3& v)
	{
		TemplateVec3 ret(*this);
		ret *= v;
		return ret;
	}

	const TemplateVec3 operator*(const T& t) const
	{
		TemplateVec3 ret(*this);
		ret *= t;
		return ret;
	}

	TemplateVec3 operator/(const TemplateVec3& v)
	{
		TemplateVec3 ret(*this);
		ret /= v;
		return ret;
	}

	TemplateVec3 operator/(const T& t)
	{
		TemplateVec3 ret(*this);
		ret /= t;
		return ret;
	}

	TemplateVec3& operator+=(const TemplateVec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	TemplateVec3& operator+=(const T& v)
	{
		x += v;
		y += v;
		z += v;
		return *this;
	}

	TemplateVec3& operator-=(const TemplateVec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	TemplateVec3& operator-=(const T& v)
	{
		x -= v;
		y -= v;
		z -= v;
		return *this;
	}

	TemplateVec3& operator*=(const TemplateVec3& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	TemplateVec3& operator*=(const T& v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	TemplateVec3& operator/=(const TemplateVec3& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	TemplateVec3& operator/=(const T& v)
	{
		x /= v;
		y /= v;
		z /= v;
		return *this;
	}

	const T operator()(const int idx) const
	{
		if (idx == 0) return x;
		if (idx == 1) return y;
		if (idx == 2) return z;
		assert(0);
	}

	bool	operator==(const TemplateVec3 &v) const
	{
		return (x == v.x && y == v.y && v.z == z);
	}
	bool	operator!=(const TemplateVec3 &v) const
	{
		return !(*this == v);
	}

};
typedef TemplateVec3<int>Vec3_i;
typedef TemplateVec3<float>Vec3;
typedef TemplateVec3<double>Vec3_d;

/*! @class Float4
*   @brief 4��float�̒l�������܂�
*   @detail DirectX11�ł́A�F�̎w��Ȃǂ�4��foat�w�肷��̂Ŏ�ɂ���Ɏg���܂�
*/
class Float4
{
public:
	float r, g, b, a;
	Float4() :
		r(0),
		g(0),
		b(0),
		a(0)
	{}
	Float4(float x, float y, float z, float w)
	{
		this->r = x;
		this->g = y;
		this->b = z;
		this->a = w;
	}
	explicit Float4(const Float4& f4)
	{
		r = f4.r;
		g = f4.g;
		b = f4.b;
		a = f4.a;
	}
	~Float4() {};
	Float4&	operator=(const Float4& v)
	{
		r = v.r;
		g = v.g;
		b = v.b;
		a = v.a;
		return *this;
	}
	Float4& operator+=(const Float4& v)
	{
		r += v.r;
		g += v.g;
		b += v.b;
		a += v.a;
		return *this;
	}
	Float4& operator-=(const Float4& v)
	{
		r -= v.r;
		g -= v.g;
		b -= v.b;
		a -= v.a;
		return *this;
	}
	Float4& operator*=(const Float4& v)
	{
		r *= v.r;
		g *= v.g;
		b *= v.b;
		a *= v.a;
		return *this;
	}
	Float4& operator/=(const Float4& v)
	{
		r /= v.r;
		g /= v.g;
		b /= v.b;
		a /= v.a;
		return *this;
	}
	bool	operator==(const Float4 &v) const
	{
		return (r == v.r && g == v.g && v.b == b && a == v.a);
	}
	bool	operator!=(const Float4 &v) const
	{
		return !(*this == v);
	}

};

using Pos = Vec3;
using Velocity = Vec3;
using Angles = Vec3;
using Scale = Vec3;