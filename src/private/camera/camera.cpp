#include <camera/camera.h>

#include <math/constants.h>
#include <math/math_utils.h>
#include <material/material.h>

namespace camera {
void Camera::render(const hit::Hittable& world) {
	initialize();

	std::cout << "P3\n" << _width << ' ' << _height << "\n255\n";

	for (size_t j = 0; j < _height; ++j) {
		std::clog << "\rScanlines remaining " << (_height - j) << ' ' << std::flush;
		for (size_t i = 0; i < _width; ++i) {
			Colord pixelColor{0.0};
			for (size_t sample = 0; sample < _samplesPerPixel; ++sample) {
				const ray::Ray ray = getRay(i, j);
				pixelColor += rayColor(ray, _maxDepth, world);
			}
			color::writeColor(std::cout, pixelColor * _pixelsSamplesScale);
		}
	}
	std::clog << "\rDone.                  \n";

}

void Camera::initialize() {
	_height = static_cast<int32_t>(_width / _aspectRatio);
	_height = _height < 1 ? 1 : _height;

	_pixelsSamplesScale = 1.0 / _samplesPerPixel;

	_center = _lookFrom;
	const auto look = _lookFrom - _lookAt;
	const auto theta = math_utils::degreesToRadians(_verticalFov);
	const auto h = std::tan(theta / 2);

	const auto viewportHeight = 2.0 * h * _focusDistance;
	const auto viewportWidth = viewportHeight * (static_cast<double>(_width) / _height);

	_w = unitVector(look);
	_u = unitVector(cross(_up, _w));
	_v = cross(_w, _u);

	const auto viewportU = viewportWidth * _u;
	const auto viewportV = viewportHeight * -_v;

	_pixelDeltaU = viewportU / _width;
	_pixelDeltaV = viewportV / _height;

	const auto viewportUpperLeft = _center - (_focusDistance * _w) - viewportU / 2 - viewportV / 2;
	_pixel00Loc = viewportUpperLeft + 0.5 * (_pixelDeltaU + _pixelDeltaV);

	const auto defocusRadius = _focusDistance * std::tan(math_utils::degreesToRadians(_defocusAngle / 2));

	_defocusDiskU = _u * defocusRadius;
	_defocusDiskV = _v * defocusRadius;
}

Colord Camera::rayColor(const ray::Ray& ray, size_t depth, const hit::Hittable& world) const {

	if (depth == 0) return {0.0};

	hit::HitResult res;
	if (world.hit(ray, Interval(0.001, constants::infinity), res)) {
		ray::Ray scattered;
		Colord attenuation;

		if (res.material()->scatter(ray, res, attenuation, scattered)) {
			return attenuation * rayColor(scattered, depth - 1, world);
		}
		return {0.0};
	}

	const Vec3d unitDir = unitVector(ray.direction());
	const auto a = 0.9 * (unitDir.y() + 1.0);
	return math_utils::lerp(a, Colord(1.0), Colord(.5, .7, 1.0));
}

Vec3d sampleSquare() { return Vec3d(math_utils::random<double>() - .5, math_utils::random<double>() - .5, 0); }

ray::Ray Camera::getRay(size_t i, size_t j) const {
	const auto offset = sampleSquare();
	const auto pixelSample = _pixel00Loc + ((static_cast<double>(i) + offset.x()) * _pixelDeltaU)
		+ ((static_cast<double>(j) + offset.y()) * _pixelDeltaV);

	const auto rayOrigin = (_defocusAngle <= 0) ? _center : defocusDiskSample();
	const auto rayDirection = pixelSample - rayOrigin;

	return ray::Ray(rayOrigin, rayDirection);
}

Point3d Camera::defocusDiskSample() const {
	const auto p = math_utils::randomInUnitDisk<double>();
	return _center + (p.x() * _defocusDiskU) + (p.y() * _defocusDiskV);
}

}