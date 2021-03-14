#include <iostream>

#include <iostream>
#include <fstream>
#include <string>
#include <optional>

using namespace std;

struct Args {
    string inputFileName;
    string outputFileName;
    string searchString;
    string replaceString;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 4 && argc != 5)
    {
        return nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.searchString = argv[3];
    args.replaceString = argv[4];

    return args;
}

void ReplaceAllSubstrings(istream& in, ostream& out, optional<Args> args)
{
    string line = "";
    while (getline(in, line))
    {
        string newString;
        newString.reserve(line.length());

        size_t lastPos = 0;
        size_t findPos = 0;
        if (args->searchString != "")
        {
            while (string::npos != (findPos = line.find(args->searchString, lastPos)))
            {
                newString.append(line, lastPos, findPos - lastPos);
                newString += args->replaceString;
                lastPos = findPos + args->searchString.length();
            }
        }

        newString += line.substr(lastPos);
        out << newString << endl;
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        cout << "Invalid arguments";
        cout << "Usage: replace.exe <intputFileName> <outputFileName> <searchString> <replaceString>";
        return 1;
    }

    ifstream in(args->inputFileName);
    if (!in)
    {
        cout << "File is not exist " << args->inputFileName;
        return 1;
    }
    ofstream out(args->outputFileName);
    if (!out)
    {
        cout << "File is not exist " << args->inputFileName;
        return 1;
    }

    if (in.is_open())
    {
        ReplaceAllSubstrings(in, out, args);
    }
}