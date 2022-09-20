#pragma once

#include "process_deals.hpp"
#include <optional>
#include <vector>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <algorithm>
#include <deque>
#include <optional>

// Deal



bool Deal::operator< (const Deal &other) const {
    if (_stock != other._stock) {
        return _stock < other._stock;
    }
    if (_close_operation_id == other._close_operation_id) {
        return _open_operation_id < other._open_operation_id;
    }
    if (!_close_operation_id) {
        return false;
    }
    if (!other._close_operation_id) {
        return true;
    }
    return _close_operation_id.value() < other._close_operation_id.value();
}

std::ostream& operator<< (std::ostream& out, const Deal& deal) {
    std::string position_type;
    if (deal._position_type == PositionType::Long) {
        position_type = "long";
    } else {
        position_type = "short";
    }
    out << deal._stock << " " << deal._stocks_amount << " " << deal._open_price << " ";
    if (deal._close_price) {
        out << deal._close_price.value() << " ";
    } else {
        out << "- ";
    }
    if (deal._profit) {
        out << deal._profit.value() << " ";
    } else {
        out << "- ";
    }
    out << position_type << " " << deal._open_operation_id << " ";
    if (deal._close_operation_id) {
        out << deal._close_operation_id.value();
    }
    out << "\n";
}


// Operation

std::optional<Deal> Operation::get_complete_deal(Operation &other) {
    if (_operation_type == other._operation_type) {
        return std::nullopt;
    }
    size_t stocks_to_get = std::min(_stocks_amount, other._stocks_amount);
    _stocks_amount -= stocks_to_get;
    other._stocks_amount -= stocks_to_get;
    int open_price = _stock_price, close_price = other._stock_price;
    int profit = (close_price - open_price) * stocks_to_get;
    if (_operation_type == OperationType::Sell) {
        profit *= -1;
    }
    size_t open_operation_id = _operation_id, close_operation_id = other._operation_id;
    PositionType position_type = (_operation_type == OperationType::Buy) ? PositionType::Long : PositionType::Short;
    return Deal{
        _stock_id,
        stocks_to_get,
        open_price,
        close_price,
        profit,
        position_type,
        open_operation_id,
        close_operation_id
    };
}

Deal Operation::get_pending_deal() const {
    PositionType position_type = (_operation_type == OperationType::Buy) ? PositionType::Long : PositionType::Short;
    return Deal{
        _stock_id,
        _stocks_amount,
        _stock_price,
        std::nullopt,
        std::nullopt,
        position_type,
        _operation_id,
        std::nullopt
    };
}

std::string Operation::get_stock_id() const {
    return _stock_id;
}

bool Operation::no_stocks() const {
    return _stocks_amount == 0;
}

std::istream& operator>> (std::istream& in, Operation& operation) {
    std::string operation_type;
    in >> operation._operation_id >> operation_type >> operation._stock_id >> operation._stocks_amount >> operation._stock_price;
    operation._operation_type = parse_operation_type(operation_type);
    return in;
}

std::vector<Deal> process_operation(Operation new_operation, std::unordered_map<std::string, std::deque<Operation>> &operations_by_stock_id, const DealType &deal_type) {
    std::vector<Deal> result;
    std::string stock_id = new_operation.get_stock_id();

    while (operations_by_stock_id[stock_id].size() != 0 && !new_operation.no_stocks()) {
        Operation &operation = operations_by_stock_id[stock_id].back();
        auto deal_opt = operation.get_complete_deal(new_operation);
        if (!deal_opt) {
            break;
        }
        result.push_back(deal_opt.value());
        if (operation.no_stocks()) {
            operations_by_stock_id[stock_id].pop_back();
        }
    }

    if (new_operation.no_stocks()) {
        return result;
    }
    if (deal_type == DealType::Latest) {
        operations_by_stock_id[stock_id].push_back(new_operation);
    } else {
        operations_by_stock_id[stock_id].push_front(new_operation);
    }
    return result;
}

std::vector<Deal> postprocess_operations(std::unordered_map<std::string, std::deque<Operation>> &operations_by_stock_id) {
    std::vector<Deal> deals;

    for (auto &[stock_id, operations] : operations_by_stock_id) {
        for (auto &operation : operations) {
            deals.push_back(operation.get_pending_deal());
        }
    }

    return deals;
}

std::vector<Deal> process_operations(const std::vector<Operation> &operations, const DealType &deal_type) {
    std::vector<Deal> deals;
    std::unordered_map<std::string, std::deque<Operation>> operations_by_stock_id;

    for (auto operation: operations) {
        auto new_deals = process_operation(operation, operations_by_stock_id, deal_type);
        deals.insert(
            deals.begin(),
            std::make_move_iterator(new_deals.begin()),
            std::make_move_iterator(new_deals.end())
        );
    }

    auto new_deals = postprocess_operations(operations_by_stock_id);
    deals.insert(
        deals.begin(),
        std::make_move_iterator(new_deals.begin()),
        std::make_move_iterator(new_deals.end())
    );

    std::sort(deals.begin(), deals.end());
    return deals;
}

void process_deals(const std::string &in_file, const std::string &out_file, const DealType &deal_type) {
    auto operations = read_data<Operation>(in_file);
    auto deals = process_operations(operations, deal_type);
    write_data<Deal>(deals, out_file);
}