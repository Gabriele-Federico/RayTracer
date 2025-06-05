#ifndef RAY_H
#define RAY_H

#include <vec/vec3.h>

namespace ray {
class Ray {
public:
	Ray() = default;
	Ray(const Point3d& origin, const Vec3d& direction) : _origin{origin}, _direction{direction} {}

	constexpr const Point3d& origin() const { return _origin; }
	constexpr const Vec3d& direction() const { return _direction; }

	Point3d at(double t) const { return _origin + t * _direction; }

private:
	Point3d _origin;
	Vec3d _direction;

};
}

#endif // RAY_H
