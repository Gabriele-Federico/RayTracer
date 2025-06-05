#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <hittable/hittable.h>

#include <memory>
#include <vector>

namespace hit {
class HittableList : public Hittable {
public:
	HittableList() {}
	HittableList(const std::shared_ptr<Hittable>& object) { add(std::move(object)); }

	void clear() { _objects.clear(); }
	void add(const std::shared_ptr<Hittable>& object) { _objects.push_back(object); }

	constexpr auto objects() { return _objects; }

	bool hit(const ray::Ray& ray, Interval interval, HitResult& res) const noexcept override;
private:
	std::vector<std::shared_ptr<Hittable>> _objects;
};

}

#endif // HITTABLE_LIST_H