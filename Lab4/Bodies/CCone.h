#pragma once
#include "CBody.h"
#include <math.h>

class CCone final : public CBody
{
public:
	CCone(double baseRadius, double height, double density);

	double GetBaseRadius() const;
	double GetHeight() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_baseRadius;
	double m_height;
	double m_density;
};


