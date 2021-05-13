#include "CCone.h"

CCone::CCone(double baseRadius, double height, double density)
	: CBody("Cone", density) 
	, m_height(height)
	, m_baseRadius(baseRadius)
{
	AssertBodyParameterValid(height);
	AssertBodyParameterValid(baseRadius);
	//TODO
	AssertBodyParameterValid(density);
}

double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCone::GetVolume() const
{
	return pow(m_baseRadius, 2) * 3.14 * m_height / 3;
}

void CCone::AppendProperties(std::ostream& strm) const
{
	strm << "\tbaseRadius= " << GetBaseRadius() << std::endl
		<< "\theight = " << GetHeight() << std::endl;
}