class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int cur_min = prices[0];
        int result = 0;
        for (auto price: prices) {
            cur_min = min(price, cur_min);
            result = max(result, price - cur_min);
        }
        return result;
    }
};
