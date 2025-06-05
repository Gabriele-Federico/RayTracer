#include <hittable/hittable.h>

namespace hit {
void HitResult::setFaceNormal(const ray::Ray& ray, const Vec3d& outwardNormal) noexcept {
	_frontFace = (dot(ray.direction(), outwardNormal)) < 0;
	_normal = _frontFace ? outwardNormal : -outwardNormal;
}

void HitResult::setMaterial(const std::shared_ptr<Material>& material) noexcept {
	_material = material;
}
}
