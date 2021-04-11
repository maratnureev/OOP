#pragma once
#include <iosfwd>
#include <functional>
#include <map>
#include <string>
#include <vector>

class CCalculator;

class CRemoteControl
{
public:
	CRemoteControl(CCalculator& calc, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool CreateVar(std::istream& args);
	bool SetVar(std::istream& args);
	bool CreateFunction(std::istream& args);
	bool Print(std::istream& args);
	bool PrintVars(std::istream& args);
	bool PrintFns(std::istream& args);
private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	CCalculator& m_calc;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;

	std::vector<std::string> SplitString(const std::string& str, char delim) const;
	void PrintValue(double value) const;
};