#pragma once
#include "IPerson.h"

class IStudent : public IPerson
{
	virtual int GetStudentIdNumber() const = 0;
	virtual std::string GetUniversityName() const = 0;
};

