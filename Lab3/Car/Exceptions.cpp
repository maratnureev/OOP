#include "Exceptions.h"
#include <exception>
#include <string>

InvalidSpeedException::InvalidSpeedException(const std::string& msg) : m_msg(msg) 
{
}

std::string InvalidSpeedException::GetMessage() const 
{ 
    return(m_msg); 
}

InvalidGearException::InvalidGearException(const std::string& msg) : m_msg(msg) 
{
}

std::string InvalidGearException::GetMessage() const 
{ 
    return(m_msg); 
}

InvalidEngineOffStateException::InvalidEngineOffStateException(const std::string& msg) : m_msg(msg) 
{
}

std::string InvalidEngineOffStateException::GetMessage() const 
{ 
    return(m_msg); 
}
