#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../StringList/CStringList.h"
#include "../StringList/InvalidStringListException.h"

SCENARIO("Empty string list creation test")
{
	CStringList stringList;
	REQUIRE(stringList.GetSize() == 0);
}

SCENARIO("String list append test 1 element")
{
	CStringList stringList;
	stringList.Append("String for test");
	REQUIRE(stringList.GetBackElement() == "String for test");
	REQUIRE(stringList.GetSize() == 1);
}

SCENARIO("String list append test 2 element and iterator")
{
	CStringList stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	auto it = stringList.begin();
	REQUIRE(*it == "String for test 1");
	++it;
	REQUIRE(*it == "String for test 2");
	REQUIRE(stringList.GetSize() == 2);
}

SCENARIO("String list push forward test")
{
	CStringList stringList;
	stringList.Append("String for test 1");
	stringList.PushForward("String for test 2");
	auto it = stringList.begin();
	REQUIRE(*it == "String for test 2");
	++it;
	REQUIRE(*it == "String for test 1");
	REQUIRE(stringList.GetSize() == 2);
}

SCENARIO("String list clear test")
{
	CStringList stringList;
	stringList.Append("String for test 1");
	stringList.PushForward("String for test 2");
	stringList.Clear();
	REQUIRE_THROWS(stringList.GetBackElement());
	REQUIRE(stringList.GetSize() == 0);
}

SCENARIO("String list insert in the middle test")
{
	CStringList stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.begin();
	it++;
	REQUIRE_NOTHROW(stringList.insert("String for test 4", it));
	REQUIRE(*it == "String for test 4");
	REQUIRE(*stringList.begin() == "String for test 1");
	it++;
	REQUIRE(*it == "String for test 2");
	REQUIRE(stringList.GetSize() == 4);
}

SCENARIO("String list insert at the begin test")
{
	CStringList stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.begin();
	REQUIRE_NOTHROW(stringList.insert("String for test 4", it));
	REQUIRE(*it == "String for test 4");
	REQUIRE(*stringList.begin() == "String for test 4");
	++it;
	REQUIRE(*it == "String for test 1");
	REQUIRE(stringList.GetSize() == 4);
}

SCENARIO("String list insert at the end test")
{
	CStringList stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.end();
	REQUIRE_NOTHROW(stringList.insert("String for test 4", it));
	REQUIRE(*it == "String for test 4");
	auto newIt = stringList.begin();
	++newIt;
	++newIt;
	++newIt;
	REQUIRE(*newIt == "String for test 3");
	REQUIRE(stringList.GetSize() == 4);
}

SCENARIO("String list remove in the middle test")
{
	CStringList stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.begin();
	++it;
	REQUIRE_NOTHROW(stringList.remove(it));
	REQUIRE(*it == "String for test 3");
	REQUIRE(*stringList.begin() == "String for test 1");
	REQUIRE(stringList.GetSize() == 2);
}

SCENARIO("String list remove at the begin test")
{
	CStringList stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.begin();
	REQUIRE_NOTHROW(stringList.remove(it));
	REQUIRE(*it == "String for test 2");
	REQUIRE(*stringList.begin() == "String for test 2");
	REQUIRE(stringList.GetSize() == 2);
}

SCENARIO("String list remove at the end test")
{
	CStringList stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.end();
	REQUIRE_NOTHROW(stringList.remove(it));
	REQUIRE_THROWS(*it);
	REQUIRE(stringList.GetSize() == 2);
}

SCENARIO("Invalid insert test")
{
	CStringList stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.end();
	it++;
	REQUIRE_THROWS(stringList.insert("String for test 4", it));
}

SCENARIO("Invalid remove test")
{
	CStringList stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.end();
	it++;
	REQUIRE_THROWS(stringList.remove(it));
} 