#pragma once
#include "CPersonImpl.h"
#include "IWorker.h"

class CWorker : public CPersonImpl<IWorker>
{
public:
	CWorker(std::string const& name, std::string const& surname, std::string const& middleName, std::string const& address, std::string const& specialty)
	: CPersonImpl(name, surname, middleName, address) 
	, m_specialty(specialty)
	{}

	std::string GetSpecialty() const
	{
		return m_specialty;
	}

private:
	std::string m_specialty;
};

