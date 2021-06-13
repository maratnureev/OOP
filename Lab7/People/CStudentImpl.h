#pragma once
#include "CPersonImpl.h"

template <typename Base>
class CStudentImpl : public CPersonImpl<Base>
{
public:
	CStudentImpl(std::string name, std::string surname, std::string middleName, std::string address, int studentIdNumber, std::string universityName)
		: CPersonImpl<Base>(name, surname, middleName, address)
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


