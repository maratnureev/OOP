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
	auto primeSet = GeneratePrimeNumbersSet(0);

	REQUIRE(primeSet.empty());
}

SCENARIO("5761455 set size with upper bound 100000000")
{
	auto primeSet = GeneratePrimeNumbersSet(100000000);

	REQUIRE(primeSet.size() == 5761455);
}