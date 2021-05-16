#pragma once
#include <exception>
#include <string>
class StringException :
    public std::exception
{
public:
    StringException(const std::string& msg);

    std::string GetMessage() const;
private:
    std::string m_msg;
};

