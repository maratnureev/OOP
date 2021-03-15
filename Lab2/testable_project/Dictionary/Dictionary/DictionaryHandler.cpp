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

vector<string> SplitString(const string str, char delim)
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

map<string, vector<string>>InitDictionary(string const& dictionaryFileName)
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
            string translation = line.substr(delimiter+1);
            istringstream iss(line);
            vector<string> translations = SplitString(translation, ',');
            dictionary[sourceWord] = translations;
        }
    }
    return dictionary;
}

void AskForTranslationAndSave(string const& lineForTranslation, string const& lowerCaseTranslation, map<string, vector<string>>& dictionary)
{
    string translation;
    cout << "����������� ����� '" + lineForTranslation + "'. ������� ������� ��� ������ ������ ��� ������.\n";
    getline(cin, translation);
    if (!translation.empty())
    {
        string lowerCaseLine = lineForTranslation;
        std::transform(lowerCaseLine.begin(), lowerCaseLine.end(), lowerCaseLine.begin(), ::tolower);
        vector<string> translations = dictionary[lowerCaseLine];
        translations.push_back(translation);
        dictionary[lowerCaseLine] = translations;
        cout << "����� '" + lineForTranslation + "' ��������� � ������� ��� '" + translation + "'.\n";
    }
    else
    {
        cout << "����� '" << lineForTranslation << "' �� ���������.\n";
    }
}

void WriteTransations(vector<string>& translations, ostream &out)
{
    string outputString;
    auto Print = [&outputString](const string& number) {
        outputString += number + ", ";
    };
    for_each(translations.begin(), translations.end(), Print);
    outputString.erase(outputString.size() - 2);
    out << outputString << endl;
}

void HandleWord(string const& lineForTranslation, map<string, vector<string>>& dictionary)
{
    vector<string> translations = dictionary[lineForTranslation];
    if (translations.empty())
        AskForTranslationAndSave(lineForTranslation, dictionary);
    else
        WriteTransations(translations, cout);
}

void SaveDictionary(map<string, vector<string>>& dictionary, string const& dictionaryFileName)
{
    ofstream out(dictionaryFileName, std::ofstream::trunc);
    for (auto& word : dictionary)
    {
        out << word.first << '=';
        WriteTransations(word.second, out);
    }
}

void LaunchTranslator(map<string, vector<string>>& dictionary)
{
    string lineForTranslation;

    while (true)
    {
        cin >> lineForTranslation;
        if (lineForTranslation == "...")
            break;
        HandleWord(lineForTranslation, dictionary);
    }
}