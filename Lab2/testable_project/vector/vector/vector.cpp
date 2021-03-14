#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <optional>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include "vector.h"

using namespace std;

vector<double> ReadVector()
{
    //TODO: проверять является ли числом
    vector<double> floatNumbers;
    string tempString;
    getline(cin, tempString);
    double number = 0;
    istringstream tempStream(tempString);
    while (tempStream >> number)
        floatNumbers.push_back(number);
    return floatNumbers;
}

double FindMinElem(vector<double>& floatNumbers)
{
    return *min_element(floatNumbers.begin(), floatNumbers.end());
}

void CalculateVector(vector<double>& floatNumbers)
{
    if (!floatNumbers.empty())
    {
        auto minValue = FindMinElem(floatNumbers);
        auto multiplyNumber{
            [minValue](double firstMult) -> double
            {
                return minValue * firstMult;
            }
        };
        transform(floatNumbers.begin(), floatNumbers.end(), floatNumbers.begin(), multiplyNumber);
    }
}

void WriteVector(vector<double>& floatNumbers)
{
    if (!floatNumbers.empty())
    {
        auto Print = [](const double& number) { cout << number << " "; };
        for_each(floatNumbers.begin(), floatNumbers.end(), Print);
    }
}
