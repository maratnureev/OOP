#pragma once
#include "CStudentImpl.h"
#include "IStudent.h"

class CStudent : public CStudentImpl<IStudent>
{
	CStudent(std::string name, std::string surname, std::string middleName, std::string address, int studentIdNumber, std::string universityName)
		: CStudentImpl(name, surname, middleName, address, studentIdNumber, universityName) {}
};

