#pragma once
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS
};

class CHttpURL
{
public:
	CHttpURL(std::string const& url);
	CHttpURL(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP
	);
	CHttpURL(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		int port
	);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	int GetPort() const;
	friend std::ostream& operator<<(std::ostream& Str, CHttpURL const& v);


private:
	std::string m_url;
	std::string m_document;
	std::string m_domain;
	Protocol m_protocol;
	int m_port;
	
	void ParseURL(std::string const& url);
	std::string BuildURL() const;

	static std::string CompleteDocument(const std::string& document);
	static int GetPortByProtocol(Protocol protocol);
	static Protocol GetProtocolByString(std::string protocol);
	static std::string GetStringByProtocol(Protocol protocol);

	static void AssertValidDomain(const std::string& domain);
	static void AssertValidPort(const int port);
};


