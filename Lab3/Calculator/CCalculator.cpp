#include "CCalculator.h"
#include "Exceptions.h"
#include <limits>
#include <algorithm>
#include <regex>

const std::regex IDENTIFIER_REGEX(R"([a-zA-Z_][\w_]*)");

void CCalculator::CreateVar(const std::string& varName)
{
    AssertIsNameAvailable(varName);
    AssertValidName(varName);
    m_variableMap[varName] = double(NAN);
}

void CCalculator::SetVar(const std::string& varName, double varValue)
{
    AssertValidName(varName);
    auto varIndex = m_variableMap.find(varName);
    if (varIndex == m_variableMap.end())
    {
        CreateVar(varName);
    }
    m_variableMap[varName] = varValue;
}

void CCalculator::SetVar(const std::string& varName1, const std::string& varName2)
{
    AssertValidName(varName1);
    AssertValidName(varName2);
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
    throw InvalidArgumentException("Variable or function with this name does not exist: " + varName2);
}

void CCalculator::CreateFunction(const std::string& funcName, const std::string& varName1, const std::string& varName2, const char operation)
{
    AssertValidName(funcName);
    AssertValidName(varName1);
    AssertValidName(varName2);
    AssertIsNameAvailable(funcName);

    auto userFunc = [this, varName1, varName2, operation]() -> double {
        bool isFirstNameFunction = IsFunctionName(varName1);
        bool isSecondNameFunction = IsFunctionName(varName2);
        if (!IsVariableName(varName1))
            if (!isFirstNameFunction)
                return double(NAN);
        if (!IsVariableName(varName2))
            if (!isSecondNameFunction)
                return double(NAN);
        if (isFirstNameFunction)
            if (isSecondNameFunction)
                return Calculate(m_funcMap[varName1](), m_funcMap[varName2](), operation);
            else
                return Calculate(m_funcMap[varName1](), m_variableMap[varName2], operation);
        else
            if (isSecondNameFunction)
                return Calculate(m_variableMap[varName1], m_funcMap[varName2](), operation);
            else
                return Calculate(m_variableMap[varName1], m_variableMap[varName2], operation);
        return double(NAN);
    };

    m_funcMap[funcName] = userFunc;
}

void CCalculator::CreateFunction(const std::string& funcName, const std::string& varName1)
{
    AssertValidName(funcName);
    AssertValidName(varName1);
    AssertIsNameAvailable(funcName);
    auto userFunc = [this, varName1]() -> double {
        bool isFirstNameFunction = IsFunctionName(varName1);
        if (!IsVariableName(varName1))
            if (!isFirstNameFunction)
                return double(NAN);
        if (isFirstNameFunction)
            return m_funcMap[varName1]();
        else
            return m_variableMap[varName1];
    };
    m_funcMap[funcName] = userFunc;
}

double CCalculator::GetValueByName(const std::string& identifierName) const
{
    AssertValidName(identifierName);
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
        throw InvalidArgumentException(std::string("Variable or function with this name does not exist: " + identifierName));
    }
}

std::map<std::string, double> CCalculator::GetVariableValueMap() const
{
    return m_variableMap;
}

std::map<std::string, double> CCalculator::GetFunctionValueMap() const
{
    std::map<std::string, double> funcValueMap;
    auto getFuncValue = [&funcValueMap](const std::pair<std::string, UserFunction>& pair) {
        funcValueMap[pair.first] = pair.second();
    };
    std::for_each(m_funcMap.begin(), m_funcMap.end(), getFuncValue);
    return funcValueMap;
}

void CCalculator::AssertIsNameAvailable(const std::string& name) const
{
    auto varIndex = m_variableMap.find(name);
    if (varIndex != m_variableMap.end())
        throw InvalidArgumentException(std::string("Variable with this name already exists: " + name));
    else
    {
        auto fnIndex = m_funcMap.find(name);
        if (fnIndex != m_funcMap.end())
            throw InvalidArgumentException(std::string("Function with this name already exists: " + name));
    }
}

bool CCalculator::IsVariableName(const std::string& name) const
{
    auto varIndex = m_variableMap.find(name);
    if (varIndex == m_variableMap.end())
        return false;
    return true;
}

bool CCalculator::IsFunctionName(const std::string& name) const
{
    auto fnIndex = m_funcMap.find(name);
    if (fnIndex == m_funcMap.end())
        return false;
    return true;
}

void CCalculator::AssertValidName(const std::string& identifierName) const
{
    std::smatch piecesMatch;
    if (!std::regex_match(identifierName, piecesMatch, IDENTIFIER_REGEX))
        throw InvalidArgumentException(std::string("Identifier name should consists of symbols (a-z, A-Z, 0-9, _) and should not start with number"));
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

