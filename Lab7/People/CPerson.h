#pragma once
#include "CPersonImpl.h"
#include "IPerson.h"

class CPerson : public CPersonImpl<IPerson>
{
public:
    CPerson(std::string const& name, std::string const& surname, std::string const& middleName, std::string const& address)
        : CPersonImpl(name, surname, middleName, address) {}
};
