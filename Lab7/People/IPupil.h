#pragma once
#include "IPerson.h"

class IPupil : public IPerson
{
	virtual int GetSchoolNumber() const = 0;
	virtual std::string GetSchoolClass() const = 0;
};

