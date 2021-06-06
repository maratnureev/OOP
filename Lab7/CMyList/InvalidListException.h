#pragma once
#include <string>
#include <stdexcept>

class InvalidListException : public std::invalid_argument
{
public:
    InvalidListException(const std::string& msg);
};
