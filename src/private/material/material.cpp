#include <material/material.h>

#include <math/math_utils.h>

bool Material::scatter(const ray::Ray& ray, const hit::HitResult& res, Colord& attenuation, ray::Ray& scattered) const {
	return false;
}

bool Lambertian::scatter(const ray::Ray& ray, const hit::HitResult& res, Colord& attenuation, ray::Ray& scattered) const {
	auto scatterDirection = res.normal() + math_utils::randomUnitVector<double>();

	if (math_utils::nearZero(scatterDirection)) scatterDirection = res.normal();

	scattered = ray::Ray(res.point, scatterDirection);
	attenuation = _albedo;

	return true;
}

bool Metal::scatter(const ray::Ray& ray, const hit::HitResult& res, Colord& attenuation, ray::Ray& scattered) const {
	Vec3d reflected = reflect(ray.direction(), res.normal());

	reflected = unitVector(reflected) + (_fuzz * math_utils::randomUnitVector<double>());
	scattered = ray::Ray(res.point, reflected);

	attenuation = _albedo;

	return (dot(scattered.direction(), res.normal()) > 0);
}

bool Dielectric::scatter(const ray::Ray& ray, const hit::HitResult& res, Colord& attenuation, ray::Ray& scattered) const {
	attenuation = Colord(1.0);
	const double refractionIndex = res.frontFace() ? (1.0 / _refractionIndex) : _refractionIndex;

	const Vec3d unitDirection = unitVector(ray.direction());
	const double cosTheta = std::min(dot(-unitDirection, res.normal()), 1.0);
	const double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

	const bool cannotRefract = refractionIndex * sinTheta > 1.0;
	const Vec3d direction = cannotRefract || reflectance(cosTheta, refractionIndex) > math_utils::random<double>() ?
		reflect(unitDirection, res.normal()) : refract(unitDirection, res.normal(), refractionIndex);

	scattered = ray::Ray(res.point, direction);
	return true;
}

double Dielectric::reflectance(double cosine, double refractionIndex) const noexcept {
	auto r0 = (1 - refractionIndex) / (1 + refractionIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}
