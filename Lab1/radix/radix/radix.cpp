#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <optional>

using namespace std;

const int LETTER_A_NUMBER = 10;
const int ZERO_NUMBER = 0;
const char LETTER_A_SYMBOL = 'A';
const char ZERO_SYMBOL = '0';
const char NINE_SYMBOL = '9';
const char LETTER_Z_SYMBOL = 'Z';

struct Args {
    int sourceRadix = 0;
    int destinationRadix = 0;
    string value;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Invalid args";
        return nullopt;
    }
    Args args;
    args.sourceRadix= stoi(argv[1]);
    args.destinationRadix = stoi(argv[2]);
    args.value = argv[3];

    if (args.sourceRadix < 2 || args.sourceRadix > 36)
    {
        cout << "Invalid source notaion";
        return nullopt;
    }
    if (args.destinationRadix < 2 || args.destinationRadix > 36)
    {
        cout << "Invalid destination notaion";
        return nullopt;
    }

    return args;
}

int StringToInt(const string& str, int radix, map<char, int>& symbolMap, bool& wasError)
{
    wasError = true;
    string value = str;
    if (str == "")
    {
        cout << "Invalid value";
        return 0;
    }
    int result = 0;
    long long overflowResult = 0;
    
    int strLength = value.length();
    bool isNegative = false;
    int startPos = 0;
    if (str != "" && str[0] == '-')
    {
        startPos = 1;
        isNegative = true;
    }
    for (int i = startPos; i < strLength; i++)
    {
        overflowResult *= radix;
        char symbol = value[i];
        if (!((symbol >= '0' && symbol <= '9') || (symbol >= 'A' && symbol <= 'Z')))
        {
            cout << "Invalid value";
            return 0;
        }
        int number = symbolMap[value[i]];
        if (number >= radix)
        {
            cout << "Invalid value";
            return 0;
        }
        if (isNegative)
        {
            overflowResult -= number;
        }
        else
        {
            overflowResult += number;
        }
    }
    if (overflowResult > INT_MAX || overflowResult < INT_MIN)
    {
        cout << "Result overflow";
        return 0;
    }
    result = (int)overflowResult;
    wasError = false;
    return result;
}

string IntToString(int n, int radix, map<int, char>& numberMap)
{
    int j = ZERO_NUMBER;
    string result = "";
    string reverseResult = "";
    bool isNegative = false;
    if (n < 0)
    {
        isNegative = true;
    }
    while (n != 0)
    {
        int remainder = abs(n % radix);
        reverseResult += numberMap[remainder];
        n /= radix;
    }
    for (int i = reverseResult.length() - 1; i >= 0; i--)
    {
        result += reverseResult[i];
    }
    if (isNegative)
    {
        result.insert(0, "-");
    }

    return result;
}

string ConvertNumber(string value, int sourceRadix, int destinationRadix, map<char, int>& symbolMap, map<int, char>& numberMap, bool& wasError)
{
    wasError = false;

    if (value == "0")
        return value;

    int decimalNumber = StringToInt(value, sourceRadix, symbolMap, wasError);
    if (wasError)
        return "";

    return IntToString(decimalNumber, destinationRadix, numberMap);
}

void InitSymbolMaps(map<char, int>& symbolMap, map<int, char>& numberMap)
{
    int j = ZERO_NUMBER;
    for (char i = ZERO_SYMBOL; i <= NINE_SYMBOL; i++)
    {
        numberMap[j] = i;
        symbolMap[i] = j++;
    }
    j = LETTER_A_NUMBER;
    for (char i = LETTER_A_SYMBOL; i <= LETTER_Z_SYMBOL; i++)
    {
        symbolMap[i] = j;
        numberMap[j++] = i;
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
    bool wasError = false;
    auto args = ParseArgs(argc, argv);
    if (!args)
        return 1;

    map<char, int> symbolMap;
    map<int, char> numberMap;
    
    InitSymbolMaps(symbolMap, numberMap);

    string newDestinationNumber = ConvertNumber(args->value, args->sourceRadix, args->destinationRadix, symbolMap, numberMap, wasError);
    if (wasError)
        return 1;

    cout << newDestinationNumber << endl;
}