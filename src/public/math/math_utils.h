#ifndef MATH_UTILS
#define MATH_UTILS
#include <iostream>
#include <math/constants.h>
#include <vec/vec3.h>

#include <random>

namespace math_utils {

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

constexpr auto lerp(auto v, auto start, auto end) {
	return (1 - v) * start + v * end;
}

constexpr double degreesToRadians(double degrees) {
	return degrees * constants::PI / 180.0;
}

template<arithmetic T>
inline T random() {
	if constexpr (std::is_floating_point_v<T>) {
		static std::uniform_real_distribution<T> distribution(0.0, 1.0);
		static std::mt19937 generator;
		return distribution(generator);
	}
	else {
		static std::uniform_int_distribution<T> distribution(0, 1);
		static std::mt19937 generator;
		return distribution(generator);
	}
}

template <arithmetic T>
inline T random(T min, T max) {
	return min + (max - min) * random<T>();
}

template <arithmetic T>
inline vec::Vec3<T> randomVec() {
	return vec::Vec3<T>(random<T>(), random<T>(), random<T>());
}

template <typename T>
inline vec::Vec3<T> randomVec(T min, T max) {
	return vec::Vec3<T>(random<T>(min, max), random<T>(min, max), random<T>(min, max));
}

template<typename T>
auto randomUnitVector() {
	while (true) {
		const auto p = math_utils::randomVec<T>(-1, 1);
		const auto lensq = p.lengthSquared();
		if (1e-160 < lensq && lensq <= 1) {
			return p / std::sqrt(lensq);
		}
	}
}

template <typename T>
inline vec::Vec3<T> randomOnHemisphere(const vec::Vec3<T>& normal) {
	vec::Vec3<T> onUnitSphere = randomUnitVector<T>();
	if (dot(onUnitSphere, normal) > 0.0) return onUnitSphere;
	return -onUnitSphere;
}


template<typename T>
inline vec::Vec3<T> randomInUnitDisk() {
	while (true) {
		auto p = vec::Vec3<T>(random<T>(-1, 1), random<T>(-1, 1), 0.0);
		if (p.lengthSquared() < 1) {
			return p;
		}
	}
}

inline bool nearZero(const Vec3d& vec) {
	constexpr auto e = 1e-8;
	return (std::abs(vec.x()) < e && std::abs(vec.y()) < e && std::abs(vec.z()) < e);
}

}

#endif // MATH_UTILS