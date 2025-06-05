#ifndef COLOR_H
#define COLOR_H

#include <vec/vec3.h>

using Colord = Vec3d;
using Colori = vec::Vec3<int32_t>;

namespace color {

Colori toColorI(const Colord& color);

void writeColor(std::ostream& out, const Colord& color);

double linearToGamma(double linearComponent);

Colord random();

Colord random(double min, double max);
}

#endif // COLOR_H