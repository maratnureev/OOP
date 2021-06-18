#pragma once
#include "CStudentImpl.h"
#include "IAdvancedStudent.h"

class CAdvancedStudent : public CStudentImpl<IAdvancedStudent>
{
public:
	CAdvancedStudent(std::string const& name, std::string const& surname, std::string const& middleName, std::string const& address, int studentIdNumber, std::string const& universityName, std::string thesisSubject)
		: CStudentImpl(name, surname, middleName, address, studentIdNumber, universityName)
		, m_thesisSubject(thesisSubject)
	{}

	std::string GetThesisSubject() const
	{
		return m_thesisSubject;
	}

private:
	std::string m_thesisSubject;
};

