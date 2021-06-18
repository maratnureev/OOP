#pragma once
#include "IPerson.h"

class ITeacher : public IPerson
{
	virtual std::string GetSubject() const = 0;
};

