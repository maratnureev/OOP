#include <iostream>
#include <stdexcept>
#include "CHttpURL.h"
#include "CURLParsingError.h"

int main()
{
    std::string line;
    std::string protocol;
    int port = -1;
    std::string host;
    std::string document;
    while (std::getline(std::cin, line))
    {
        try
        {
            CHttpURL url(line);
            std::cout << url;
        }
        catch (std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;;
        }
    }
}
