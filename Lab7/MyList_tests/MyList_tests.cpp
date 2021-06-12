#define CATCH_CONFIG_MAIN
#include <string>
#include <vector>

#include "../../catch2/catch.hpp"

#include "../CMyList/CMyList.h"
#include "../CMyList/InvalidListException.h"

SCENARIO("Empty string list creation test")
{
	CMyList<std::string> stringList;
	REQUIRE(stringList.GetSize() == 0);
}

SCENARIO("String list append test 1 element")
{
	CMyList<std::string> stringList;
	stringList.Append("String for test");
	REQUIRE(stringList.GetBackElement() == "String for test");
	REQUIRE(stringList.GetSize() == 1);
}

SCENARIO("String list append test 2 element and iterator")
{
	CMyList<std::string> stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	auto it = stringList.begin();
	REQUIRE(*it == "String for test 1");
	++it;
	REQUIRE(*it == "String for test 2");
	REQUIRE(stringList.GetSize() == 2);
}

SCENARIO("String list push to empty list")
{
	CMyList<std::string> stringList;
	stringList.PushForward("String for test 2");
	auto it = stringList.begin();
	REQUIRE(*it == "String for test 2");
	REQUIRE(stringList.GetSize() == 1);
}

SCENARIO("String list push forward test")
{
	CMyList<std::string> stringList;
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
	CMyList<std::string> stringList;
	stringList.Append("String for test 1");
	stringList.PushForward("String for test 2");
	stringList.Clear();
	REQUIRE_THROWS(stringList.GetBackElement());
	REQUIRE(stringList.GetSize() == 0);
}

SCENARIO("String list Insert in the middle test")
{
	CMyList<std::string> stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.begin();
	it++;
	REQUIRE_NOTHROW(stringList.Insert("String for test 4", it));
	REQUIRE(*it == "String for test 4");
	REQUIRE(*stringList.begin() == "String for test 1");
	it++;
	REQUIRE(*it == "String for test 2");
	REQUIRE(stringList.GetSize() == 4);
}

SCENARIO("String list Insert at the begin test")
{
	CMyList<std::string> stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.begin();
	REQUIRE_NOTHROW(stringList.Insert("String for test 4", it));
	REQUIRE(*it == "String for test 4");
	REQUIRE(*stringList.begin() == "String for test 4");
	++it;
	REQUIRE(*it == "String for test 1");
	REQUIRE(stringList.GetSize() == 4);
}

SCENARIO("String list Insert at the end test")
{
	CMyList<std::string> stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.end();
	REQUIRE_NOTHROW(stringList.Insert("String for test 4", it));
	REQUIRE(*it == "String for test 4");
	auto newIt = stringList.begin();
	++newIt;
	++newIt;
	++newIt;
	REQUIRE(*newIt == "String for test 3");
	REQUIRE(stringList.GetSize() == 4);
}

SCENARIO("String list Remove in the middle test")
{
	CMyList<std::string> stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.begin();
	++it;
	REQUIRE_NOTHROW(stringList.Remove(it));
	REQUIRE(*it == "String for test 3");
	REQUIRE(*stringList.begin() == "String for test 1");
	REQUIRE(stringList.GetSize() == 2);
}

SCENARIO("String list Remove at the begin test")
{
	CMyList<std::string> stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.begin();
	REQUIRE_NOTHROW(stringList.Remove(it));
	REQUIRE(*it == "String for test 2");
	REQUIRE(*stringList.begin() == "String for test 2");
	REQUIRE(stringList.GetSize() == 2);
}

SCENARIO("String list Remove at the end test")
{
	CMyList<std::string> stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.end();
	REQUIRE_NOTHROW(stringList.Remove(it));
	REQUIRE_THROWS(*it);
	REQUIRE(stringList.GetSize() == 2);
}

SCENARIO("Invalid Insert test")
{
	CMyList<std::string> stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.end();
	it++;
	REQUIRE_THROWS(stringList.Insert("String for test 4", it));
}

SCENARIO("Invalid Remove test")
{
	CMyList<std::string> stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	auto it = stringList.end();
	it++;
	REQUIRE_THROWS(stringList.Remove(it));
}

