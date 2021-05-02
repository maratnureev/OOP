#include "CBody.h"
#include "Exception.h"
#include <string>

CBody::CBody(const std::string& type, double density) 
	: m_density(density)
	, m_type(type)
	, m_parent(nullptr)
{
}

double CBody::GetDensity() const
{
	return m_density;
}

double CBody::GetMass() const
{
	return GetVolume() * GetDensity();
}

void CBody::SetParentBody(CBody* parent)
{
	if (m_parent != nullptr)
		throw InvalidParameterException("Body can have only 1 parent");
	m_parent = parent;
}

CBody* CBody::GetParentBody() const
{
	return m_parent;
}

std::string CBody::ToString() const
{
	std::ostringstream strm;
	strm << m_type << ":" << std::endl << std::setprecision(10)
		<< "\tdensity = " << GetDensity() << std::endl
		<< "\tvolume = " << GetVolume() << std::endl
		<< "\tmass = " << GetMass() << std::endl;
	AppendProperties(strm);
	return strm.str();
}

void CBody::AssertBodyParameterValid(const double param)
{
	if (param <= 0)
		throw InvalidParameterException("Invalid parameter: " + std::to_string(param));
}