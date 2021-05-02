#include "CCompound.h"
#include "CBody.h"
#include "Exception.h"
#include <algorithm>

CCompound::CCompound()
	: CBody("Compund", 0)
{
}

double CCompound::GetVolume() const
{
	double volume = 0;
	for (const auto child : m_childs)
	{
		double childVolume = child->GetVolume();
		volume += childVolume;
	}
	return volume;
}

double CCompound::GetMass() const
{
	double mass = 0;
	for (const auto child : m_childs)
	{
		double childMass = child->GetMass();
		mass += childMass;
	}
	return mass;
}

double CCompound::GetDensity() const
{
	return GetMass() / GetVolume();
}

std::vector<CBody*> CCompound::GetChilds() const
{
	return m_childs;
}


void CCompound::AddChildBody(CBody* child)
{
	AssertChildValid(child);
	m_childs.push_back(child);
}

void CCompound::AppendProperties(std::ostream& strm) const
{
	strm << "\tCompound object:\n";
	for (const auto appendedChild : m_childs)
	{
		strm << "\t" << appendedChild->ToString();
	}
}

void CCompound::AssertChildValid(CBody* appendedChild) const
{
	CCompound* appendedCompoundBody = dynamic_cast<CCompound*>(appendedChild);
	if (appendedCompoundBody == nullptr)
		return;
	if (appendedChild == this)
		throw InvalidChildException(std::string("Can not append object as it's child"));
	for (auto child : appendedCompoundBody->GetChilds())
	{
		AssertChildValid(child);
	}
}