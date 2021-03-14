#include <iostream>
#include <string>
#include <optional>
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
    setlocale(LC_ALL, "rus");
    auto args = ParseArgs(argc, argv);
    if (!args)
        return 1;
    auto dictionary = InitDictionary(args->dictionaryFileName);
    LaunchTranslator(dictionary);

}