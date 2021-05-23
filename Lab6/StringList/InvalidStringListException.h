#pragma once
#include <string>
#include <stdexcept>

class InvalidStringListException : public std::invalid_argument
{
public:
    InvalidStringListException(const std::string& msg);
};
