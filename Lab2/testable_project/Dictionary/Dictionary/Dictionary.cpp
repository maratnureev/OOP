#include <iostream>
#include <string>
#include <optional>
#include <clocale>
#include <Windows.h>
#include "DictionaryHandler.h"

using namespace std;

struct Args {
    string dictionaryFileName;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid args";
        return nullopt;
    }
    Args args;
    args.dictionaryFileName = argv[1];

    return args;
}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    auto args = ParseArgs(argc, argv);
    if (!args)
        return 1;
    auto dictionary = InitDictionary(args->dictionaryFileName);
    auto startDictionary(dictionary);

    LaunchTranslator(dictionary);
    if (startDictionary != dictionary)
    {
        SaveDictionary(dictionary, args->dictionaryFileName);
    }
}