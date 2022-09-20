#include "process_deals/process_deals.cpp"
#include <cassert>
#include <iostream>

bool is_equal_files(const std::string &first, const std::string &second) {
    std::ifstream first_in(first), second_in(second);
    while (!first_in.eof() && !second_in.eof()) {
        std::string first_inp, second_inp;
        first_in >> first_inp;
        second_in >> second_inp;
        if (first_inp != second_inp) {
            return false;
        }
    }
    return first_in.eof() && second_in.eof();
}

bool check_test(const std::string &in, const std::string &gt_out, const DealType &deal_type) {
    process_deals(in, "tmp", deal_type);
    return is_equal_files("tmp", gt_out);
}

void sample_tests() {
    assert(("incorrect sample latest", check_test("tests/sample_input", "tests/sample_output_latest", DealType::Latest)));
    assert(("incorrect sample oldest", check_test("tests/sample_input", "tests/sample_output_oldest", DealType::Oldest)));
}

int main() {
	sample_tests();
    std::cout << "All tests passed\n";
}