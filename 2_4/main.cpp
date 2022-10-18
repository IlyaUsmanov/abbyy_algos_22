class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        back_track(board, 0);
    }
private:
    static int const sub_box_size = 3;
    static int const field_size = 9;
    
    set<char> get_all_possible() {
        set <char> result;
        for (int i = 0; i < field_size; i++) {
            result.insert('1' + i);
        }
        return result;
    }
    
    void erase_lines(vector<vector<char>> &board, set<char> &possible, pair<int, int> coords) {
        for (int i = 0; i < field_size; i++) {
            possible.erase(board[coords.first][i]);
            possible.erase(board[i][coords.second]);
        }
    }
    
    int move_to_sub_box_start(int coord) {
        return coord - coord % sub_box_size;
    }
    
    pair<int, int> get_sub_box_start(pair<int, int> coords) {
        return {move_to_sub_box_start(coords.first), move_to_sub_box_start(coords.second)};
    }
    
    void erase_sub_box(vector<vector<char>> &board, set<char> &possible, pair<int, int> coords) {
        auto sub_box_start = get_sub_box_start(coords);
        for (int i = 0; i < sub_box_size; i++) {
            for (int j = 0; j < sub_box_size; j++) {
                possible.erase(board[sub_box_start.first + i][sub_box_start.second + j]);
            }
        }
    }
    
    void erase_duplicates(vector<vector<char>> &board, set<char> &possible, pair<int, int> coords) {
        erase_lines(board, possible, coords);
        erase_sub_box(board, possible, coords);
    }
    
    pair<int, int> decode_into_coord(int coord_encoded) {
        return {coord_encoded / field_size, coord_encoded % field_size};
    }
    
    bool back_track(vector<vector<char>> &board, int coord_encoded_to_start) {
        for (int coord_encoded = coord_encoded_to_start; coord_encoded < field_size * field_size; coord_encoded++) {
            auto [i, j] = decode_into_coord(coord_encoded);
            if (board[i][j] != '.') {
                continue;
            }
            auto possible = get_all_possible();
            erase_duplicates(board, possible, {i, j});
            if (possible.empty()) {
                return false;
            }
            for (auto value: possible) {
                board[i][j] = value;
                if (back_track(board, coord_encoded + 1)) {
                    return true;
                }
                board[i][j] = '.';
            }
            return false;
        }
        return true;
    }
};
