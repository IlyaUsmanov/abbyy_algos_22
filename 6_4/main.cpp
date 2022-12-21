class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> g(n);
        for (auto edge: connections) {
            int u = edge[0], v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<int> tin(n, -1), fup(n);
        int cur_time = 0;
        vector<vector<int>> result;
        for (int v = 0; v < n; v++) {
            if (tin[v] == -1) {
                dfs(v, -1, cur_time, tin, fup, g);
            }
            for (auto u: g[v]) {
                if (fup[u] > tin[v]) {
                    result.push_back({u, v});
                }
            }
        }
        return result;
    }
private:
    void dfs(int v, int parent, int &cur_time, vector<int> &tin, vector<int> &fup, vector<vector<int>> &g) {
        tin[v] = cur_time++;
        fup[v] = tin[v];
        for (auto u: g[v]) {
            if (u == parent) {
                continue;
            }
            if (tin[u] == -1) {
                dfs(u, v, cur_time, tin, fup, g);
                fup[v] = min(fup[v], fup[u]);
            } else {
                fup[v] = min(fup[v], tin[u]);
            }
        }
    }
};
