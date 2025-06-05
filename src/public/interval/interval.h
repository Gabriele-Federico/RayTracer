#ifndef INTERVAL_H
#define INTERVAL_H

#include <math/constants.h>

class Interval {
public:
	Interval() : _min{constants::infinity}, _max{-constants::infinity} {}
	Interval(double min, double max) : _min{min}, _max{max} {}

	double size() const { return _max - _min; }
	constexpr double min() { return _min; }
	constexpr double max() { return _max; }

	bool contains(double x) const { return _min <= x && x <= _max; }
	bool surrounds(double x) const { return _min < x && x < _max; }
	double clamp(double x) const;

	static const Interval EMPTY;
	static const Interval UNIVERSE;

private:

	double _min;
	double _max;

};

#endif // INTERVAL_H