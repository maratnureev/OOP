#include "BodiesController.h"
#include "CBody.h"
#include "CCone.h"
#include "CCompound.h"
#include "CCylinder.h"
#include "CParallelepiped.h"
#include "CSphere.h"
#include "Exception.h"
#include <string>
#include <iostream>
#include <sstream>

const double WATER_DENSITY = 1000;
const double GRAVITY = 9.81;

using namespace std;
using namespace std::placeholders;

BodiesController::BodiesController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "AddCone", bind(&BodiesController::AddCone, this, _1) },
		  { "AddSphere", bind(&BodiesController::AddSphere, this, _1) },
		  { "AddParallelepiped", bind(&BodiesController::AddParallelepiped, this, _1) },
		  { "AddCylinder", bind(&BodiesController::AddCylinder, this, _1) },
		  { "AddCompound", bind(&BodiesController::AddCompound, this, _1) },
		  { "AddChildToCompound", bind(&BodiesController::AddChildToCompound, this, _1) },
		  { "Info", bind(&BodiesController::Info, this, _1) },
		})
{
}

bool BodiesController::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		//TODO: make void methods
		return it->second(strm);
	}

	return false;
}

bool BodiesController::AddCone(std::istream& args)
{
	string name;
	double baseRadius = 0;
	double height = 0;
	double density = 0;
	args >> name >> baseRadius >> height >> density;
	if (IsBodyNameExist(name))
	{
		//TODO redo output
		m_output << "Invalid body name\n";
		return true;
	}
	try
	{
		m_bodyMap.insert(std::make_pair(name, new CCone(baseRadius, height, density)));
	}
	catch (const InvalidParameterException& e)
	{
		m_output << e.GetMessage() << endl;
	}
	return true;
}

bool BodiesController::AddSphere(std::istream& args)
{
	string name;
	double radius = 0;
	double density = 0;
	args >> name >> radius >> density;
	if (IsBodyNameExist(name))
	{
		m_output << "Invalid body name\n";
		return true;
	}
	try
	{
		m_bodyMap.insert(std::make_pair(name, new CSphere(radius, density)));
	}
	catch (const InvalidParameterException& e)
	{
		m_output << e.GetMessage() << endl;
	}
	return true;
}

bool BodiesController::AddParallelepiped(std::istream& args)
{
	string name;
	double width = 0;
	double height = 0;
	double depth = 0;
	double density = 0;
	args >> name >> width >> height >> depth >> density;
	if (IsBodyNameExist(name))
	{
		m_output << "Invalid body name\n";
		return true;
	}
	try
	{
		m_bodyMap.insert(std::make_pair(name, new CParallelepiped(width, height, depth, density)));
	}
	catch (const InvalidParameterException& e)
	{
		m_output << e.GetMessage() << endl;
	}
	return true;
}

bool BodiesController::AddCylinder(std::istream& args)
{
	string name;
	double baseRadius = 0;
	double height = 0;
	double density = 0;
	//TODO validate args
	args >> name >> baseRadius >> height >> density;
	if (IsBodyNameExist(name))
	{
		m_output << "Invalid body name\n";
		return true;
	}
	try
	{
		m_bodyMap.insert(std::make_pair(name, new CCylinder(baseRadius, height, density)));
	}
	catch (const InvalidParameterException& e)
	{
		m_output << e.GetMessage() << endl;
	}
	return true;
}

bool BodiesController::AddCompound(std::istream& args)
{
	string name;
	args >> name;
	if (IsBodyNameExist(name))
	{
		m_output << "Invalid body name\n";
		return true;
	}
	m_bodyMap[name] = make_unique<CCompound>();
	return true;
}

bool BodiesController::AddChildToCompound(std::istream& args)
{
	string parentName;
	string childName;
	args >> parentName >> childName;
	if (!IsBodyNameExist(parentName))
	{
		m_output << "Invalid parent name\n";
		return true;
	}
	if (!IsBodyNameExist(childName))
	{
		m_output << "Invalid child name\n";
		return true;
	}
	CCompound* parentBody = dynamic_cast<CCompound*>(m_bodyMap[parentName].get());
	if (parentBody == nullptr)
	{
		m_output << "Parent body is not compund\n";
		return true;
	}
	auto childBody = std::move(m_bodyMap[childName]);
	childBody->SetParentBody(parentBody);
	try
	{
		parentBody->AddChildBody(std::move(childBody));
		m_bodyMap.erase(childName);
	}
	catch (const InvalidChildException& e)
	{
		m_output << e.GetMessage() << endl;
	}
	return true;
}

bool BodiesController::Info(std::istream& args) const 
{
	if (m_bodyMap.empty())
	{
		m_output << "There are no bodies in the controller\n";
		return true;
	}
	for (const auto& pair : m_bodyMap)
	{
		m_output << "Body name: " << pair.first << endl;
		m_output << pair.second.get()->ToString();
	}
	PrintHeighestMassBodyName();
	PrintLowerArchimedPowerBodyName();

	return true;
}

bool BodiesController::IsBodyNameExist(const std::string& name) const 
{
	for (const auto& pair : m_bodyMap)
		if (pair.first == name)
			return true;
	return false;
}

void BodiesController::PrintHeighestMassBodyName() const
{
	double highestMass = -1;
	string highestBodyMassName;

	for (const auto& pair : m_bodyMap)
	{
		if (highestMass < pair.second->GetMass())
		{
			highestBodyMassName = pair.first;
			highestMass = pair.second->GetMass();
		}
	}

	m_output << "Highest mass body: " << highestBodyMassName << endl;
	m_output << m_bodyMap.at(highestBodyMassName).get()->ToString();
}

double GetArchimedPower(CBody* body)
{
	return (body->GetDensity() - WATER_DENSITY) * GRAVITY * body->GetVolume();
}

void BodiesController::PrintLowerArchimedPowerBodyName() const
{
	double minArchimedPower = DBL_MAX;
	string minArchimedPowerBodyName;

	for (const auto& pair : m_bodyMap)
	{
		if (minArchimedPower > GetArchimedPower(pair.second.get()))
		{
			minArchimedPower = GetArchimedPower(pair.second.get());
			minArchimedPowerBodyName = pair.first;
		}
	}

	m_output << "Lower Archimed power body: " << minArchimedPowerBodyName << endl;
	m_output << m_bodyMap.at(minArchimedPowerBodyName)->ToString();
}
