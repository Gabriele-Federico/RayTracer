#include <hittable/sphere.h>

bool Sphere::hit(const ray::Ray& ray, Interval interval, hit::HitResult& res) const {
	const Vec3d oc = _center - ray.origin();
	const auto a = ray.direction().lengthSquared();
	const auto h = dot(ray.direction(), oc);
	const auto c = oc.lengthSquared() - _radius * _radius;
	const auto discriminant = h * h - a * c;
	if (discriminant < 0) return false;

	const auto sqrtDiscriminant = std::sqrt(discriminant);

	auto root = (h - sqrtDiscriminant) / a;
	if (!interval.surrounds(root)) {
		root = (h + sqrtDiscriminant) / a;
		if (!interval.surrounds(root)) {
			return false;
		}
	}

	res.distance = root;
	res.point = ray.at(res.distance);
	res.setFaceNormal(ray, (res.point - _center) / _radius);
	res.setMaterial(_material);
	return true;
}
