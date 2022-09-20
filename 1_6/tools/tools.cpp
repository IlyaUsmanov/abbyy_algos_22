#include <cassert>
#include <string>
#include <vector>
#include <fstream>

enum DealType { Latest, Oldest };
enum OperationType { Sell, Buy };
enum PositionType { Short, Long };

DealType parse_deal_type(const std::string &deal_type) {
    if (deal_type == "latest") {
        return DealType::Latest;
    } else if (deal_type == "oldest") {
        return DealType::Oldest;
    }
    assert(("incorrect deal type", false));
}

OperationType parse_operation_type(const std::string &operation_type) {
    if (operation_type == "buy") {
        return OperationType::Buy;
    } else if (operation_type == "sell") {
        return OperationType::Sell;
    }
    assert(("incorrect operation type", false));
}

PositionType parse_position_type(const std::string &position_type) {
    if (position_type == "short") {
        return PositionType::Short;
    } else if (position_type == "long") {
        return PositionType::Long;
    }
    assert(("incorrect position type", false));
}

template <typename T>
std::vector<T> read_data(const std::string &in_file) {
    std::ifstream in(in_file);
    std::vector<T> result;

    while (!in.eof()) {
        T value;
        std::string operation_type;
        in >> value;
        result.push_back(value);
    }

    return result;
}

template <typename T>
void write_data(const std::vector<T> &values, const std::string &out_file) {
    std::ofstream out(out_file);

    for (auto value : values) {
        out << value;
    }
}