#pragma once
#include "CPersonImpl.h"
#include "IPerson.h"

class CWorker : public CPersonImpl<IPerson>
{
public:
	CWorker(std::string name, std::string surname, std::string middleName, std::string address, std::string specialty)
	: CPersonImpl(name, surname, middleName, address) {}

	std::string GetSpecialty()
	{
		return m_specialty;
	}

private:
	std::string m_specialty;
};

