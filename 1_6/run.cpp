#include <iostream>
#include <cassert>
#include <string>
#include "process_deals/process_deals.cpp"

int main(int argc, char *argv[]) {
    assert(("Exactly 3 arguments should be passed", argc == 4));
    std::string in_file = argv[1], out_file = argv[2], deal_type = argv[3];
    process_deals(in_file, out_file, parse_deal_type(deal_type));
}