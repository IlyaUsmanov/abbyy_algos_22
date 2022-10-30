class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        map<int, int> counter;
        for (auto num: nums) {
            counter[num]++;
        }
        vector<vector<int>> subsets;
        vector<int> cur;
        
        idsSubsets(subsets, counter.begin(), counter.end(), cur);
        
        return subsets;
    }
private:
    void idsSubsets(vector<vector<int>>& subsets, map<int, int>::iterator counter_it, map<int, int>::iterator counter_end, vector<int>& cur) {
        if (counter_it == counter_end) {
            subsets.push_back(cur);
            return;
        }
        auto [num, count] = *counter_it;
        counter_it++;
        for (int i = 0; i <= count; i++) {
            idsSubsets(subsets, counter_it, counter_end, cur);
            cur.push_back(num);
        }
        for (int _ = 0; _ <= count; _++) {
            cur.pop_back();
        }
    }
};
