class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int N = edges.size();
        unordered_map<int, int> end_of_edge;
        int possible_answer_1 = -1, possible_answer_2 = -1; 
        int last_in_circle = -1;
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            if (merge(u, v)) {
                last_in_circle = i;
            }
            if (end_of_edge.count(v) == 0) {
                end_of_edge[v] = i;
            } else {
                possible_answer_1 = end_of_edge[v];
                possible_answer_2 = i;
            }
        }
        if (possible_answer_1 == -1) {
            return edges[last_in_circle];
        }
        
        clear_dsu();
        cout << possible_answer_1 << " " << possible_answer_2 << endl;
        for (int i = 0; i < edges.size(); i++) {
            if (i == possible_answer_2) {
                continue;
            }
            int u = edges[i][0];
            int v = edges[i][1];
            if (merge(u, v)) {
                return edges[possible_answer_1];
            }
        }
        return edges[possible_answer_2];
    }
private:
    unordered_map<int, int> ancestor;
    unordered_map<int, int> size;
    
    void clear_dsu() {
        ancestor.clear();
        size.clear();
    }
    
    int get_ancestor(int v) {
        if (ancestor[v] == 0) {
            return v;
        }
        return ancestor[v] = get_ancestor(ancestor[v]);
    }
    
    bool merge(int u, int v) {
        u = get_ancestor(u);
        v = get_ancestor(v);
        if (u == v) {
            return true;
        }
        if (size[u] > size[v]) {
            swap(u, v);
        }
        size[v] += size[u] + 1;
        ancestor[u] = v;
        return false;
    }
};
