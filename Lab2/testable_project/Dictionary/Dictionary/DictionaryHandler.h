#pragma once
#include <map>
#include <string>
#include <vector>
#include <fstream>

std::map<std::string, std::vector<std::string>>InitDictionary(std::string const& dictionaryFileName);
void SaveTranslation(std::string const& translation, std::string const& lowerCaseTranslation, std::map<std::string, std::vector<std::string>>& dictionary);
std::string AskForTranslation(std::string const& lineForTranslation);
void WriteTransations(std::vector<std::string>& translations, std::ostream& out);
void HandleWord(std::string const& lineForTranslation, std::map<std::string, std::vector<std::string>>& dictionary);
bool LaunchTranslator(std::map<std::string, std::vector<std::string>>& dictionary);
void SaveDictionary(std::map<std::string, std::vector<std::string>>& dictionary, std::string const& dictionaryFileName);