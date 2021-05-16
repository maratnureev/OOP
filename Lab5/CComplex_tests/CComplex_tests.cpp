#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Complex/CComplex.h"

#include <string>
#include <sstream>

SCENARIO("Test valid empty complex creation")
{
	CComplex complex;
	REQUIRE(complex.Re() == 0);
	REQUIRE(complex.Im() == 0);
}

SCENARIO("Test valid complex with params creation")
{
	CComplex complex(1.2, 4.5);
	REQUIRE(complex.Re() == 1.2);
	REQUIRE(complex.Im() == 4.5);
}

SCENARIO("Test sum complex and complex")
{
	CComplex a(1.2, 4.5);
	CComplex b(1.2, 4.5);
	auto c = a + b;
	REQUIRE(c.Re() == 2.4);
	REQUIRE(c.Im() == 9);
}

SCENARIO("Test sum double and complex")
{
	double a = 1.2;
	CComplex b(1.2, 4.5);
	auto c = a + b;
	REQUIRE(c.Re() == 2.4);
	REQUIRE(c.Im() == 4.5);
}

SCENARIO("Test sum complex and double")
{
	double a = 1.2;
	CComplex b(1.2, 4.5);
	auto c = b + a;
	REQUIRE(c.Re() == 2.4);
	REQUIRE(c.Im() == 4.5);
}

SCENARIO("Test sub complex and complex")
{
	CComplex a(1.3, 4.7);
	CComplex b(1.2, 4.5);
	auto c = a - b;
	REQUIRE(fabs(c.Re() - 0.1) < DBL_EPSILON);
	REQUIRE(fabs(c.Im() - 0.2) < DBL_EPSILON);
}

SCENARIO("Test sub double and complex")
{
	double a = 1.2;
	CComplex b(1.2, 4.5);
	auto c = a - b;
	REQUIRE(c.Re() == 0);
	REQUIRE(c.Im() == 4.5);
}

SCENARIO("Test sub complex and double")
{
	double a = 1.2;
	CComplex b(1.2, 4.5);
	auto c = b - a;
	REQUIRE(c.Re() == 0);
	REQUIRE(c.Im() == 4.5);
}

SCENARIO("Test mult complex and complex")
{
	CComplex a(1.3, 4.7);
	CComplex b(1.2, 4.5);
	auto c = a * b;
	REQUIRE(fabs(c.Re() - (-19.59)) < 0.001);
	REQUIRE(fabs(c.Im() - 11.49) < 0.001);
}

SCENARIO("Test mult double and complex")
{
	double a = 1.2;
	CComplex b(1.2, 4.5);
	auto c = a * b;
	REQUIRE(fabs(c.Re() - 1.44) < 0.001);
	REQUIRE(fabs(c.Im() - 5.4) < 0.001);
}

SCENARIO("Test mult complex and double")
{
	double a = 1.2;
	CComplex b(1.2, 4.5);
	auto c = b * a;
	REQUIRE(fabs(c.Re() - 1.44) < 0.001);
	REQUIRE(fabs(c.Im() - 5.4) < 0.001);
}

SCENARIO("Test div complex and complex")
{
	CComplex a(1.3, 4.7);
	CComplex b(1.3, 4.7);
	auto c = a / b;
	REQUIRE(fabs(c.Re() - 1) < 0.001);
	REQUIRE(fabs(c.Im() - 0) < 0.001);
}

SCENARIO("Test div double and complex")
{
	double a = 1.2;
	CComplex b(1.2, 4.5);
	auto c = a / b;
	REQUIRE(fabs(c.Re() - 0.06639004149377593) < 0.001);
	REQUIRE(fabs(c.Im() - (-0.24896265560165975)) < 0.001);
}

SCENARIO("Test div complex and double")
{
	double a = 1.2;
	CComplex b(1.2, 4.5);
	auto c = b / a;
	REQUIRE(fabs(c.Re() - 1) < 0.001);
	REQUIRE(fabs(c.Im() - 3.75) < 0.001);
}

SCENARIO("Test unary +")
{
	CComplex b(1.2, 4.5);
	auto a = +b;
	REQUIRE(a.Re() == 1.2);
	REQUIRE(a.Im() == 4.5);
}

SCENARIO("Test unary -")
{
	CComplex b(1.2, 4.5);
	auto a = -b;
	REQUIRE(a.Re() == -1.2);
	REQUIRE(a.Im() == -4.5);
}

SCENARIO("Test +=")
{
	CComplex b(1.2, 4.5);
	CComplex a(1.2, 4.5);
	a += b;
	REQUIRE(a.Re() == 2.4);
	REQUIRE(a.Im() == 9);
}

SCENARIO("Test -=")
{
	CComplex a(1.3, 4.7);
	CComplex b(1.2, 4.5);
	a -= b;
	REQUIRE(fabs(a.Re() - 0.1) < DBL_EPSILON);
	REQUIRE(fabs(a.Im() - 0.2) < DBL_EPSILON);
}

SCENARIO("Test *=")
{
	CComplex a(1.3, 4.7);
	CComplex b(1.2, 4.5);
	a *= b;
	REQUIRE(fabs(a.Re() - (-19.59)) < 0.001);
	REQUIRE(fabs(a.Im() - 11.49) < 0.001);
}

SCENARIO("Test /=")
{
	CComplex a(1.3, 4.7);
	CComplex b(1.3, 4.7);
	a /= b;
	REQUIRE(fabs(a.Re() - 1) < 0.001);
	REQUIRE(fabs(a.Im() - 0) < 0.001);
}

SCENARIO("Test ==")
{
	CComplex a(1.3, 4.7);
	CComplex b(1.3, 4.7);
	REQUIRE(a == b);
}

SCENARIO("Test real part !=")
{
	CComplex a(1.2, 4.7);
	CComplex b(1.3, 4.7);
	REQUIRE(a != b);
}

SCENARIO("Test image part !=")
{
	CComplex a(1.2, 4.7);
	CComplex b(1.2, 4.6);
	REQUIRE(a != b);
}

SCENARIO("Test both parts !=")
{
	CComplex a(1.2, 4.7);
	CComplex b(1.3, 4.6);
	REQUIRE(a != b);
}