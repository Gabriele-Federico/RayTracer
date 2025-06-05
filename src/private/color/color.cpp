#include <color/color.h>

#include <interval/interval.h>
#include <math/math_utils.h>

namespace color {

Colori toColorI(const Colord& color) {
	return {static_cast<int32_t>(255.999 * color.r()),
			static_cast<int32_t>(255.999 * color.g()),
			static_cast<int32_t>(255.999 * color.b())};
}

void writeColor(std::ostream& out, const Colord& color) {
	static const Interval intensity{0.0, 0.999};

	const auto r = linearToGamma(color.r());
	const auto g = linearToGamma(color.g());
	const auto b = linearToGamma(color.b());

	int32_t rbyte = static_cast<int32_t>(256 * intensity.clamp(r));
	int32_t gbyte = static_cast<int32_t>(256 * intensity.clamp(g));
	int32_t bbyte = static_cast<int32_t>(256 * intensity.clamp(b));


	out << rbyte << ' ' << gbyte << ' ' << bbyte << "\n";
}

double linearToGamma(double linearComponent) {
	return linearComponent > 0.0 ? std::sqrt(linearComponent) : 0.0;
}

Colord random() {
	return math_utils::randomVec<double>();
}

Colord random(double min, double max) {
	return math_utils::randomVec<double>(min, max);
}

}
