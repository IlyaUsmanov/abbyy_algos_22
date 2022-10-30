class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s2.size() + s1.size() != s3.size()) {
            return false;
        }
        vector <bool> dp(s2.size() + 1);
        dp[0] = true;
        for (int i = 1; i <= s3.size(); i++) {
            for (int j = s2.size(); j >= 0; j--) {
                if (j > i) {
                    continue;
                }
                if (dp[j] && i - j - 1 < s1.size() && s3[i - 1] == s1[i - j - 1]) {
                    dp[j] = true;
                } else if (j != 0 && dp[j - 1] && s3[i - 1] == s2[j - 1]) {
                    dp[j] = true;
                } else {
                    dp[j] = false;
                }
            }
        }
        return dp[s2.size()];
    }
};
