#include <iostream>
#include "URLParser.h"
#include <string>

int main()
{
    std::string line;
    std::string protocol;
    int port = -1;
    std::string host;
    std::string document;
    while (std::getline(std::cin, line))
    {
        bool isValidUrl = false;
        isValidUrl = ParseURL(line, protocol, port, host, document);
        if (!isValidUrl)
            std::cout << "URL is invalid" << std::endl;
        else
            WriteURLParts(line, protocol, port, host, document);
    }
}