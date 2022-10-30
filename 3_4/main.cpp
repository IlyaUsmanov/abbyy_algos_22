class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> suf_max(n);
        suf_max[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--) {
            suf_max[i] = max(suf_max[i + 1], height[i + 1]);
        }
        int cur_max = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += max(0, min(cur_max, suf_max[i]) - height[i]);
            cur_max = max(cur_max, height[i]);
        }
        return ans;
    }
};
