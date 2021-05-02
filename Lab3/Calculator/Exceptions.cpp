#include "Exceptions.h"
#include <exception>
#include <string>

InvalidArgumentException::InvalidArgumentException(const std::string& msg) : m_msg(msg)
{
}

std::string InvalidArgumentException::GetMessage() const
{
    return m_msg;
}
