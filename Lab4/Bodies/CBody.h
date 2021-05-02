#pragma once

#include <string>
#include <sstream>
#include <iomanip>

class CBody
{
public:
	CBody(const std::string& type, double density);

	virtual double GetDensity() const;
	virtual double GetVolume() const = 0;
	virtual double GetMass() const;
	void SetParentBody(CBody* parent);
	CBody* GetParentBody() const;
	std::string ToString() const;

	void AssertBodyParameterValid(double param);

private:
	virtual void AppendProperties(std::ostream& strm) const = 0;
	double m_density;
	std::string m_type;
	CBody* m_parent;
};

