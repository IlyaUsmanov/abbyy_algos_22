#include <string>
#include <iostream>

template<typename T>
concept NumbersConvertibleToString = (std::is_integral_v<T> ||
                                     std::is_floating_point_v<T>) && 
                                     requires(T number) { std::to_string(number); };

template<NumbersConvertibleToString U, NumbersConvertibleToString V>
std::string concat(U t1, V t2) {
    return std::to_string(t1) + std::to_string(t2);
}

int main() {
    static_assert(NumbersConvertibleToString<int>);
    static_assert(NumbersConvertibleToString<float>);
    static_assert(NumbersConvertibleToString<double>);
    static_assert(NumbersConvertibleToString<long long>);
    static_assert(!NumbersConvertibleToString<std::string>);
    std::cout << concat(true, false) << std::endl;
}