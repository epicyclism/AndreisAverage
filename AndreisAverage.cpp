// AndreisAverage.cpp

#include <iostream>
#include <iterator>
#include <type_traits>
#include <numeric>
#include <list>

template<typename S, typename D, typename I>
auto average(I b, I e)
{
	using E = typename std::iterator_traits<I>::value_type;
	if constexpr (std::is_same<std::iterator_traits<I>::iterator_category, std::random_access_iterator_tag>::value)
		return std::accumulate(b, e, S(0)) / D(e - b);
	else
	{
		std::size_t n = 0;
		auto s = std::accumulate(b, e, S(0), [&n](auto l, auto r) { ++n; return l + r; });
		return s / D(n);
	}
}

template <typename I>
auto average(I b, I e)
{
	using E = typename std::iterator_traits<I>::value_type;
	if constexpr (std::is_floating_point<E>::value)
		return average<E, E>(b, e);
	else
	if constexpr (std::is_integral<E>::value)
	{
		if constexpr (std::is_signed<E>::value)
			return average<long, double>(b, e);
		else
			return average<unsigned long, double>(b, e);
	}
	else // user defined
		return average<E, double>(b, e);
}

int main()
{
	      double   ad []{ 0.1, 0.2, 0.3, 0.4, 0.5 };
	      int      ai []{ 1, 2, 3, 4, 5 };
	const double   adc[]{ 0.1, 0.2, 0.3, 0.4, 0.5 };
	const unsigned auc[]{ 11, 21, 31, 41, 51 };
	std::list<int> al{ 1, 2, 3, 5, 7, 11, 13 };
	char ac[]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	std::cout << "      double : " << average(std::begin(ad), std::end(ad)) << "\n";
	std::cout << "      int    : " << average(std::begin(ai), std::end(ai)) << "\n";
	std::cout << "const double : " << average(std::begin(adc), std::end(adc)) << "\n";
	std::cout << "const int    : " << average(std::begin(auc), std::end(auc)) << "\n";
	std::cout << " list<int>   : " << average(std::begin(al), std::end(al)) << "\n";
	std::cout << "      cnar   : " << average(std::begin(ac), std::end(ac)) << "\n";
}
