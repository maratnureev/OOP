#include <set>
#include <vector>
#include "PrimeNumbers.h"


std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primeSet;
    std::vector<bool> prime(upperBound + 1, true);
    std::vector<int>SmallestPrimeFactor(upperBound + 1);
    prime[0] = prime[1] = false;
    for (int i = 2; i < upperBound; i++)
    {
        if (prime[i])
        {
            primeSet.insert(i);
            SmallestPrimeFactor[i] = i;
        }
        std::set<int>::iterator primeSetIt = primeSet.begin();

        auto setElement = *primeSetIt;

        for (int j = 0; j < primeSet.size() && i * setElement < upperBound && setElement <= SmallestPrimeFactor[i]; j++)
        {
            prime[i * setElement] = false;
            SmallestPrimeFactor[i * setElement] = setElement;
            primeSetIt++;
            setElement = *primeSetIt;
        }
    }

    return primeSet;
}