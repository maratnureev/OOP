#pragma once
#include "CPersonImpl.h"
#include "IPupil.h"

template <typename Base>
class CPupil : public CPersonImpl<IPupil>
{
public:
	CPupil(std::string const& name, std::string const& surname, std::string const& middleName, std::string const& address, int schoolNumber, std::string const& schoolClass)
		: CPersonImpl<Base>(name, surname, middleName, address)
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


