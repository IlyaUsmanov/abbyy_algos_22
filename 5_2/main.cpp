class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<int> dist(n);
        vector<bool> used(n);
        for (int i = 0; i < n; i++) {
            dist[i] = get_dist(points[0], points[i]);
        }
        used[0] = true;
        int result = 0;
        for (int _ = 0; _ < n - 1; _++) {
            int point_id = -1;
            for (int j = 0; j < n; j++) {
                if (!used[j] && (point_id == -1 || dist[point_id] > dist[j])) {
                    point_id = j;
                }
            }
            used[point_id] = true;
            result += dist[point_id];
            for (int j = 0; j < n; j++) {
                dist[j] = min(dist[j], get_dist(points[point_id], points[j]));
            }
        }
        return result;
    }
private:
    int get_dist(vector<int> p1, vector<int> p2) {
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
    }
};
