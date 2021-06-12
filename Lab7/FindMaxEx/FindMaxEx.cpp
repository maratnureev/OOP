#include <iostream>
#include <vector>
#include <string>

struct Athlete
{
    std::string firstName;
    std::string lastName;
    std::string parentName;
    int height = 0;
    int weight = 0;
};

std::vector<Athlete> InitAthleteVector()
{
    std::vector <Athlete> arr;
    for (int i = 0; i < 10; i++)
    {
        Athlete athlete;
        athlete.firstName = "Name" + std::to_string(i+1);
        athlete.lastName = "Surname" + std::to_string(i + 1);
        athlete.parentName = "Middle name" + std::to_string(i + 1);
        athlete.height = (i + 6) * (i + 6) * (i + 6);
        athlete.weight = (20 - i) * (20 - i);
        arr.push_back(athlete);
    }
    return arr;
}

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
    if (arr.size() > 0)
        maxValue = arr.back();
    else
        return false;
    for (auto& item : arr)
    {
        if (less(maxValue, item))
            maxValue = item;
    }
    return true;
}

int main()
{
    auto arr = InitAthleteVector();
    auto lessMass = [](Athlete a, Athlete b) -> bool {
        return a.weight < b.weight;
    };

    Athlete maxMassAthlete;
    FindMax(arr, maxMassAthlete, lessMass);
    std::cout << maxMassAthlete.firstName << std::endl;
    std::cout << maxMassAthlete.lastName << std::endl;
    std::cout << maxMassAthlete.parentName << std::endl;
    std::cout << maxMassAthlete.height << std::endl;
    std::cout << maxMassAthlete.weight << std::endl;

    auto lessHeight = [](Athlete a, Athlete b) -> bool {
        return a.weight > b.weight;
    };
    Athlete minHeightAthlete;
    FindMax(arr, minHeightAthlete, lessHeight);

    std::cout << minHeightAthlete.firstName << std::endl;
    std::cout << minHeightAthlete.lastName << std::endl;
    std::cout << minHeightAthlete.parentName << std::endl;
    std::cout << minHeightAthlete.height << std::endl;
    std::cout << minHeightAthlete.weight << std::endl;
}


