#pragma once
#include "IPerson.h"

class IWorker : public IPerson
{
	virtual std::string GetSpecialty() const = 0;
};

