#ifndef VEC3_H
#define VEC3_H

#include <array>
#include <cmath>
#include <iostream>
#include <utility>

namespace vec {

template<typename T> requires (std::is_arithmetic_v<T>)
class Vec3 {
public:

	constexpr Vec3() : _x{0}, _y{0}, _z{0} {}
	constexpr Vec3(T v) : _x{v}, _y{v}, _z{v} {}
	constexpr Vec3(T x, T y, T z) : _x{x}, _y{y}, _z{z} {}

	constexpr T x() const { return _x; }
	constexpr T y() const { return _y; }
	constexpr T z() const { return _z; }
	constexpr T r() const { return _x; }
	constexpr T g() const { return _y; }
	constexpr T b() const { return _z; }

	Vec3 operator-() const { return Vec3{-_x, -_y, -_z}; }

	Vec3& operator+=(const Vec3& other) {
		_x += other._x;
		_y += other._y;
		_z += other._z;
		return *this;
	}

	Vec3& operator*=(T t) {
		_x *= t;
		_y *= t;
		_z *= t;
		return *this;
	}

	Vec3& operator/=(T t) {
		return *this *= (1 / t);
	}

	constexpr T length() const { return std::sqrt(lengthSquared()); }
	constexpr T lengthSquared() const { return _x * _x + _y * _y + _z * _z; }

private:
	T _x;
	T _y;
	T _z;

};

}

template<typename T>
using Point3 = vec::Vec3<T>;

using Vec3f = vec::Vec3<float>;
using Vec3d = vec::Vec3<double>;
using Point3f = Point3<float>;
using Point3d = Point3<double>;

template<typename T>
std::ostream& operator<<(std::ostream& out, const vec::Vec3<T>& v) {
	return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

template<typename T, typename U>
auto operator+(const vec::Vec3<T>& v, const vec::Vec3<U>& w) {
	return vec::Vec3{v.x() + w.x(), v.y() + w.y(), v.z() + w.z()};
}

template<typename T, typename U>
auto operator-(const vec::Vec3<T>& v, const vec::Vec3<U>& w) {
	return vec::Vec3{v.x() - w.x(), v.y() - w.y(), v.z() - w.z()};
}

template<typename T, typename U>
auto operator*(const vec::Vec3<T>& v, const vec::Vec3<U>& w) {
	return vec::Vec3{v.x() * w.x(), v.y() * w.y(), v.z() * w.z()};
}

template<typename T, typename U>
auto operator/(const vec::Vec3<T>& v, const vec::Vec3<U>& w) {
	return vec::Vec3{v.x() / w.x(), v.y() / w.y(), v.z() / w.z()};
}

template<typename T, typename U>
auto operator*(const vec::Vec3<T>& v, U u) {
	return vec::Vec3(v.x() * u, v.y() * u, v.z() * u);
}

template<typename T, typename U>
auto operator*(U u, const vec::Vec3<T>& v) {
	return v * u;
}

template<typename T, typename U>
auto operator/(const vec::Vec3<T>& v, U u) {
	return vec::Vec3{v.x() / u, v.y() / u, v.z() / u};
}

template<typename T, typename U>
auto dot(const vec::Vec3<T>& v, const vec::Vec3<U>& w) {
	return v.x() * w.x() + v.y() * w.y() + v.z() * w.z();
}

template<typename T, typename U>
auto cross(const vec::Vec3<T>& v, const vec::Vec3<U>& w) {
	return vec::Vec3{v.y() * w.z() - v.z() * w.y(),
				v.z() * w.x() - v.x() * w.z(),
				v.x() * w.y() - v.y() * w.x()};
}

template<typename T>
auto unitVector(const vec::Vec3<T>& v) {
	return v / v.length();
}

template<typename T, typename U>
auto reflect(const vec::Vec3<T> v, const vec::Vec3<U> n) {
	return v - 2 * dot(v, n) * n;
}


template<typename T, typename U>
auto refract(const vec::Vec3<T>& uv, const vec::Vec3<U>& n, double etaIOverEtaT) {
	auto cosTheta = std::min(dot(-uv, n), 1.0);
	const Vec3d perpendicular = etaIOverEtaT * (uv + cosTheta * n);
	const Vec3d parallel = -std::sqrt(std::abs(1 - perpendicular.lengthSquared())) * n;
	return perpendicular + parallel;
}

#endif // VEC3_H