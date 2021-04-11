#include "../../catch2/catch.hpp"

#include "../Calculator/CCalculator.h"
#include "../Calculator/CRemoteControl.h"
#include "../Calculator/Exceptions.h"

#include <string>
#include <sstream>

SCENARIO("Remote control handle function var test")
{
	CCalculator calc;
	std::string input = "var v1";
	std::istringstream iss(input);
	std::ostringstream oss;
	CRemoteControl CRemoteControl(calc, iss, oss);
	REQUIRE(CRemoteControl.HandleCommand());
}

SCENARIO("Remote control handle function let test")
{
	CCalculator calc;
	std::string input = "let v1=1";
	std::istringstream iss(input);
	std::ostringstream oss;
	CRemoteControl CRemoteControl(calc, iss, oss);
	REQUIRE(CRemoteControl.HandleCommand());
}

SCENARIO("Remote control handle function fn test")
{
	CCalculator calc;
	std::string input = "fn fn1=v1";
	std::istringstream iss(input);
	std::ostringstream oss;
	CRemoteControl CRemoteControl(calc, iss, oss);
	REQUIRE(CRemoteControl.HandleCommand());
}

SCENARIO("Remote control handle function print test")
{
	CCalculator calc;
	std::string input = "print v1";
	std::istringstream iss(input);
	std::ostringstream oss;
	CRemoteControl CRemoteControl(calc, iss, oss);
	REQUIRE(CRemoteControl.HandleCommand());
}

SCENARIO("Remote control handle function printVars test")
{
	CCalculator calc;
	std::string input = "printvars";
	std::istringstream iss(input);
	std::ostringstream oss;
	CRemoteControl CRemoteControl(calc, iss, oss);
	REQUIRE(CRemoteControl.HandleCommand());
}

SCENARIO("Remote control handle function printfns test")
{
	CCalculator calc;
	std::string input = "printfns";
	std::istringstream iss(input);
	std::ostringstream oss;
	CRemoteControl CRemoteControl(calc, iss, oss);
	REQUIRE(CRemoteControl.HandleCommand());
}

SCENARIO("Remote control non-exist function test")
{
	CCalculator calc;
	std::string input = "TVOn";
	std::istringstream iss(input);
	std::ostringstream oss;
	CRemoteControl CRemoteControl(calc, iss, oss);
	REQUIRE(!CRemoteControl.HandleCommand());
}
