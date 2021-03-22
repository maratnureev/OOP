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

SCENARIO("Handle vector with int elements")
{	
	std::vector<double> inputVector = { -4, 2, 3, 5, 6 };
	CalculateVector(inputVector);
	std::vector<double> expected = { 16.0, -8.0, -12.0, -20.0, -24.0 };
	REQUIRE(expected == inputVector);
}

SCENARIO("Handle vector with float elements")
{
	std::vector<double> inputVector = { -4.4, 2.8, 3.3, 5.1, 6.1 };
	CalculateVector(inputVector);
	std::vector<double> expected = { 19.36, -12.32, -14.52, -22.44, -26.84 };
	auto roundValue{
			[](double firstMult) -> double
			{
				return round(firstMult * 1000) / 1000;
			}
	};
	transform(expected.begin(), expected.end(), expected.begin(), roundValue);
	REQUIRE(expected == inputVector);
}