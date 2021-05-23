#include "InvalidStringListException.h"

InvalidStringListException::InvalidStringListException(const std::string& msg)
    : invalid_argument(msg)
{
}
