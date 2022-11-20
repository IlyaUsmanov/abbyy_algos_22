#include <iostream>
#include <ranges>
#include <string>
#include <vector>
#include <algorithm>

template < typename InputIter >
auto sum ( InputIter begin , InputIter end ) {
    auto sum { * begin };
    for ( auto iter { ++ begin }; iter != end ; ++ iter ) {
        sum += * iter ;
    }
    return sum;
}

class Person {
public:
    std::string first_name;
    std::string second_name;
};

int main() {
    std::vector<std::pair<Person, int> > personsWithAge{ {Person("Ilya", "Usmanov"), 21}, {Person("Unknown", "Child"), 9},
                                                         {Person("Unknown", "Ancient"), 99}, {Person("Simple", "Guy"), 14} };
    auto filteredPersons =
        personsWithAge
        | std::views::transform([](std::pair<Person, int> personWithAge) { return personWithAge.second; })
        | std::views::filter([](int age) { return age >= 12 && age <= 65; });
    std::cout << (double)sum(filteredPersons.begin(), filteredPersons.end()) / std::ranges::distance(filteredPersons);
}