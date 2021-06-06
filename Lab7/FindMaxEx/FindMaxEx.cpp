#include <iostream>
#include <vector>
#include <string>

struct Athlete
{
    std::string firstName;
    std::string lastName;
    std::string parentName;
    int height;
    int weight;
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
        maxValue = arr[0];
    else
        return false;
    for (int i = 0; i < arr.size(); i++)
    {
        if (less(maxValue, arr[i]))
            maxValue = arr[i];
    }
    return true;
}

int main()
{
    auto arr = InitAthleteVector();
    auto lessMass = [](Athlete a, Athlete b) -> bool {
        if (a.weight < b.weight)
            return true;
    };
    Athlete maxMassAthlete;
    FindMax(arr, maxMassAthlete, lessMass);

}


