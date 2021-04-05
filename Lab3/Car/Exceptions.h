#pragma once
#include <exception>
#include <string>

class InvalidSpeedException :
    public std::exception
{
public:
    InvalidSpeedException(const std::string& msg);

    std::string GetMessage() const;
private:
    std::string m_msg;
};

class InvalidGearException :
    public std::exception
{
public:
    InvalidGearException(const std::string& msg);

    std::string GetMessage() const;
private:
    std::string m_msg;
};

class InvalidEngineOffStateException :
    public std::exception
{
public:
    InvalidEngineOffStateException(const std::string& msg);

    std::string GetMessage() const;
private:
    std::string m_msg;
};