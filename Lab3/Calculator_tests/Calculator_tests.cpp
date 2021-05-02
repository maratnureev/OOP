#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../Calculator/CCalculator.h"
#include "../Calculator/Exceptions.h"

#include <string>
#include <sstream>

SCENARIO("Test variable creation")
{
	CCalculator calculator;
	std::string varName = "test_var";
	REQUIRE_NOTHROW(calculator.CreateVar(varName));
	
	REQUIRE(isnan(calculator.GetValueByName(varName)));
}

SCENARIO("Test set variable")
{
	CCalculator calculator;
	std::string varName = "test_var";
	REQUIRE_NOTHROW(calculator.SetVar(varName, 1.0));

	REQUIRE(calculator.GetValueByName(varName) == 1.0);
}

SCENARIO("Test set invalid variable")
{
	CCalculator calculator;
	std::string varName = "123testVar";
	REQUIRE_THROWS(calculator.SetVar(varName, 1.0));
}

SCENARIO("Test init variable with non-existed variable")
{
	CCalculator calculator;
	std::string varName = "test_var";
	REQUIRE_THROWS(calculator.SetVar(varName, "test_var2"));
}

SCENARIO("Test create variable with same name")
{
	CCalculator calculator;
	std::string varName = "test_var";
	calculator.SetVar(varName, 1.0);
	REQUIRE_THROWS(calculator.CreateVar(varName));

	REQUIRE(calculator.GetValueByName(varName) == 1.0);
}

SCENARIO("Test create variable with same fn name")
{
	CCalculator calculator;
	calculator.CreateFunction("test_fn", "var1", "var2", '+');
	REQUIRE_THROWS(calculator.CreateVar("test_fn"));
}

SCENARIO("Test create variable init with non-init var")
{
	CCalculator calculator;
	std::string varName = "test_var";
	REQUIRE_THROWS(calculator.SetVar(varName, "non-existent-var"));
}

SCENARIO("Test create function")
{
	CCalculator calculator;
	std::string fnName = "test_fn";
	REQUIRE_NOTHROW(calculator.CreateFunction(fnName, "var1", "var2", '+'));

	REQUIRE(isnan(calculator.GetValueByName(fnName)));
}

SCENARIO("Test user function sum")
{
	CCalculator calculator;
	std::string fnName = "test_fn";
	calculator.SetVar("var1", 1.2);
	calculator.SetVar("var2", 1.2);
	REQUIRE_NOTHROW(calculator.CreateFunction(fnName, "var1", "var2", '+'));

	REQUIRE(calculator.GetValueByName(fnName) == 1.2+1.2);
}

SCENARIO("Test user function sub")
{
	CCalculator calculator;
	std::string fnName = "test_fn";
	calculator.SetVar("var1", 1.4);
	calculator.SetVar("var2", 1.2);
	REQUIRE_NOTHROW(calculator.CreateFunction(fnName, "var1", "var2", '-'));

	REQUIRE(calculator.GetValueByName(fnName) == 1.4 - 1.2);
}

SCENARIO("Test user function div")
{
	CCalculator calculator;
	std::string fnName = "test_fn";
	calculator.SetVar("var1", 1.4);
	calculator.SetVar("var2", 1.2);
	REQUIRE_NOTHROW(calculator.CreateFunction(fnName, "var1", "var2", '/'));

	REQUIRE(calculator.GetValueByName(fnName) == 1.4 / 1.2);
}

SCENARIO("Test user function mult")
{
	CCalculator calculator;
	std::string fnName = "test_fn";
	calculator.SetVar("var1", 1.4);
	calculator.SetVar("var2", 1.2);
	REQUIRE_NOTHROW(calculator.CreateFunction(fnName, "var1", "var2", '*'));

	REQUIRE(calculator.GetValueByName(fnName) == 1.4 * 1.2);
}

