class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> used(n, vector<bool>(m));
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (used[i][j] || grid[i][j] != '1') {
                    continue;
                }
                result++;
                dfs(i, j, used, grid);
            }
        }
        
        return result;
    }
private:
    static const int nDirs = 4;
    static constexpr int dx[nDirs] = {0, 0, 1, -1};
    static constexpr int dy[nDirs] = {-1, 1, 0, 0};
    
    bool isInField(int x, int y, const vector<vector<char>> &grid) {
        int n = grid.size();
        int m = grid[0].size();
        return (x >= 0) && (y >= 0) && (x < n) && (y < m);
    }
    
    void dfs(int x, int y, vector<vector<bool>> &used, const vector<vector<char>> &grid) {
        used[x][y] = true;
        for (int shiftId = 0; shiftId < nDirs; shiftId++) {
            int xNew = x + dx[shiftId];
            int yNew = y + dy[shiftId];
            if (!isInField(xNew, yNew, grid) || grid[xNew][yNew] != '1' || used[xNew][yNew]) {
                continue;
            }
            dfs(xNew, yNew, used, grid);
        }
    }
};
