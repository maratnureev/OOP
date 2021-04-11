#pragma once
#include <exception>
#include <string>

class InvalidArgumentException :
    public std::exception
{
public:
    InvalidArgumentException(const std::string& msg);

    std::string GetMessage() const;
private:
    std::string m_msg;
};

