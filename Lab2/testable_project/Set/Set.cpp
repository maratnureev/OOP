#include <iostream>
#include "PrimeNumbers.h"

int main()
{
    int upperBound;
    std::cin >> upperBound;
    auto primeSet = GeneratePrimeNumbersSet(upperBound);
    std::cout << primeSet.size();
}
