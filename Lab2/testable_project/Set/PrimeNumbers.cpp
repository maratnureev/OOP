#include <set>
#include <vector>
#include "PrimeNumbers.h"

const int MAX_UPPER_BOUND = 100000001;

std::set<int> GeneratePrimeNumbersSet(int upperBound, bool& wasError)
{
    std::set<int> primeSet;
    if (upperBound >= MAX_UPPER_BOUND)
    {
        wasError = true;
        return primeSet;
    }
    std::vector<bool> prime(upperBound +1, true);
    std::vector<int> smallestPrimeFactor(upperBound +1);
    prime[0] = prime[1] = false;
    for (int i = 2; i <= upperBound; i++)
    {
        if (prime[i])
        {
            primeSet.insert(i);
            smallestPrimeFactor[i] = i;
        }
        std::set<int>::iterator primeSetIt = primeSet.begin();

        auto setElement = *primeSetIt;

        for (int j = 0; j < primeSet.size() && i * setElement <= upperBound && setElement <= smallestPrimeFactor[i]; j++)
        {
            prime[i * setElement] = false;
            smallestPrimeFactor[i * setElement] = setElement;
            primeSetIt++;
            setElement = *primeSetIt;
        }
    }

    return primeSet;
}