#pragma once
#include <stdexcept>
#include <string>

class CURLParsingError : public std::invalid_argument
{
public:
    CURLParsingError(const std::string& msg);
};

