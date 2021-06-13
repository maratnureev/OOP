#pragma once
#include <string>

class IPerson
{
	virtual std::string GetName() const = 0;
	virtual std::string GetSurname() const = 0;
	virtual std::string GetMiddleName() const = 0;
	virtual std::string GetAddress() const = 0;
};


