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
	for (const auto& child : m_childs)
	{
		double childVolume = child->GetVolume();
		volume += childVolume;
	}
	return volume;
}

double CCompound::GetMass() const
{
	double mass = 0;
	for (const auto& child : m_childs)
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

void CCompound::AddChildBody(std::unique_ptr<CBody> child)
{
	AssertChildValid(child.get());
	m_childs.push_back(std::move(child));
}

void CCompound::AppendProperties(std::ostream& strm) const
{
	if (!m_childs.empty())
		strm << "\tCompound object:\n";
	for (const auto& appendedChild : m_childs)
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
	auto parentBody = dynamic_cast<CCompound*>(GetParentBody());
	if (parentBody != nullptr)
		parentBody->AssertChildValid(appendedChild);
}