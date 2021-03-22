#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <optional>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

vector<string> SplitString(const string& str, char delim)
{
	vector<string> elems;
	stringstream ss(str);
	string item;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

map<string, vector<string>> InitDictionary(string const& dictionaryFileName)
{
	map<string, vector<string>> dictionary;
	ifstream in(dictionaryFileName);
	if (in)
	{
		string line;
		while (getline(in, line))
		{
			auto delimiter = line.find("=");
			string sourceWord = line.substr(0, delimiter);
			string translation = line.substr(delimiter + 1);
			istringstream iss(line);
			vector<string> translations = SplitString(translation, ',');
			dictionary[sourceWord] = translations;
		}
	}
	return dictionary;
}

string AskForTranslation(string const& lineForTranslation)
{
	string translation;
	cout << "Неизвестное слово '" + lineForTranslation + "'. Введите перевод или пустую строку для отказа.\n";
	getline(cin, translation);
	return translation;
}

void SaveTranslation(string const& translation, string const& lowerCaseTranslation, map<string, vector<string>>& dictionary)
{
	vector<string> translations = dictionary[lowerCaseTranslation];
	translations.push_back(translation);
	dictionary[lowerCaseTranslation] = translations;
}

void WriteTransations(vector<string>& translations, ostream& out)
{
	string outputString;
	auto Print = [&outputString](const string& number) {
		outputString += number + ", ";
	};
	for_each(translations.begin(), translations.end(), Print);
	if (!outputString.empty())
	{
		outputString.erase(outputString.size() - 2);
	}
	out << outputString << endl;
}

void HandleWord(string const& lineForTranslation, map<string, vector<string>>& dictionary)
{
	string lowerCaseLine = lineForTranslation;
	std::transform(lowerCaseLine.begin(), lowerCaseLine.end(), lowerCaseLine.begin(), ::tolower);
	vector<string> translations = dictionary[lowerCaseLine];
	if (translations.empty())
	{
		string translation = AskForTranslation(lineForTranslation);
		if (!translation.empty())
		{
			SaveTranslation(translation, lowerCaseLine, dictionary);
			cout << "Слово '" << lineForTranslation << "' сохранено в словаре как '" << translation << "'.\n";
		}
		else
			cout << "Слово '" << lineForTranslation << "' не сохранено.\n";
	}
	else
		WriteTransations(translations, cout);
}

void SaveDictionary(map<string, vector<string>>& dictionary, string const& dictionaryFileName)
{
	cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
	string needSaving;
	getline(cin, needSaving);
	if ((needSaving == "y") || (needSaving == "Y"))
	{
		//TODO: выделить функцию сохранения словаря
		ofstream out(dictionaryFileName, std::ofstream::trunc);
		for (auto& word : dictionary)
		{
			out << word.first << '=';
			WriteTransations(word.second, out);
		}
		cout << "Изменения сохранены. До свидания.";
	}
}

bool LaunchTranslator(map<string, vector<string>>& dictionary)
{
	string lineForTranslation;
	bool isDictionaryTranslated = false;
	while (true)
	{
		getline(cin, lineForTranslation);
		if (lineForTranslation == "...")
			break;
		HandleWord(lineForTranslation, dictionary);
	}

	return isDictionaryTranslated;
}