class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        vector<vector<int>> result(2);
        vector<vector<int>> g(n);
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1];
            g[u].push_back(i);
            g[v].push_back(i);
        }
        int real_mst = mst(n, g, edges);
        cout << real_mst<<endl;
        for (int i = 0; i < n; i++) {
            for (auto edge_id: g[i]) {
                auto &edge = edges[edge_id];
                if (edge[0] != i) {
                    continue;
                }
                int w = edge[2];
                edge[2]++;
                if (real_mst != mst(n, g, edges)) {
                    result[0].push_back(edge_id);
                } else {
                    edge[2] = 0;
                    if (real_mst == mst(n, g, edges) + w) {
                        result[1].push_back(edge_id);
                    }
                }
                edge[2] = w;
            }
        }
        return result;
    }
private:
    int mst(int n, vector<vector<int>> &g, vector<vector<int>>& edges) {
        int result = 0;
        set<pair<int, int>> candidates;
        vector<int> connect_cost(n, -1);
        candidates.insert({0, 0});
        connect_cost[0] = 0;
        while (!candidates.empty()) {
            auto [cost, v] = *candidates.begin();
            // cout << v << " " << cost << endl;
            candidates.erase({cost, v});
            connect_cost[v] = -2;
            result += cost;
            for (auto edge_id: g[v]) {
                auto edge = edges[edge_id];
                int u = edge[1] + edge[0] - v, w = edge[2];
                if (connect_cost[u] != -2 && (connect_cost[u] == -1 || connect_cost[u] > w)) {
                    candidates.erase({connect_cost[u], u});
                    connect_cost[u] = w;
                    candidates.insert({connect_cost[u], u});
                    
                }
            }
        }
        return result;
    }
};
