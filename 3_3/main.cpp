class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector <int> res(amount + 1, -1);
        res[amount] = 0;
        for (auto coin: coins) {
            for (int state = amount; state >= coin; state--) {
                if (res[state] == -1) {
                    continue;
                }
                int new_state = state - coin;
                if (res[new_state] == -1 || res[new_state] > res[state] + 1) {
                    res[new_state] = res[state] + 1;
                }
            }
        }
        return res[0];
    }
};
