#pragma once
#include "CPersonImpl.h"
#include "ITeacher.h"

class CTeacher : public CPersonImpl<ITeacher>
{
public:
	CTeacher(std::string const& name, std::string const& surname, std::string const& middleName, std::string const& address, std::string const& subject)
		: CPersonImpl(name, surname, middleName, address)
		, m_subject(subject)
	{}

	std::string GetSubject() const
	{
		return m_subject;
	}

private:
	std::string m_subject;
};
