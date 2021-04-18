#include "CParallelepiped.h"
#include <math.h>


CParallelepiped::CParallelepiped(double width, double height, double depth, double density)
	: CBody("Parallelepiped", density)
	, m_depth(depth)
	, m_height(height)
	, m_width(width)
{
	AssertBodyParameterValid(depth);
	AssertBodyParameterValid(height);
	AssertBodyParameterValid(width);
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetVolume() const
{
	return m_depth * m_height * m_width;
}

void CParallelepiped::AppendProperties(std::ostream& strm) const
{
	strm << "\tdepth = " << GetDepth() << std::endl
		<< "\theight = " << GetHeight() << std::endl
		<< "\twidth = " << GetWidth() << std::endl;
}