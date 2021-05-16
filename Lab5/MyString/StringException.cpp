#include "StringException.h"

StringException::StringException(const std::string& msg) : m_msg(msg)
{
}

std::string StringException::GetMessage() const
{
    return(m_msg);
}
