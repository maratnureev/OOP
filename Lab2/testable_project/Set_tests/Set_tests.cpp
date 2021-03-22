#include <vector>
#include <string>
#include <map>
#include <iosfwd>


#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Set/PrimeNumbers.h"

using namespace std;

SCENARIO("Empty set with upper bound 0")
{
	bool wasError = false;
	auto primeSet = GeneratePrimeNumbersSet(0, wasError);

	REQUIRE(primeSet.empty());
}

#ifdef NDEBUG
SCENARIO("5761455 set size with upper bound 100000000")
{
	bool wasError = false;
	auto primeSet = GeneratePrimeNumbersSet(100000000, wasError);

	REQUIRE(primeSet.size() == 5761455);
}
#endif

SCENARIO("Upper bound is 100 check prime set")
{
	bool wasError = false;
	auto primeSet = GeneratePrimeNumbersSet(97, wasError);

	set<int> expectedSet = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

	REQUIRE(primeSet == expectedSet);
}

SCENARIO("Upper bound 100000001 more than maximum")
{
	bool wasError = false;
	auto primeSet = GeneratePrimeNumbersSet(100000001, wasError);

	REQUIRE(wasError);
}