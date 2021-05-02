#include "CRemoteControl.h"
#include "CCalculator.h"
#include "Exceptions.h"
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace std::placeholders;


CRemoteControl::CRemoteControl(CCalculator& calc, std::istream& input, std::ostream& output)
	: m_calc(calc)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "var", [this](istream& strm) {
			   return CreateVar(strm);
		   } },
		  { "let", bind(&CRemoteControl::SetVar, this, std::placeholders::_1) },
		  { "fn", bind(&CRemoteControl::CreateFunction, this, _1) },
		  { "print", bind(&CRemoteControl::Print, this, _1) },
		  { "printvars", bind(&CRemoteControl::PrintVars, this, _1) },
		  { "printfns", bind(&CRemoteControl::PrintFns, this, _1) },
		})
{
};

const vector<char> OPERATIONS = {'+', '-', '/', '*'};

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CRemoteControl::CreateVar(std::istream& args)
{
	string varName;
	args >> varName;
	try
	{
		m_calc.CreateVar(varName);
	}
	catch (const InvalidArgumentException& e)
	{
		m_output << e.GetMessage() << endl;
	}
	return true;
}

bool CRemoteControl::SetVar(std::istream& args)
{
	string letVarParams;
	args >> letVarParams;
	auto stringParts = SplitString(letVarParams, '=');
	try
	{
		try 
		{
			double number = stod(stringParts[1]);
			m_calc.SetVar(stringParts[0], number);
		}
		catch (std::exception)
		{
			m_calc.SetVar(stringParts[0], stringParts[1]);
		}
	}
	catch (const InvalidArgumentException& e)
	{
		m_output << e.GetMessage() << endl;
	}
	return true;
}

bool CRemoteControl::CreateFunction(std::istream& args)
{
	string letVarParams;
	args >> letVarParams;
	auto stringParts = SplitString(letVarParams, '=');
	char deliminator = '\0';

	auto getOperation = [&stringParts, &deliminator](const char operation){
		auto deliminatorIndex = stringParts[1].find(operation);
		if (deliminatorIndex != string::npos)
		{
			deliminator = operation;
		}
	};

	for_each(OPERATIONS.begin(), OPERATIONS.end(), getOperation);
	auto functionMembers = SplitString(stringParts[1], deliminator);

	try
	{
		if (deliminator == '\0')
		{
			m_calc.CreateFunction(stringParts[0], functionMembers[0]);
		}
		else
		{
			m_calc.CreateFunction(stringParts[0], functionMembers[0], functionMembers[1], deliminator);
		}
	}
	catch (const InvalidArgumentException& e)
	{
		m_output << e.GetMessage() << endl;
	}

	return true;
}

bool CRemoteControl::Print(std::istream& args)
{
	string identifierName;
	args >> identifierName;

	try
	{
		double value = m_calc.GetValueByName(identifierName);
		PrintValue(value);
		m_output << endl;
	}
	catch (const InvalidArgumentException& e)
	{
		m_output << e.GetMessage() << endl;
	}
	
	return true;
}

bool CRemoteControl::PrintVars(std::istream& args)
{
	auto variableValueMap = m_calc.GetVariableValueMap();

	auto printVariableValue = [this](const std::pair<std::string, double>& pair) {
		m_output << pair.first << ":";
		PrintValue(pair.second);
		m_output << endl;
	};

	for_each(variableValueMap.begin(), variableValueMap.end(), printVariableValue);
	return true;
}

bool CRemoteControl::PrintFns(std::istream& args)
{
	auto functionValueMap = m_calc.GetFunctionValueMap();

	auto printFunctionValue = [this](const std::pair<std::string, double>& pair) {
		m_output << pair.first << ":";
		PrintValue(pair.second);
		m_output << endl;
	};

	for_each(functionValueMap.begin(), functionValueMap.end(), printFunctionValue);
	return true;
}

std::vector<string> CRemoteControl::SplitString(const std::string& str, char delim) const
{
	std::vector<std::string> elems;
	std::stringstream ss(str);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

void CRemoteControl::PrintValue(double value) const
{
	if (isnan(value))
	{
		m_output << "nan";
		return;
	}
	m_output << setprecision(2) << fixed << value;
}