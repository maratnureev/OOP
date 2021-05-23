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
	void AddChildBody(std::unique_ptr<CBody> child);
	//TODO const reference
	void AssertChildValid(std::unique_ptr<CBody>& appendedChild) const;

private:
	void AppendProperties(std::ostream& strm) const override;
	std::vector<std::unique_ptr<CBody>> m_childs;
};

