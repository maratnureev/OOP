#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../HttpURL/CHttpURL.h"
#include "../HttpURL./CURLParsingError.h"

SCENARIO("Valid url creation by string creation")
{
	std::string url = "http://www.mysite.com";
	REQUIRE_NOTHROW(CHttpURL(url));
	CHttpURL httpUrl(url);
	REQUIRE(httpUrl.GetURL() == "http://www.mysite.com");
	REQUIRE(httpUrl.GetProtocol() == Protocol::HTTP);
	REQUIRE(httpUrl.GetPort() == 80);
	REQUIRE(httpUrl.GetDomain() == "www.mysite.com");
	REQUIRE(httpUrl.GetDocument() == "");
}

SCENARIO("Valid url creation by params without port creation")
{
	std::string url = "http://www.mysite.com" ;
	REQUIRE_NOTHROW(CHttpURL("www.mysite.com", "", Protocol::HTTP));
	CHttpURL httpUrl("www.mysite.com", "document", Protocol::HTTP);
	REQUIRE(httpUrl.GetURL() == "http://www.mysite.com/document");
	REQUIRE(httpUrl.GetProtocol() == Protocol::HTTP);
	REQUIRE(httpUrl.GetPort() == 80);
	REQUIRE(httpUrl.GetDomain() == "www.mysite.com");
	REQUIRE(httpUrl.GetDocument() == "/document");
}

SCENARIO("Valid url creation by params with port creation")
{
	std::string url = "http://www.mysite.com:400";
	REQUIRE_NOTHROW(CHttpURL("www.mysite.com", "", Protocol::HTTP, 400));
	CHttpURL httpUrl("www.mysite.com", "", Protocol::HTTP, 400);
	REQUIRE(httpUrl.GetURL() == "http://www.mysite.com:400");
	REQUIRE(httpUrl.GetProtocol() == Protocol::HTTP);
	REQUIRE(httpUrl.GetPort() == 400);
	REQUIRE(httpUrl.GetDomain() == "www.mysite.com");
	REQUIRE(httpUrl.GetDocument() == "");
}

SCENARIO("Valid url with document")
{
	std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	REQUIRE_NOTHROW(CHttpURL(url));
	CHttpURL httpUrl(url);

	REQUIRE(httpUrl.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
}

SCENARIO("Valid url with port and document")
{
	std::string url = "http://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
	REQUIRE_NOTHROW(CHttpURL(url));
	CHttpURL httpUrl(url);
	REQUIRE(httpUrl.GetPort() == 8000);
	REQUIRE(httpUrl.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
}


SCENARIO("Valid url with port but without document")
{
	std::string url = "http://www.mysite.com:8000";
	REQUIRE_NOTHROW(CHttpURL(url));

	REQUIRE_NOTHROW(CHttpURL("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 8000));
}

SCENARIO("Valid url with http protocol")
{
	std::string url = "http://www.mysite.com:8000";
	REQUIRE_NOTHROW(CHttpURL(url));
	CHttpURL httpUrl(url);

	REQUIRE(httpUrl.GetProtocol() == Protocol::HTTP);
}

SCENARIO("Valid url with https protocol")
{
	std::string url = "https://www.mysite.com";
	REQUIRE_NOTHROW(CHttpURL(url));
	CHttpURL httpUrl(url);

	REQUIRE(httpUrl.GetProtocol() == Protocol::HTTPS);
}


SCENARIO("Invalid url with invalid port")
{
	std::string url = "http://www.mysite.com:0";
	REQUIRE_THROWS(CHttpURL(url));
}

SCENARIO("Invalid url with invalid port 2")
{
	std::string url = "https://www.mysite.com:65536";
	REQUIRE_THROWS(CHttpURL(url));
}

SCENARIO("Invalid url with 1 protocol")
{
	std::string url = "http://www.mysite.com:1";
	REQUIRE_NOTHROW(CHttpURL(url));
}

SCENARIO("Invalid url with 65535 protocol")
{
	std::string url = "https://www.mysite.com:65535";
	REQUIRE_NOTHROW(CHttpURL(url));
}

SCENARIO("Invalid url with 2 ports")
{
	std::string url = "https://www.mysite.com:8000:123";
	REQUIRE_THROWS(CHttpURL(url));
}

SCENARIO("Invalid url with 2 protocols and 2 ports")
{
	std::string url = "https://https://www.mysite.com:8000:123";
	REQUIRE_THROWS(CHttpURL(url));
}

SCENARIO("Valid url with capital protocol")
{
	std::string url = "HTTPS://www.mysite.com:8000";
	REQUIRE_NOTHROW(CHttpURL(url));
}