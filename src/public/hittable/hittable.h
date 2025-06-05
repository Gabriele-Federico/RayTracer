#ifndef HITTABLE_H
#define HITTABLE_H

#include <interval/interval.h>
#include <ray/ray.h>
#include <vec/vec3.h>

class Material;

namespace hit {
struct HitResult {
	Point3d point;
	double distance;

	void setFaceNormal(const ray::Ray& ray, const Vec3d& outwardNormal) noexcept;
	void setMaterial(const std::shared_ptr<Material>& material) noexcept;
	constexpr Vec3d normal() const noexcept { return _normal; }
	constexpr bool frontFace() const noexcept { return _frontFace; }
	std::shared_ptr<Material> material() const { return _material; }

private:
	bool _frontFace;
	Vec3d _normal;
	std::shared_ptr<Material> _material;
};

class Hittable {
public:
	virtual ~Hittable() = default;
	virtual bool hit(const ray::Ray& ray, Interval interval, HitResult& res) const = 0;
};

}

#endif // HITTABLE_H