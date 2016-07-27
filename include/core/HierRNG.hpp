#ifndef CORE_HierRNG
#define CORE_HierRNG
#include <random>

class HierRNG {
	private:

	protected:
	static unsigned int seed;
	static std::mt19937 generator;

	public:
	static void initialize();
	static void initialize(unsigned int seed);

	template <typename T>
	using autoUniformDist = typename std::conditional<
		std::is_integral<T>::value,
		std::uniform_int_distribution<T>,
		typename std::conditional<
			std::is_floating_point<T>::value,
			std::uniform_real_distribution<T>,
			void
		>::type
	>::type;

	template <typename T>
	static T uniform(T lower, T upper);

	template <typename T>
	static T zeroOne();

	static double gaussian(double mean, double stdDev);
	static unsigned int index(unsigned int maxIndex);
	static bool binary();
};

template <typename T>
T HierRNG::uniform(T lower, T upper) {
	autoUniformDist<T> dist(lower, upper);
	return dist(HierRNG::generator);
}

template <typename T>
T HierRNG::zeroOne() {
	return HierRNG::uniform<T>(0, 1);
}

#endif
