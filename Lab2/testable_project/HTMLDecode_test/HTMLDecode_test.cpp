#include <vector>

#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../HTMLDecode/HTMLDecode/html.h"

SCENARIO("Handle empty string")
{
	std::string emptyString;
	REQUIRE(HtmlDecode(emptyString) == "");
}

SCENARIO("Handle string with all html characters")
{
	std::string htmlString = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	REQUIRE(HtmlDecode(htmlString) == "Cat <says> \"Meow\". M&M's");
}

SCENARIO("Handle string without html characters")
{
	std::string htmlString = "Just some string";
	REQUIRE(HtmlDecode(htmlString) == "Just some string");
}