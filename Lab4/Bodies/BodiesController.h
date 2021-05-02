#pragma once
#include <functional>
#include <map>
#include <memory>
#include "CBody.h"

class BodiesController
{
public:
	BodiesController(std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool AddCone(std::istream& args);
	bool AddSphere(std::istream& args);
	bool AddParallelepiped(std::istream& args);
	bool AddCylinder(std::istream& args);
	bool AddCompound(std::istream& args);
	bool AddChildToCompound(std::istream& args);
	bool Info(std::istream& args) const;
	bool IsBodyNameExist(const std::string& name) const;
private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;
	std::ostream& m_output;
	std::map<std::string, std::unique_ptr<CBody>> m_bodyMap;

	void PrintHeighestMassBodyName() const;
	void PrintLowerArchimedPowerBodyName() const;

	const ActionMap m_actionMap;
};