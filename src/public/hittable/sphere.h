#ifndef SPHERE_H
#define SPHERE_H

#include <hittable/hittable.h>
#include <material/material.h>
#include <vec/vec3.h>

#include <memory>
#include <utility>

class Sphere : public hit::Hittable {
public:
	Sphere(const Vec3d& center, double radius, const std::shared_ptr<Material>& material) :
		_center{center}, _radius{std::max(0.0, radius)}, _material{material} {}
	bool hit(const ray::Ray& ray, Interval interval, hit::HitResult& res) const override;

private:
	Vec3d _center;
	double _radius;
	std::shared_ptr<Material> _material;
};

#endif // SPHERE_H