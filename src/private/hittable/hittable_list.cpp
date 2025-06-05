#include <hittable/hittable_list.h>

namespace hit {
bool HittableList::hit(const ray::Ray& ray, Interval interval, HitResult& res) const noexcept {
	HitResult temp;
	bool hit = false;
	auto closest = interval.max();
	for (auto& object : _objects) {
		if (object->hit(ray, Interval(interval.min(), closest), temp)) {
			hit = true;
			closest = temp.distance;
			res = temp;
		}
	}
	
	return hit;
}
}

