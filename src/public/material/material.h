#ifndef MATERIAL_H
#define MATERIAL_H

#include <color/color.h>
#include <hittable/hittable.h>
#include <ray/ray.h>

class Material {
public:
	virtual ~Material() = default;

	virtual bool scatter(const ray::Ray& ray, const hit::HitResult& res, Colord& attenuation, ray::Ray& scattered) const;
};


class Lambertian : public Material {
public:
	Lambertian(const Colord& albedo) : _albedo(albedo) {}

	bool scatter(const ray::Ray& ray, const hit::HitResult& res, Colord& attenuation, ray::Ray& scattered) const override;

private:
	Colord _albedo;
};

class Metal : public Material {
public:
	Metal(const Colord& albedo, double fuzz) : _albedo{albedo}, _fuzz{fuzz < 1 ? fuzz : 1} {}

	bool scatter(const ray::Ray& ray, const hit::HitResult& res, Colord& attenuation, ray::Ray& scattered) const override;

private:
	Colord _albedo;
	double _fuzz;

};

class Dielectric : public Material {
public:
	Dielectric(double refractionIndex) : _refractionIndex{refractionIndex} {}

	bool scatter(const ray::Ray& ray, const hit::HitResult& res, Colord& attenuation, ray::Ray& scattered) const override;

private:
	double reflectance(double cosine, double refractionIndex) const noexcept;

	double _refractionIndex;
};

#endif