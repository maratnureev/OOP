#include <string>
#include <iostream>
#include <iosfwd>
#include <regex>
#include "URLParser.h"

const std::regex urlRegex("(http[s]?|ftp)://([a-zA-Z0-9.]*)(:([0-9]+))?(/(.*))?");

bool AssertValidPort(const int port)
{
    if (port < 1 || port > 65535)
        return false;
    return true;
}

int GetPortByProtocol(std::string const& protocol)
{
    if (protocol == "http")
        return 80;
    if (protocol == "https")
        return 443;
    if (protocol == "ftp")
        return 21;
    return -1;
}

bool ParseURL(std::string const& url, std::string& protocol, int& port, std::string& host, std::string& document)
{
    std::smatch pieces_match;
    std::string strPort;
    port = -1;
    if (std::regex_match(url, pieces_match, urlRegex)) 
    {
        protocol = pieces_match[1].str();
        host = pieces_match[2].str();
        port = pieces_match[4].str() == "" ? -1 : stoi(pieces_match[4].str());
        document = pieces_match[6].str();
        if (port == -1)
            port = GetPortByProtocol(protocol);
        return AssertValidPort(port);
    }

    return false;
}

void WriteURLParts(std::string const& url, std::string& protocol, int& port, std::string& host, std::string& document)
{
    std::cout << url << std::endl;
    std::cout << "HOST: " << host << std::endl;
    std::cout << "PORT: " << port << std::endl;
    std::cout << "DOC: " << document << std::endl;
}