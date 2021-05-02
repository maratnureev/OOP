#pragma once
#include "CBody.h"
#include <math.h>
#include <vector>

class CCompound final : public CBody
{
public:
	CCompound();
	double GetVolume() const override;
	double GetMass() const override;
	double GetDensity() const override;
	std::vector<CBody*> GetChilds() const;
	void AddChildBody(CBody* child);

private:
	void AppendProperties(std::ostream& strm) const override;
	void AssertChildValid(CBody* appendedChild) const;
	std::vector<CBody*> m_childs;
};

