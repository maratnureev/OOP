#include "InvalidListException.h"

InvalidListException::InvalidListException(const std::string& msg)
    : invalid_argument(msg)
{
}