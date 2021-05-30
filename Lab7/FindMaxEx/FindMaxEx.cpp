#include <iostream>
#include <vector>


template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
    if (arr.size > 0)
        maxValue = arr[0];
    else
        return false;
    for (int i = 0; i < arr.size(), i++)
    {
        if (less(maxValue, arr[i]))
            maxValue = arr[i];
    }
    return true;
}

int main()
{
    std::cout << "Hello World!\n";
}