SCENARIO("Get back element test")
{
	CMyList<std::string> stringList;
	stringList.Append("String for test 1");
	stringList.Append("String for test 2");
	stringList.Append("String for test 3");
	REQUIRE(stringList.GetBackElement() == "String for test 3");
}

//integer test

SCENARIO("Empty integer list creation test")
{
	CMyList<int> intList;
	REQUIRE(intList.GetSize() == 0);
}

SCENARIO("integer list append test 1 element")
{
	CMyList<int> intList;
	intList.Append(1);
	REQUIRE(intList.GetBackElement() == 1);
	REQUIRE(intList.GetSize() == 1);
}

SCENARIO("integer list append test 2 element and iterator")
{
	CMyList<int> intList;
	intList.Append(1);
	intList.Append(2);
	auto it = intList.begin();
	REQUIRE(*it == 1);
	++it;
	REQUIRE(*it == 2);
	REQUIRE(intList.GetSize() == 2);
}

SCENARIO("integer list push to empty list")
{
	CMyList<int> intList;
	intList.PushForward(2);
	auto it = intList.begin();
	REQUIRE(*it == 2);
	REQUIRE(intList.GetSize() == 1);
}

SCENARIO("integer list push forward test")
{
	CMyList<int> intList;
	intList.Append(1);
	intList.PushForward(2);
	auto it = intList.begin();
	REQUIRE(*it == 2);
	++it;
	REQUIRE(*it == 1);
	REQUIRE(intList.GetSize() == 2);
}

SCENARIO("integer list clear test")
{
	CMyList<int> intList;
	intList.Append(1);
	intList.PushForward(2);
	intList.Clear();
	REQUIRE_THROWS(intList.GetBackElement());
	REQUIRE(intList.GetSize() == 0);
}

SCENARIO("integer list Insert in the middle test")
{
	CMyList<int> intList;
	intList.Append(1);
	intList.Append(2);
	intList.Append(3);
	auto it = intList.begin();
	it++;
	REQUIRE_NOTHROW(intList.Insert(4, it));
	REQUIRE(*it == 4);
	REQUIRE(*intList.begin() == 1);
	it++;
	REQUIRE(*it == 2);
	REQUIRE(intList.GetSize() == 4);
}

SCENARIO("integer list Insert at the begin test")
{
	CMyList<int> intList;
	intList.Append(1);
	intList.Append(2);
	intList.Append(3);
	auto it = intList.begin();
	REQUIRE_NOTHROW(intList.Insert(4, it));
	REQUIRE(*it == 4);
	REQUIRE(*intList.begin() == 4);
	++it;
	REQUIRE(*it == 1);
	REQUIRE(intList.GetSize() == 4);
}

SCENARIO("integer list Insert at the end test")
{
	CMyList<int> intList;
	intList.Append(1);
	intList.Append(2);
	intList.Append(3);
	auto it = intList.end();
	REQUIRE_NOTHROW(intList.Insert(4, it));
	REQUIRE(*it == 4);
	auto newIt = intList.begin();
	++newIt;
	++newIt;
	++newIt;
	REQUIRE(*newIt == 3);
	REQUIRE(intList.GetSize() == 4);
}

SCENARIO("integer list Remove in the middle test")
{
	CMyList<int> intList;
	intList.Append(1);
	intList.Append(2);
	intList.Append(3);
	auto it = intList.begin();
	++it;
	REQUIRE_NOTHROW(intList.Remove(it));
	REQUIRE(*it == 3);
	REQUIRE(*intList.begin() == 1);
	REQUIRE(intList.GetSize() == 2);
}

SCENARIO("integer list Remove at the begin test")
{
	CMyList<int> intList;
	intList.Append(1);
	intList.Append(2);
	intList.Append(3);
	auto it = intList.begin();
	REQUIRE_NOTHROW(intList.Remove(it));
	REQUIRE(*it == 2);
	REQUIRE(*intList.begin() == 2);
	REQUIRE(intList.GetSize() == 2);
}

SCENARIO("integer list Remove at the end test")
{
	CMyList<int> intList;
	intList.Append(1);
	intList.Append(2);
	intList.Append(3);
	auto it = intList.end();
	REQUIRE_NOTHROW(intList.Remove(it));
	REQUIRE_THROWS(*it);
	REQUIRE(intList.GetSize() == 2);
}