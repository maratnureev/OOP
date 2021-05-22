#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../MyString/CMyString.h"
#include "../MyString/StringException.h"

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

SCENARIO("Test operator [] right side")
{
	CMyString string1("Hello world");
	char letterH = string1[0];
	REQUIRE(letterH == 'H');
}

SCENARIO("Test const operator [] right side")
{
	const CMyString string1("Hello world");
	char letterH = string1[0];
	REQUIRE(letterH == 'H');
}

SCENARIO("Test operator [] left side")
{
	CMyString string1("Hello world");
	string1[0] = 'L';
	REQUIRE(string1[0] == 'L');
}

SCENARIO("Test self assignment")
{
	CMyString string1("Hello world");
	REQUIRE_THROWS(string1 = string1);
}

SCENARIO("Operator = test")
{
	CMyString string1;
	CMyString string2 = "Hello world";
	string1 = string2;
	REQUIRE(string1.GetLength() == 11);
	REQUIRE(memcmp(string1.GetStringData(), string2.GetStringData(), 11) == 0);
}

SCENARIO("test nullptr as char array in constructor")
{
	CMyString string(nullptr);
	REQUIRE(string.GetLength() == 0);
	REQUIRE(memcmp(string.GetStringData(), "", 1) == 0);
}

SCENARIO("test operator ==")
{
	CMyString string1("string");
	CMyString string2("string");
	REQUIRE(string1 == string2);
}

SCENARIO("test operator !=")
{
	CMyString string1("string");
	CMyString string2("string4");
	REQUIRE(string1 != string2);
}

SCENARIO("test operator >")
{
	CMyString string1("AAB");
	CMyString string2("AAA");
	REQUIRE(string1 > string2);
	CMyString string3("AAAA");
	CMyString string4("AAA");
	REQUIRE(string3 > string4);
	CMyString string5("AAA");
	CMyString string6("AAA");
	REQUIRE(!(string5 > string6));
}

SCENARIO("test operator <")
{
	CMyString string1("AAB");
	CMyString string2("AAA");
	REQUIRE(!(string1 < string2));
}

SCENARIO("test operator >=")
{
	CMyString string1("AAB");
	CMyString string2("AAA");
	REQUIRE(string1 >= string2);
	CMyString string3("AAA");
	CMyString string4("AAA");
	REQUIRE(string3 >= string4);
}

SCENARIO("test operator <=")
{
	CMyString string1("AAA");
	CMyString string2("AAAASD");
	REQUIRE(string1 <= string2);
	CMyString string3("AAA");
	CMyString string4("AAA");
	REQUIRE(string3 <= string4);
}

SCENARIO("test operator >>")
{
	CMyString string;
	std::istringstream input("Hello world");
	input >> string;
	REQUIRE(string.GetLength() == 11);
	REQUIRE(memcmp(string.GetStringData(), "Hello world", 11) == 0);
}