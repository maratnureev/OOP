#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../regex/URLParser.h"

SCENARIO("Valid url without port and document")
{
	std::string url = "http://www.mysite.com";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(isValid);
	REQUIRE(protocol == "http");
	REQUIRE(port == 80);
	REQUIRE(host == "www.mysite.com");
}

SCENARIO("Valid url with document but without port")
{
	std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(isValid);
	REQUIRE(protocol == "http");
	REQUIRE(port == 80);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

SCENARIO("Valid url with port and document")
{
	std::string url = "http://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(isValid);
	REQUIRE(protocol == "http");
	REQUIRE(port == 8000);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

SCENARIO("Valid url with port but without document")
{
	std::string url = "http://www.mysite.com:8000";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(isValid);
	REQUIRE(protocol == "http");
	REQUIRE(port == 8000);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "");
}

SCENARIO("Valid url with http protocol")
{
	std::string url = "http://www.mysite.com";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(isValid);
	REQUIRE(protocol == "http");
	REQUIRE(port == 80);
	REQUIRE(host == "www.mysite.com");
}

SCENARIO("Valid url with https protocol")
{
	std::string url = "https://www.mysite.com";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(isValid);
	REQUIRE(protocol == "https");
	REQUIRE(port == 443);
	REQUIRE(host == "www.mysite.com");
}

SCENARIO("Valid url with ftp protocol")
{
	std::string url = "ftp://www.mysite.com";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(isValid);
	REQUIRE(protocol == "ftp");
	REQUIRE(port == 21);
	REQUIRE(host == "www.mysite.com");
}

SCENARIO("Invalid url with invalid port")
{
	std::string url = "www.mysite.com:0";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(!isValid);
}

SCENARIO("Invalid url with invalid port 2")
{
	std::string url = "https://www.mysite.com:65536";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(!isValid);
}

SCENARIO("Invalid url with 2 ports")
{
	std::string url = "https://www.mysite.com:8000:123";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(!isValid);
}

SCENARIO("Invalid url with 2 protocols and 2 ports")
{
	std::string url = "https://https://www.mysite.com:8000:123";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(!isValid);
}

SCENARIO("Invalid url")
{
	std::string url = "https:///www.mysite.com:8000:123";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(!isValid);
}

SCENARIO("Valid url with capital protocol")
{
	std::string url = "HTTPS://www.mysite.com:8000";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(isValid);
}

SCENARIO("Valid port 1")
{
	std::string url = "HTTPS://www.mysite.com:1";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(isValid);
}

SCENARIO("Valid port 65535")
{
	std::string url = "HTTPS://www.mysite.com:65535";
	std::string host;
	int port = -1;
	std::string protocol;
	std::string document;
	bool isValid = ParseURL(url, protocol, port, host, document);
	REQUIRE(isValid);
}