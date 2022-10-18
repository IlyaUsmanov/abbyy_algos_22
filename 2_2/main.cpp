class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        map<int, int> counter;
        for (auto num: nums) {
            counter[num]++;
        }
        vector<int> unique_nums;
        vector<int> unique_nums_counts;
        for (auto kv: counter) {
            unique_nums.push_back(kv.first);
            unique_nums_counts.push_back(kv.second);
        }
        vector<int> cur;
        vector<vector<int>> unique_counts;
        idsSubsets(unique_counts, unique_nums_counts, cur);
        vector<vector<int>> res;
        for (int i = 0; i < unique_counts.size(); i++) {
            vector<int> cur_res;
            for (int j = 0; j < unique_nums.size(); j++) {
                for (int k = 0; k < unique_counts[i][j]; k++) {
                    cur_res.push_back(unique_nums[j]);
                }
            }
            res.push_back(cur_res);
        }
        return res;
    }
private:
    void idsSubsets(vector<vector<int>>& unique_counts, vector<int>& ids, vector<int>& cur) {
        if (ids.size() == cur.size()) {
            unique_counts.push_back(cur);
            return;
        }
        int cur_id = cur.size();
        for (int i = 0; i <= ids[cur_id]; i++) {
            cur.push_back(i);
            idsSubsets(unique_counts, ids, cur);
            cur.pop_back();
        }
    }
};
