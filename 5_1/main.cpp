class Solution {
public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        vector<vector<pair<int, long long>>> g(n), inv_g(n);
        for (auto edge: edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            g[u].push_back({v, w});
            inv_g[v].push_back({u, w});
        }
        auto d1 = dijkstra(n, src1, g);
        auto d2 = dijkstra(n, src2, g);
        auto d3 = dijkstra(n, dest, inv_g);
        long long result = -1;
        for (int v = 0; v < n; v++) {
            if (d1[v] == -1 || d2[v] == -1 || d3[v] == -1) {
                continue;
            }
            if (result == -1 || result > d1[v] + d2[v] + d3[v]) {
                result = d1[v] + d2[v] + d3[v];
            }
        }
        return result;
    }
private:
    vector<long long> dijkstra(int n, int from, vector<vector<pair<int, long long>>> &g) {
        set<pair<long long, int>> candidates;
        vector<long long> distances(n, -1);
        candidates.insert({0, from});
        distances[from] = 0;
        while (!candidates.empty()) {
            auto [dist, v] = *candidates.begin();
            candidates.erase({dist, v});
            for (auto [u, w]: g[v]) {
                if (distances[u] == -1 || distances[u] > dist + w) {
                    candidates.erase({distances[u], u});
                    distances[u] = dist + w;
                    candidates.insert({distances[u], u});
                }
            }
        }
        return distances;
    }
};
