#pragma once
#include "IStudent.h"

class IAdvancedStudent : public IStudent
{
	virtual std::string GetThesisSubject() const = 0;
};

