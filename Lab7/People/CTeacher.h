#pragma once
#include "CPersonImpl.h"
#include "IPerson.h"

class CTeacher : public CPersonImpl<IPerson>
{
public:
	CTeacher(std::string name, std::string surname, std::string middleName, std::string address, std::string subject)
		: CPersonImpl(name, surname, middleName, address) {}

	std::string GetSubject()
	{
		return m_subject;
	}

private:
	std::string m_subject;
};
