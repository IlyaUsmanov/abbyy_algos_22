/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        return generateTreesRec(n, 0);
    }
private:
    vector<TreeNode*> generateTreesRec(int n, int start_val) {
        if (n == 0) {
            return vector<TreeNode*>(1, nullptr);
        }
        vector<TreeNode*> res;
        for (int i = 1; i <= n; i++) {
            auto lefts = generateTreesRec(i - 1, start_val);
            auto rights = generateTreesRec(n - i, start_val + i);
            for (auto left: lefts) {
                for (auto right: rights) {
                    auto root = new TreeNode(i + start_val);
                    root->left = left;
                    root->right = right;
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};
