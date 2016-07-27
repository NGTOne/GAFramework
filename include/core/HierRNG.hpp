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
	T getUniformRandomNumber(T lower, T upper);
};

template <typename T>
T HierRNG::getUniformRandomNumber(T lower, T upper) {
	autoUniformDist<T> dist(lower, upper);
	return dist(HierRNG::generator);
}

#endif
