#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../Bodies/CBody.h"
#include "../Bodies/CCompound.h"
#include "../Bodies/CCone.h"
#include "../Bodies/CSphere.h"
#include "../Bodies/CCylinder.h"
#include "../Bodies/CParallelepiped.h"
#include "../Bodies/Exception.h"
#include "../Bodies/BodiesController.h"

#include <string>
#include <sstream>

SCENARIO("Test valid sphere creation")
{
	CSphere sphere(10, 10);
	REQUIRE(sphere.GetDensity() == 10);
	REQUIRE(sphere.GetRadius() == 10);
	REQUIRE(sphere.GetMass() == 3.14 * 4 / 3 * pow(10, 3) * 10);
	REQUIRE(sphere.GetVolume() == 3.14 * 4 / 3 * pow(10, 3));
}

SCENARIO("Test invalid density sphere creation")
{
	REQUIRE_THROWS(CSphere(0, 10));
}

SCENARIO("Test invalid radius sphere creation")
{
	REQUIRE_THROWS(CSphere(10, 0));
}

SCENARIO("Test valid cone creation")
{
	CCone cone(10.1, 10.2, 10.3);
	REQUIRE(cone.GetDensity() == 10.3);
	REQUIRE(cone.GetBaseRadius() == 10.1);
	REQUIRE(cone.GetHeight() == 10.2);
	REQUIRE(abs(cone.GetMass()) - abs(3.14 * 1 / 3 * pow(10.1, 2) * 10.2 * 10.3) < 0.001);
	REQUIRE(abs(cone.GetVolume()) - abs(3.14 * 1 / 3 * pow(10.1, 2) * 10.2) < 0.001);
}

SCENARIO("Test invalid density cone creation")
{
	REQUIRE_THROWS(CCone(0, 10, 10));
}

SCENARIO("Test valid cylinder creation")
{
	CCylinder cylinder(10.1, 10.2, 10.3);
	REQUIRE(cylinder.GetDensity() == 10.3);
	REQUIRE(cylinder.GetBaseRadius() == 10.1);
	REQUIRE(cylinder.GetHeight() == 10.2);
	REQUIRE(abs(cylinder.GetMass()) - abs(3.14 * pow(10.1, 2) * 10.2 * 10.3) < 0.001);
	REQUIRE(abs(cylinder.GetVolume()) - abs(3.14 * pow(10.1, 2) * 10.2) < 0.001);
}

SCENARIO("Test invalid cylinder creation")
{
	REQUIRE_THROWS(CCylinder(0, 10, 10));
}

SCENARIO("Test valid parallelepiped creation")
{
	CParallelepiped paral(10.1, 10.2, 10.3, 10.4);
	REQUIRE(paral.GetDensity() == 10.4);
	REQUIRE(paral.GetDepth() == 10.3);
	REQUIRE(paral.GetWidth() == 10.1);
	REQUIRE(paral.GetHeight() == 10.2);
	REQUIRE(abs(paral.GetMass()) - abs(10.1 * 10.2 * 10.3 * 10.4) < 0.001);
	REQUIRE(abs(paral.GetVolume()) - abs(10.1 * 10.2 * 10.3) < 0.001);
}

SCENARIO("Test invalid parallelepiped creation")
{
	REQUIRE_THROWS(CParallelepiped(0, 10, 10, 0));
}

SCENARIO("Test empty compound creation")
{
	CCompound compound;
	REQUIRE(isnan(compound.GetDensity()));
}

SCENARIO("Test add child to compound")
{
	CCompound compound;
	auto cone = new CCone(10, 10, 10);
	REQUIRE_NOTHROW(compound.AddChildBody(cone));
	REQUIRE(compound.GetDensity() == 10);
	REQUIRE(compound.GetMass() == cone->GetMass());
	REQUIRE(compound.GetVolume() == cone->GetVolume());
}

SCENARIO("Test add straight recursive child to compound")
{
	auto compound = new CCompound;
	auto cone = new CCone(10, 10, 10);
	REQUIRE_THROWS(compound->AddChildBody(compound));
}

SCENARIO("Test add direct recursive child to compound")
{
	auto compound = new CCompound;
	REQUIRE_THROWS(compound->AddChildBody(compound));
}

SCENARIO("Test add indirect recursive child to compound")
{
	auto compound1 = new CCompound;
	auto compound2 = new CCompound;
	auto compound3 = new CCompound;
	compound3->AddChildBody(compound2);
	compound2->AddChildBody(compound1);
	REQUIRE_THROWS(compound1->AddChildBody(compound3));
}

SCENARIO("Test add cone bodies controller")
{
	std::string input = "AddCone A 10 10 10";
	std::istringstream in(input);
	std::string output;
	std::ostringstream out(output);
	BodiesController controller(in, out);
	REQUIRE(controller.HandleCommand());
}

SCENARIO("Test add sphere bodies controller")
{
	std::string input = "AddSphere A 10 10";
	std::istringstream in(input);
	std::string output;
	std::ostringstream out(output);
	BodiesController controller(in, out);
	REQUIRE(controller.HandleCommand());
}

SCENARIO("Test add cylinder bodies controller")
{
	std::string input = "AddCylinder A 10 10 10";
	std::istringstream in(input);
	std::string output;
	std::ostringstream out(output);
	BodiesController controller(in, out);
	REQUIRE(controller.HandleCommand());
}

SCENARIO("Test add parallelepiped bodies controller")
{
	std::string input = "AddParallelepiped A 10 10 10 10";
	std::istringstream in(input);
	std::string output;
	std::ostringstream out(output);
	BodiesController controller(in, out);
	REQUIRE(controller.HandleCommand());
}

SCENARIO("Test add compound bodies controller")
{
	std::string input = "AddCompound A";
	std::istringstream in(input);
	std::string output;
	std::ostringstream out(output);
	BodiesController controller(in, out);
	REQUIRE(controller.HandleCommand());
}

SCENARIO("Test add child to compound command handler") 
{
	std::string input = "AddChildToCompound A A";
	std::istringstream in(input);
	std::string output;
	std::ostringstream out(output);
	BodiesController controller(in, out);

	REQUIRE(controller.HandleCommand());
}

SCENARIO("Info test")
{
	std::string input = "Info";
	std::istringstream in(input);
	std::string output;
	std::ostringstream out(output);
	BodiesController controller(in, out);
}