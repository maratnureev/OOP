#pragma once
#include "CPersonImpl.h"

template <typename Base>
class CPupil : public CPersonImpl<Base>
{
public:
	CPupil(std::string name, std::string surname, std::string middleName, std::string address, int schoolNumber, std::string schoolClass)
		: CPersonImpl(name, surname, middleName, address)
		, m_schoolNumber(schoolNumber)
		, m_schoolClass(schoolClass)
	{}
	
	int GetSchoolNumber() const
	{
		return m_schoolNumber;
	}

	std::string GetSchoolClass() const
	{
		return m_schoolClass;
	}

private:
	int m_schoolNumber;
	std::string m_schoolClass;
};


