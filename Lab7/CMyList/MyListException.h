#pragma once
#include <string>
#include <stdexcept>

class MyListException : public std::invalid_argument
{
public:
    MyListException(const std::string& msg);
};
