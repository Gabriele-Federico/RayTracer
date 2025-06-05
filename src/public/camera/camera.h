#ifndef CAMERA_H
#define CAMERA_H

#include <color/color.h>
#include <hittable/hittable.h>
#include <ray/ray.h>
#include <vec/vec3.h>

namespace camera {
class Camera {
public:
	Camera(double aspectRatio, int32_t width, const Point3d& lookFrom, const Point3d& lookAt, const Vec3d& up, double verticalFov, double defocusAngle, double focusDistance, int32_t samples, size_t maxDepth)
		: _aspectRatio{aspectRatio}, _width{width}, _lookFrom{lookFrom}, _lookAt{lookAt}, _up{up}, _verticalFov{verticalFov}, _defocusAngle{defocusAngle}, _focusDistance{focusDistance}, _samplesPerPixel{samples}, _maxDepth{maxDepth} {}
	void render(const hit::Hittable& world);

private:
	void initialize();

	Colord rayColor(const ray::Ray& ray, size_t depth, const hit::Hittable& world) const;

	ray::Ray getRay(size_t i, size_t j) const;

	Point3d defocusDiskSample() const;

	double _aspectRatio = 1.0;
	int32_t _width = 100;
	int32_t _height;
	Point3d _center;
	Vec3d _pixelDeltaU;
	Vec3d _pixelDeltaV;
	Vec3d _pixel00Loc;

	Point3d _lookFrom = Point3d(0);
	Point3d _lookAt = Point3d(0.0, 0.0, -1.0);
	Vec3d _up = Vec3d(0.0, 1.0, 0.0);

	double _verticalFov = 90;

	double _defocusAngle = 0;
	double _focusDistance = 10;

	Vec3d _defocusDiskU;
	Vec3d _defocusDiskV;


	Vec3d _u;
	Vec3d _v;
	Vec3d _w;

	int32_t _samplesPerPixel = 50;
	size_t _maxDepth = 10;

	double _pixelsSamplesScale;

};

}

#endif // CAMERA_H