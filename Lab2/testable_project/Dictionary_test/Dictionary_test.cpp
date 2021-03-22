#include <vector>
#include <string>
#include <map>
#include <iosfwd>


#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Dictionary/Dictionary/DictionaryHandler.h"

using namespace std;

SCENARIO("Handle word in empty dictionary, translation not added")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	string lineForTranslation = "testWord";
	map<string, vector<string>> dictionary;

	istringstream input("");
	cin.rdbuf(input.rdbuf());

	HandleWord(lineForTranslation, dictionary);

	REQUIRE(dictionary["testword"].empty());
}

SCENARIO("Handle word in empty dictionary, translation added")
{
	string lineForTranslation = "testWord";
	vector<string> translations = { "Перевод" };
	map<string, vector<string>> dictionary;

	istringstream input("Перевод");
	cin.rdbuf(input.rdbuf());
	bool isEdited = false;
	HandleWord(lineForTranslation, dictionary);
	
	REQUIRE(dictionary["testword"] == translations);
}


SCENARIO("Given word is translated with case missmatch")
{
	string lineForTranslation = "testWord";
	vector<string> translations = { "Перевод" };
	map<string, vector<string>> dictionary;
	dictionary["testword"] = translations;

	stringstream input("Перевод");
	cin.rdbuf(input.rdbuf());
	HandleWord(lineForTranslation, dictionary);
	
	REQUIRE(dictionary["testword"] == translations);
}

SCENARIO("Save dictionary file if dictionary changed")
{
	string lineForTranslation = "testWord";
	vector<string> translations = { "Перевод" };
	map<string, vector<string>> dictionary;
	string expected = "testword=Перевод";
	dictionary["testword"] = translations;

	stringstream input("Y");
	cin.rdbuf(input.rdbuf());
	SaveDictionary(dictionary, "dict.txt");

	ifstream dictIn("dict.txt");
	string output;
	getline(dictIn, output);

	REQUIRE(expected == output);
}

SCENARIO("Do not save dictionary file if dictionary changed")
{
	ofstream dictOut("dict.txt");
	string lineForTranslation = "testWord";
	vector<string> translations = { "Перевод" };
	map<string, vector<string>> dictionary;
	string expected = "";
	dictOut << expected;
	dictionary["testword"] = translations;
	dictOut.close();

	stringstream input("N");
	cin.rdbuf(input.rdbuf());
	bool isEdited = false;
	SaveDictionary(dictionary, "dict.txt");

	ifstream dictIn("dict.txt");
	string output;
	getline(dictIn, output);

	REQUIRE(expected == output);
}