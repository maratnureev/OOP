#pragma once
#include "CPersonImpl.h"
#include "IStudent.h"

template <typename Base>
class CStudentImpl : public CPersonImpl<IStudent>
{
public:
	CStudentImpl(std::string const& name, std::string const& surname, std::string const& middleName, std::string const& address, int studentIdNumber, std::string const& universityName)
		: CPersonImpl(name, surname, middleName, address)
		, m_studentIdNumber(studentIdNumber)
		, m_universityName(universityName)
	{}

	int GetStudentIdNumber() const
	{
		return m_studentIdNumber;
	}

	std::string GetUniversityName() const
	{
		return m_universityName;
	}

private:
	int m_studentIdNumber;
	std::string m_universityName;
};


