#pragma once
#include "CStudentImpl.h"
#include "IStudent.h"

class CStudent : public CStudentImpl<IStudent>
{
	CStudent(std::string const& name, std::string const& surname, std::string const& middleName, std::string const& address, int studentIdNumber, std::string const& universityName)
		: CStudentImpl(name, surname, middleName, address, studentIdNumber, universityName) {}
};

