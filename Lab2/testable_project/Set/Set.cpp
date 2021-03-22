#include <iostream>
#include "PrimeNumbers.h"

int main()
{
    int upperBound;
    std::cin >> upperBound;
    bool wasError = false;
    auto primeSet = GeneratePrimeNumbersSet(upperBound, wasError);
    if (wasError)
        return 1;
    std::cout << primeSet.size();
}
