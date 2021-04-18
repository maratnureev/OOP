#include "Exception.h"

InvalidChildException::InvalidChildException(const std::string& msg) : m_msg(msg)
{
}

std::string InvalidChildException::GetMessage() const
{
    return(m_msg);
}

InvalidParameterException::InvalidParameterException(const std::string& msg) : m_msg(msg)
{
}

std::string InvalidParameterException::GetMessage() const
{
    return(m_msg);
}