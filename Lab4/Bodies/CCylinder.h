#pragma once
#include "CBody.h"
#include <math.h>

class CCylinder final : public CBody
{
public:
	CCylinder(double baseRadius, double height, double density);

	double GetBaseRadius() const;
	double GetHeight() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_baseRadius;
	double m_height;
	double m_density;
};



