#include <iostream>
#include <ranges>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> result;
    for (int i : std::ranges::istream_view<int>(std::cin)) {
        if (i != -1) {
            result.push_back(i);
        } else {
            break;
        }
    }
    for (int i : result) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    auto input_numbers = std::ranges::istream_view<int>(std::cin) | std::views::take_while([](int i) { return i != -1; });
    std::vector<int> second_result;
    std::ranges::copy(
        input_numbers,
        std::back_inserter(second_result)
    );
    std::ranges::copy(
        second_result,
        std::ostream_iterator<int>{std::cout, " "}
    );
}