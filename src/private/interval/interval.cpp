#include <interval/interval.h>

const Interval Interval::EMPTY = Interval(constants::infinity, -constants::infinity);
const Interval Interval::UNIVERSE = Interval(-constants::infinity, constants::infinity);

double Interval::clamp(double x) const {
	if(x < _min) return _min;
	if(x > _max) return _max;
	return x;
}
