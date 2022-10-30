class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if (parenthesis.find(n) != parenthesis.end()) {
            return parenthesis[n];
        }
        if (n == 0) {
            return {""};
        }
        vector<string> result;
        for (int k = 0; k < n; k++) {
            auto lefts = generateParenthesis(k);
            auto rights = generateParenthesis(n - k - 1);
            for (auto left: lefts) {
                for (auto right: rights) {
                    result.push_back("(" + left + ")" + right);
                }
            }
        }
        parenthesis[n] = result;
        return result;
    }
private:
    map<int, vector<string>> parenthesis;
};
