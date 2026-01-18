// https://leetcode.com/problems/word-search
class Solution {
private:
    const vector<vector<int>> moves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    };
    bool dfs(const vector<vector<char>>& board, int i, int j, vector<vector<bool>>& used, const string& word, const int strIdx) const {
        if (strIdx == word.size() - 1) {
            // мы запускали dfs только при условии, что следующая буква word
            // соответствовала букве в board[i][j].
            // Поэтому если это уже последний индекс word,
            // то мы нашли слово.
            return true;
        }
        int n = board.size(), m = board[0].size();
        for (const auto& move : moves) {
            int ii = i + move[0], jj = j + move[1];
            if (ii < 0 || ii >= n || jj < 0 || jj >= m) continue;
            if (used[ii][jj]) continue;
            if (board[ii][jj] != word[strIdx+1]) continue;
            // backtracking
            used[ii][jj] = true;
            bool isPossible = dfs(board, ii, jj, used, word, strIdx+1);
            if (isPossible) return true;
            used[ii][jj] = false;
        }
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        if (n == 0) return word.empty();
        int m = board[0].size();
        vector<vector<bool>> used(n, vector<bool>(m, false));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (word[0] != board[i][j]) continue;
                used[i][j] = true;
                if (dfs(board, i, j, used, word, 0)) return true;
                used[i][j] = false; // остальные позиции будут возвращены к false внутри dfs
            }
        }
        return false;
    }
};
