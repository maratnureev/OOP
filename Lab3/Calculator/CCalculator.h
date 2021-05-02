#pragma once
#include <string>
#include <functional>
#include <map>
#include <vector>

class CCalculator
{
public:
	void CreateVar(const std::string& varName);
	void SetVar(const std::string& varName, double varValue);
	void SetVar(const std::string& varName1, const std::string& varName2);
	// operation enum
	void CreateFunction(const std::string& funcName, const std::string& varName1, const std::string& varName2, const char operation);
	void CreateFunction(const std::string& funcName, const std::string& varName1);
	double GetValueByName(const std::string& identifierName) const;
	std::map<std::string, double> GetVariableValueMap() const;
	std::map<std::string, double> GetFunctionValueMap() const;
	// using EnumFunctionsCallback = std::function<void(const std::string& name, double value)>;
	// void EnumerateFunctions(const EnumFunctionsCallback& callback) const;
private:
	using UserFunction = std::function<double()>;
	std::map<std::string, double> m_variableMap;
	std::map<std::string, UserFunction> m_funcMap;

	void AssertIsNameAvailable(const std::string& name) const;
	void AssertValidName(const std::string& identifierName) const;
	bool IsFunctionName(const std::string& name) const;
	bool IsVariableName(const std::string& name) const;
	double Calculate(const double value1, const double value2, char operation) const;
};


