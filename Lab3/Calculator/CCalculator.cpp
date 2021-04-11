#include "CCalculator.h"
#include "Exceptions.h"
#include <limits>
#include <algorithm>

void CCalculator::CreateVar(const std::string& varName)
{
    AssertIsNameAvailable(varName);
    m_variableMap[varName] = double(NAN);
}

void CCalculator::SetVar(const std::string& varName, double varValue)
{
    auto varIndex = m_variableMap.find(varName);
    if (varIndex == m_variableMap.end())
    {
        CreateVar(varName);
    }
    m_variableMap[varName] = varValue;
}

void CCalculator::SetVar(const std::string& varName1, const std::string& varName2)
{
    auto varIndex = m_variableMap.find(varName1);
    if (varIndex == m_variableMap.end())
    {
        CreateVar(varName1);
    }
    if (IsVariableName(varName2))
    {
        m_variableMap[varName1] = m_variableMap[varName2];
        return;
    }
    if (IsFunctionName(varName2))
    {
        m_variableMap[varName1] = m_funcMap[varName2]();
        return;
    }
    throw new InvalidArgumentException("Variable or function with this name does not exist: " + varName2);
}

void CCalculator::CreateFunction(const std::string& funcName, const std::string& varName1, const std::string& varName2, const char operation)
{
    AssertIsNameAvailable(funcName);
    auto userFunc = [this, varName1, varName2, operation]() -> double {
        bool isFirstNameFunction = IsFunctionName(varName1);
        bool isSecondNameFunction = IsFunctionName(varName2);
        if (!IsVariableName(varName1))
        {
            if (!isFirstNameFunction)
            {
                return double(NAN);
            }
        }
        if (varName2 == "")
        {
            return m_variableMap[varName1];
        }
        if (!IsVariableName(varName2))
        {
            if (!isSecondNameFunction)
            {
                return double(NAN);
            }
        }
        if (isFirstNameFunction)
        {
            if (isSecondNameFunction)
                return Calculate(m_funcMap[varName1](), m_funcMap[varName2](), operation);
            else
                return Calculate(m_funcMap[varName1](), m_variableMap[varName2], operation);
        }
        else
        {
            if (isSecondNameFunction)
                return Calculate(m_variableMap[varName1], m_funcMap[varName2](), operation);
            else
                return Calculate(m_variableMap[varName1], m_variableMap[varName2], operation);
        }
        return double(NAN);
    };
    m_funcMap[funcName] = userFunc;
}

double CCalculator::GetValueByName(const std::string& identifierName) const
{
    if (IsVariableName(identifierName))
    {
        return m_variableMap.at(identifierName);
    }
    else if (IsFunctionName(identifierName))
    {
        auto userFunction = m_funcMap.at(identifierName);
        return userFunction();
    }
    else
    {
        throw new InvalidArgumentException(std::string("Variable or function with this name does not exist: " + identifierName));
    }
}

std::map<std::string, double> CCalculator::GetVariableValueMap() const
{
    return m_variableMap;
}

std::map<std::string, double> CCalculator::GetFunctionValueMap() const
{
    std::map<std::string, double> funcValueMap;
    auto getFuncValue = [&funcValueMap](const std::pair<std::string, userFunction>& pair) {
        funcValueMap[pair.first] = pair.second();
    };
    std::for_each(m_funcMap.begin(), m_funcMap.end(), getFuncValue);
    return funcValueMap;
}

void CCalculator::AssertIsNameAvailable(const std::string& name) const
{
    auto varIndex = m_variableMap.find(name);
    if (varIndex != m_variableMap.end())
    {
        throw new InvalidArgumentException(std::string("Variable with this name already exists: " + name));
    }
    else
    {
        auto fnIndex = m_funcMap.find(name);
        if (fnIndex != m_funcMap.end())
        {
            throw new InvalidArgumentException(std::string("Function with this name already exists: " + name));
        }
    }
}

bool CCalculator::IsVariableName(const std::string& name) const
{
    auto varIndex = m_variableMap.find(name);
    if (varIndex == m_variableMap.end())
    {
        return false;
    }
    return true;
}

bool CCalculator::IsFunctionName(const std::string& name) const
{
    auto fnIndex = m_funcMap.find(name);
    if (fnIndex == m_funcMap.end())
    {
        return false;
    }
    return true;
}

double CCalculator::Calculate(const double value1, const double value2, char operation) const
{
    switch (operation)
    {
    case '+':
        return value1 + value2;
    case '-':
        return value1 - value2;
    case '*':
        return value1 * value2;
    case '/':
        return value1 / value2;
    default:
        return double(NAN);
    }
}

