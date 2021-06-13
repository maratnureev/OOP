#pragma once
#include "CStudentImpl.h"
#include "IStudent.h"

class CAdvancedStudent : public CStudentImpl<IStudent>
{
public:
	CAdvancedStudent(std::string name, std::string surname, std::string middleName, std::string address, int studentIdNumber, std::string universityName, std::string thesisSubject)
		: CStudentImpl(name, surname, middleName, address, studentIdNumber, universityName)
		, m_thesisSubject(thesisSubject)
	{}
private:
	std::string m_thesisSubject;
};

