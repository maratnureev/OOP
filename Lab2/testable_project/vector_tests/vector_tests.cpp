#include <vector>

#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../vector/vector/vector.h"

SCENARIO("Handle empty vector return empty vector")
{
	std::vector<double> emptyVector;
	CalculateVector(emptyVector);
	bool isEmpty = emptyVector.empty();
	REQUIRE(isEmpty);
}

SCENARIO("Handle vector with same elements")
{
	std::vector<double> sameElemsVector = {3, 3, 3, 3, 3};
	CalculateVector(sameElemsVector);
	std::vector<double> expected = {9, 9, 9, 9, 9};
	REQUIRE(expected == sameElemsVector);
}