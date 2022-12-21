class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int mask = 0;
        for (auto num: nums) {
            mask ^= num;
        }
        int first_num = 0;
        for (long long num: nums) {
            if (2 * (num & mask) >= mask) {
                first_num ^= num;
            }
        }
        return {first_num, mask ^ first_num};
    }
};
