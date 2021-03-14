#pragma once
#include <map>
#include <string>
#include <vector>

std::map<std::string, std::vector<std::string>>InitDictionary(std::string const& dictionaryFileName);
void AskForTranslationAndSave(std::string const& lineForTranslation, std::map<std::string, std::vector<std::string>>& dictionary);
void WriteTransations(std::vector<std::string>& translations);
void HandleWord(std::string const& lineForTranslation, std::map<std::string, std::vector<std::string>>& dictionary);
void LaunchTranslator(std::map<std::string, std::vector<std::string>>& dictionary);