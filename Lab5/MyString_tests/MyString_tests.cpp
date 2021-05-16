#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../MyString/CMyString.h"

#include <string>
#include <sstream>

SCENARIO("Test empty valid string creation")
{
	CMyString string;
	auto expected = new char[1];
	expected[0] = '\0';
	REQUIRE(string.GetLength() == 0);
	REQUIRE(memcmp(string.GetStringData(), "", 1) == 0);
}

SCENARIO("Test char constructor valid string creation")
{
	CMyString string("Hello");
	REQUIRE(string.GetLength() == 5);
	REQUIRE(memcmp(string.GetStringData(), "Hello", 6) == 0);
}

SCENARIO("Test string constructor valid string creation")
{
	std::string expected = "Hello";
	CMyString string(expected);
	REQUIRE(string.GetLength() == 5);
	REQUIRE(memcmp(string.GetStringData(), "Hello", 6) == 0);
}

SCENARIO("Test copy constructor")
{
	std::string expected = "Hello";
	CMyString string(expected);
	CMyString copyString = string;
	REQUIRE(copyString.GetLength() == 5);
	REQUIRE(memcmp(copyString.GetStringData(), "Hello", 6) == 0);
}

SCENARIO("Test move constructor")
{
	std::string expected = "Hello";
	CMyString string(expected);
	CMyString moveString = std::move(string);
	REQUIRE(moveString.GetLength() == 5);
	REQUIRE(memcmp(moveString.GetStringData(), "Hello", 6) == 0);
}

SCENARIO("Test substring")
{
	CMyString string("Hello\0world", 11);
	CMyString subString = string.SubString(6, 5);
	REQUIRE(subString.GetLength() == 5);
	REQUIRE(memcmp(subString.GetStringData(), "world", 6) == 0);
}

SCENARIO("Test clear")
{
	CMyString string("Hello\0world", 11);
	string.Clear();
	REQUIRE(string.GetLength() == 0);
	REQUIRE(memcmp(string.GetStringData(), "", 1) == 0);
}

SCENARIO("Test + MyString with MyString")
{
	CMyString string1("Hello");
	CMyString string2(" world");
	CMyString string3 = string1 + string2;
	REQUIRE(string3.GetLength() == 11);
	REQUIRE(memcmp(string3.GetStringData(), "Hello world", 11) == 0);
}

SCENARIO("Test + string with MyString")
{
	std::string string1 = "Hello";
	CMyString string2(" world");
	CMyString string3 = string1 + string2;
	REQUIRE(string3.GetLength() == 11);
	REQUIRE(memcmp(string3.GetStringData(), "Hello world", 11) == 0);
}

SCENARIO("Test + char* with MyString")
{
	CMyString string2(" world");
	CMyString string3 = "Hello" + string2;
	REQUIRE(string3.GetLength() == 11);
	REQUIRE(memcmp(string3.GetStringData(), "Hello world", 11) == 0);
}

SCENARIO("Test operator []")
{
	CMyString string1("Hello world");
	char letterH = string1[0];
	REQUIRE(letterH == 'H');
}

SCENARIO("Test self assignment")
{
	CMyString string1("Hello world");
	REQUIRE_THROWS(CMyString(string1));
}