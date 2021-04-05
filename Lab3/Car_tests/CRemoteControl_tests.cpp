#include "../../catch2/catch.hpp"

#include "../Car/CCar.h"
#include "../Car/CRemoteControl.h"
#include "../Car/Exceptions.h"

#include <string>
#include <sstream>

SCENARIO("Remote control handle function EngineOn test")
{
	CCar car;
	std::string input = "EngineOn";
	std::istringstream iss(input);
	std::ostringstream oss;
	CRemoteControl CRemoteControl(car, iss, oss);
	REQUIRE(CRemoteControl.HandleCommand());
	std::string output;
	output = oss.str();
	REQUIRE(output == "Car's engine is turned on\n");
}

SCENARIO("Remote control handle function EngineOff test")
{
	CCar car;
	std::string input = "EngineOff";
	std::istringstream iss(input);
	std::ostringstream oss;
	CRemoteControl CRemoteControl(car, iss, oss);
	REQUIRE(CRemoteControl.HandleCommand());
}

SCENARIO("Remote control handle function Info test")
{
	CCar car;
	std::string input = "Info";
	std::istringstream iss(input);
	std::ostringstream oss;
	CRemoteControl CRemoteControl(car, iss, oss);
	REQUIRE(CRemoteControl.HandleCommand());
}

SCENARIO("Remote control handle function SetSpeed test")
{
	CCar car;
	std::string input = "SetSpeed 10";
	std::istringstream iss(input);
	std::ostringstream oss;
	CRemoteControl CRemoteControl(car, iss, oss);
	REQUIRE(CRemoteControl.HandleCommand());
}

SCENARIO("Remote control handle function SetGear test")
{
	CCar car;
	std::string input = "SetGear 2";
	std::istringstream iss(input);
	std::ostringstream oss;
	CRemoteControl CRemoteControl(car, iss, oss);
	REQUIRE(CRemoteControl.HandleCommand());
}

SCENARIO("Remote control non-exist function test")
{
	CCar car;
	std::string input = "TVOn";
	std::istringstream iss(input);
	std::ostringstream oss;
	CRemoteControl CRemoteControl(car, iss, oss);
	REQUIRE(!CRemoteControl.HandleCommand());
}
