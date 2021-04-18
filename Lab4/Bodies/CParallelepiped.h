#pragma once
#include "CBody.h"

class CParallelepiped final : public CBody
{
public:
	CParallelepiped(double width, double height, double depth, double density);

	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_width;
	double m_height;
	double m_depth;
	double m_density;
};
