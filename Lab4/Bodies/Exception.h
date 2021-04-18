#pragma once
#include <exception>
#include <string>

class InvalidChildException :
    public std::exception
{
public:
    InvalidChildException(const std::string& msg);

    std::string GetMessage() const;
private:
    std::string m_msg;
};

class InvalidParameterException :
    public std::exception
{
public:
    InvalidParameterException(const std::string& msg);

    std::string GetMessage() const;
private:
    std::string m_msg;
};

