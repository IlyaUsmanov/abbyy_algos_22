#pragma once

#include <string>
#include <optional>
#include <unordered_map>
#include <deque>
#include "tools/tools.cpp"


class Deal {
private:
    std::string _stock;
    size_t _stocks_amount;
    int _open_price;
    std::optional<int> _close_price;
    std::optional<int> _profit;
    PositionType _position_type;
    size_t _open_operation_id;
    std::optional<size_t> _close_operation_id;

    friend std::ostream& operator<< (std::ostream& out, const Deal& deal);
public:
    Deal(
        std::string stock,
        size_t stocks_amount,
        int open_price,
        std::optional<int> close_price,
        std::optional<int> profit,
        PositionType position_type,
        size_t open_operation_id,
        std::optional<size_t> close_operation_id
    ) : _stock(stock), _stocks_amount(stocks_amount), _open_price(open_price), _close_price(close_price), _profit(profit),
    _position_type(position_type), _open_operation_id(open_operation_id), _close_operation_id(close_operation_id) {}

    bool operator< (const Deal &other) const;
};


class Operation {
private:
    size_t _operation_id;
    OperationType _operation_type;
    std::string _stock_id;
    size_t _stocks_amount;
    int _stock_price;

    friend std::istream& operator>> (std::istream& in, Operation& operation);
public:
    std::optional<Deal> get_complete_deal(Operation &other);

    Deal get_pending_deal() const;

    std::string get_stock_id() const;

    bool no_stocks() const;
};


std::vector<Deal> process_operation(Operation new_operation, std::unordered_map<std::string, std::deque<Operation>> &operations_by_stock_id, const DealType &deal_type);

std::vector<Deal> postprocess_operations(std::unordered_map<std::string, std::deque<Operation>> &operations_by_stock_id);

std::vector<Deal> process_operations(const std::vector<Operation> &operations, const DealType &deal_type);

void process_deals(const std::string &in_file, const std::string &out_file, const DealType &deal_type);