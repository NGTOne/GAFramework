#ifndef CORE_UTILS_HierRNG
#define CORE_UTILS_HierRNG
#include <random>
#include <vector>
#include <algorithm>
#include "../../exception/MismatchedCountsException.hpp"

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

	template <template<class...> class Cont, typename Val>
	static Val choose(Cont<Val> values);

	template <typename T>
	static T chooseWithProb(double probability, T first, T second);

	template <template<class...> class Cont, typename Val>
	static std::vector<Val> choose(
		Cont<Val> values,
		unsigned int count,
		bool unique = true
	);

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

template <template<class...> class Cont, typename Val>
Val HierRNG::choose(Cont<Val> values) {
	return *(values.begin() + HierRNG::index(values.size() - 1));
}

template <template<class...> class Cont, typename Val>
std::vector<Val> HierRNG::choose(
	Cont<Val> values,
	unsigned int count,
	bool unique
) {
	if (unique && count > values.size()) throw MismatchedCountsException("Trying to select too many items from container!");
	if (unique && count == values.size())
		return std::vector<Val>(values.begin(), values.end());
	if (count == 0) return std::vector<Val>();

	std::vector<Val> returnValues({HierRNG::choose(values)}), recur;
	if (unique) values.erase(
		std::find(values.begin(), values.end(), returnValues[0])
	);
	recur = HierRNG::choose(values, count - 1, unique);
	returnValues.insert(returnValues.end(), recur.begin(), recur.end());
	return returnValues;
}

template <typename T>
T HierRNG::chooseWithProb(double probability, T first, T second) {
	return HierRNG::zeroOne<double>() > probability ? first : second;
}

#endif
