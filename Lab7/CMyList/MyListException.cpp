#include "MyListException.h"

MyListException::MyListException(const std::string& msg)
    : invalid_argument(msg)
{
}
