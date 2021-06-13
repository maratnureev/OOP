#pragma once
#include "CPersonImpl.h"
#include "IPerson.h"

class CPerson : public CPersonImpl<IPerson>
{
public:
    CPerson(std::string name, std::string surname, std::string middleName, std::string address) 
        : CPersonImpl(name, surname, middleName, address) {}
};
