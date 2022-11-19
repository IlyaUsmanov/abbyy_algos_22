#include <iostream>
#include <ranges>
#include <string>
#include <vector>
#include <algorithm>


template < typename InputIter , typename OutputIter >
void myCopy ( InputIter begin , InputIter end , OutputIter target ) {
    for (auto iter { begin }; iter != end ; ++ iter , ++ target) {
        *target = *iter ;
    }
}

class Person {
public:
    std::string first_name;
    std::string second_name;
};

std::ostream& operator<<(std::ostream& out, const Person& person) {
    out << person.first_name << ' ' << person.second_name;
    return out;
}

int main() {
    std::vector<std::pair<Person, int> > personsWithAge{ {Person("Ilya", "Usmanov"), 21}, {Person("Unknown", "Child"), 9},
                                                         {Person("Unknown", "Ancient"), 99}, {Person("Simple", "Guy"), 14},
                                                         {Person("One", "More"), 42} };
    auto filteredPersons =
        personsWithAge
        | std::views::transform([](std::pair<Person, int> personWithAge) { return personWithAge.first; })
        | std::views::take(4);
    std::ostream_iterator<Person> out_iter (std::cout, "\n");
    myCopy(filteredPersons.begin(), filteredPersons.end(), out_iter);
    auto onlySecondNames = filteredPersons | std::views::transform([](Person person) { return person.second_name; });
    std::ostream_iterator<std::string> out_second_names_iter (std::cout, "\n");
    myCopy(onlySecondNames.begin(), onlySecondNames.end(), out_second_names_iter);
}