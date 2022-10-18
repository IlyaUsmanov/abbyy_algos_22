class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> cur;
        vector<bool> used(nums.size());
        permuteUniqueRec(nums, res, used, cur);
        return res;
    }
private:
    void permuteUniqueRec(vector<int>& nums, vector<vector<int>>& res, vector<bool>& used, vector<int>& cur) {
        if (cur.size() == nums.size()) {
            res.push_back(cur);
            return;
        }
        set <int> cur_used;
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] || cur_used.find(nums[i]) != cur_used.end()) {
                continue;
            }
            used[i] = true;
            cur_used.insert(nums[i]);
            cur.push_back(nums[i]);
            permuteUniqueRec(nums, res, used, cur);
            cur.pop_back();
            used[i] = false;
        }
    }
};
