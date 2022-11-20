#include <ranges>
#include <iostream>
#include <string>

int main() {
    auto my_range =
        std::views::iota(10, 101)
        | std::views::transform([](int i) { return i * i; })
        | std::views::filter([](int i) { return i % 5 != 0; })
        | std::views::transform([](int i) { return std::to_string(i); });
    for (std::string i_str: my_range) {
        std::cout << i_str << " ";
    }
}