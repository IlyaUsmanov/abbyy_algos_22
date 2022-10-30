#include <set>

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> cur;
        vector<bool> used(nums.size());
        sort(nums.begin(), nums.end());
        permuteUniqueRec(nums, res, used, cur);
        return res;
    }
private:
    void permuteUniqueRec(vector<int>& nums, vector<vector<int>>& res, vector<bool>& used, vector<int>& cur) {
        if (cur.size() == nums.size()) {
            res.push_back(cur);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) {
                continue;
            }
            used[i] = true;
            cur.push_back(nums[i]);
            permuteUniqueRec(nums, res, used, cur);
            cur.pop_back();
            used[i] = false;
            while (i + 1 != nums.size() && nums[i] == nums[i + 1]) {
                i++;
            }
        }
    }
};
