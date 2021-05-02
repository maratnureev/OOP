#include "CCylinder.h"

CCylinder::CCylinder(double baseRadius, double height, double density)
	: CBody("Cylinder", density)
	, m_height(height)
	, m_baseRadius(baseRadius)
{
	AssertBodyParameterValid(height);
	AssertBodyParameterValid(baseRadius);
	AssertBodyParameterValid(density);
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCylinder::GetVolume() const
{
	return pow(m_baseRadius, 2) * 3.14 * m_height;
}

void CCylinder::AppendProperties(std::ostream& strm) const
{
	strm << "\tbaseRadius= " << GetBaseRadius() << std::endl
		<< "\theight = " << GetHeight() << std::endl;
}