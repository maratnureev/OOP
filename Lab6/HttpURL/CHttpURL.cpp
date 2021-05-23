#include "CURLParsingError.h"
#include "CHttpURL.h"
#include <string>
#include <iostream>
#include <iosfwd>
#include <regex>

const std::regex URL_REGEX("(http[s]?)://([a-zA-Z0-9.]+)(:([0-9]+))?(/(.*))?");
const std::regex DOMAIN_REGEX("[a-zA-Z0-9.]+");

const int MAX_PORT = 65535;
const int MIN_PORT = 1;
const int HTTP_PORT = 80;
const int HTTPS_PORT = 443;


CHttpURL::CHttpURL(std::string const& url)
    : m_port(-1)
    , m_protocol(Protocol::HTTP)
    , m_domain("")
    , m_document("")
    , m_url("")
{
    ParseURL(url);
}

CHttpURL::CHttpURL(std::string const& domain, std::string const& document, Protocol protocol)
{
    AssertValidDomain(domain);
    m_domain = domain;
    m_document = CompleteDocument(document);
    m_protocol = protocol;
    m_port = GetPortByProtocol(protocol);
    m_url = BuildURL();
}

CHttpURL::CHttpURL(std::string const& domain, std::string const& document, Protocol protocol, int port)
{
    AssertValidDomain(domain);
    m_domain = domain;
    m_document = CompleteDocument(document);
    m_protocol = protocol;
    m_port = port;
    m_url = BuildURL();
}

std::string CHttpURL::GetURL() const
{
	return m_url;
}

std::string CHttpURL::GetDomain() const
{
	return m_domain;
}

std::string CHttpURL::GetDocument() const
{
	return m_document;
}

Protocol CHttpURL::GetProtocol() const
{
	return m_protocol;
}

int CHttpURL::GetPort() const
{
	return m_port;
}

void CHttpURL::ParseURL(std::string const& url)
{
    std::string lowerUrl = url;
    std::transform(lowerUrl.begin(), lowerUrl.end(), lowerUrl.begin(), ::tolower);
    std::smatch piecesMatch;
    std::string strPort;
    int port = -1;
    if (std::regex_match(lowerUrl, piecesMatch, URL_REGEX))
    {
        m_url = url;
        m_protocol = GetProtocolByString(piecesMatch[1].str());
        m_domain = piecesMatch[2].str();
        port = piecesMatch[4].str() == "" ? -1 : stoi(piecesMatch[4].str());
        m_document = piecesMatch[5].str();
        if (port == -1)
            port = GetPortByProtocol(m_protocol);
        AssertValidPort(port);
        m_port = port;
        return;
    }

    throw CURLParsingError("Invalid url: " + url);
}


void CHttpURL::AssertValidPort(const int port) const
{
    if (port < MIN_PORT || port > MAX_PORT)
        throw std::invalid_argument("Invalid port");
}

void CHttpURL::AssertValidDomain(const std::string& domain) const
{
    if (!std::regex_match(domain, DOMAIN_REGEX))
        throw std::invalid_argument("Invalid domain: " + domain);
}

Protocol CHttpURL::GetProtocolByString(std::string protocol) const
{
    if (protocol == "http")
        return Protocol::HTTP;
    return Protocol::HTTPS;
}

int CHttpURL::GetPortByProtocol(Protocol protocol) const
{
    if (protocol == Protocol::HTTP)
        return HTTP_PORT;
    return HTTPS_PORT;
}

std::string CHttpURL::CompleteDocument(const std::string& document) const
{
    if (document != "" && document[0] != '/')
        return "/" + document;
    return document;
}   

std::string CHttpURL::BuildURL() const
{
    std::string stringProtocol = GetStringByProtocol(m_protocol);
    if (m_port == HTTP_PORT || m_port == HTTPS_PORT)
        return stringProtocol + "://" + m_domain + m_document;
    return stringProtocol + "://" + m_domain + m_document + ":" + std::to_string(m_port) + m_document;
}

std::string CHttpURL::GetStringByProtocol(Protocol protocol) const
{
    if (protocol == Protocol::HTTP)
        return "http";
    return "https";
}

std::ostream& operator<<(std::ostream& out, CHttpURL const& a) 
{
    out << a.m_url << std::endl;
    out << "HOST: " << a.m_domain << std::endl;
    out << "PORT: " << a.m_port << std::endl;
    out << "DOC: " << a.m_document << std::endl;

    return out;
}