SCENARIO("Test create function with user functions")
{
	CCalculator calculator;
	calculator.SetVar("var1", 1.4);
	calculator.SetVar("var2", 1.2);
	calculator.CreateFunction("fn1", "var1", "var2", '*');
	calculator.CreateFunction("fn2", "fn1", "var2", '*');
	calculator.CreateFunction("fn3", "var1", "fn2", '*');
	calculator.CreateFunction("fn4", "fn1", "fn2", '*');
	
	REQUIRE(calculator.GetValueByName("fn2") == 1.4 * 1.2 * 1.2);
	REQUIRE(calculator.GetValueByName("fn3") == 1.4 * 1.2 * 1.2 * 1.4);
	REQUIRE(calculator.GetValueByName("fn4") == 1.4 * 1.2 * 1.2 * 1.4 * 1.2);
}

SCENARIO("Test user function with 1 variable")
{
	CCalculator calculator;
	std::string fnName = "test_fn";
	calculator.SetVar("var1", 1.2);
	REQUIRE_NOTHROW(calculator.CreateFunction(fnName, "var1"));

	REQUIRE(calculator.GetValueByName(fnName) == 1.2);
}

SCENARIO("Test user function with 1 variable and change var value")
{
	CCalculator calculator;
	std::string fnName = "test_fn";
	calculator.SetVar("var1", 1.2);
	REQUIRE_NOTHROW(calculator.CreateFunction(fnName, "var1"));
	calculator.SetVar("var1", 1.4);

	REQUIRE(calculator.GetValueByName(fnName) == 1.4);
}

SCENARIO("Test set variable value by another variable")
{
	CCalculator calculator;
	std::string varName = "test_var";
	calculator.SetVar("var1", 1.2);
	REQUIRE_NOTHROW(calculator.SetVar(varName, "var1"));

	REQUIRE(calculator.GetValueByName(varName) == 1.2);
}

SCENARIO("Test set variable value by another variable and change after")
{
	CCalculator calculator;
	std::string varName = "test_var";
	calculator.SetVar("var1", 1.2);
	REQUIRE_NOTHROW(calculator.SetVar(varName, "var1"));
	calculator.SetVar("var1", 1.4);

	REQUIRE(calculator.GetValueByName(varName) == 1.2);
}

SCENARIO("Test set variable value by function value")
{
	CCalculator calculator;
	std::string varName = "test_var";
	calculator.SetVar("var1", 1.2);
	calculator.SetVar("var2", 1.4);
	calculator.CreateFunction("fn1", "var1", "var2", '+');
	REQUIRE_NOTHROW(calculator.SetVar(varName, "fn1"));

	REQUIRE(calculator.GetValueByName(varName) == 1.2+1.4);
}

SCENARIO("Test get all variables")
{
	CCalculator calculator;
	std::string varName = "test_var";
	calculator.SetVar("var1", 1.2);
	calculator.SetVar("var2", 1.4);
	calculator.SetVar("var3", 1.6);
	std::map<std::string, double> expectedMap;
	expectedMap["var1"] = 1.2;
	expectedMap["var2"] = 1.4;
	expectedMap["var3"] = 1.6;

	REQUIRE(calculator.GetVariableValueMap() == expectedMap);
}

SCENARIO("Test get all function values")
{
	CCalculator calculator;
	std::string varName = "test_var";
	calculator.SetVar("var1", 1.2);
	calculator.SetVar("var2", 1.4);
	calculator.SetVar("var3", 1.6);
	calculator.CreateFunction("fn1", "var1", "var2", '+');
	calculator.CreateFunction("fn2", "var2", "var3", '+');
	calculator.CreateFunction("fn3", "var3", "var1", '+');
	std::map<std::string, double> expectedMap;
	expectedMap["fn1"] = 1.2 + 1.4;
	expectedMap["fn2"] = 1.4 + 1.6;
	expectedMap["fn3"] = 1.6 + 1.2;

	REQUIRE(calculator.GetFunctionValueMap() == expectedMap);
}