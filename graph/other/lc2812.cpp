// https://leetcode.com/problems/find-the-safest-path-in-a-grid
// BFS + Bin search

class Solution {
private:
    vector<vector<int>> distances;
    const vector<vector<int>> legalMoves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    void findAllDistances(const vector<vector<int>>& grid) {
        size_t n = grid.size();
        distances.resize(n, vector<int>(n, std::numeric_limits<int>::max()));
        vector<vector<bool>> used(n, vector<bool>(n, false));
        queue<vector<int>> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    distances[i][j] = 0;
                    used[i][j] = true;
                    q.push({i, j, distances[i][j]});
                }
            }
        }

        while (!q.empty()) {
            auto f = q.front();
            int i = f[0], j = f[1], curDist = f[2];
            q.pop();
            for (const auto& m : legalMoves) {
                int ii = i + m[0], jj = j + m[1];
                if (ii < 0 || ii >= n || jj < 0 || jj >= n) continue;
                if (used[ii][jj]) continue;

                distances[ii][jj] = curDist + 1;
                used[ii][jj] = true;
                q.push({ii, jj, distances[ii][jj]});
            }
        }
    }

    int getAnswerUsingBinSearch() const {
        int l = -1, r = distances.size();
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (binSearch(m)) l = m;
            else r = m;
        }
        return l;
    }

    bool binSearch(int safenessFactor) const {
        int n = distances.size();
        vector<vector<bool>> used(n, vector<bool>(n, false));
        queue<vector<int>> q;
        used[0][0] = true;
        q.push({0, 0});
        while (!q.empty()) {
            int i = q.front()[0], j = q.front()[1];
            q.pop();
            if (distances[i][j] < safenessFactor) continue;
            if (i == n-1 && j == n-1) {
                return true;
            }
            for (const auto& m : legalMoves) {
                int ii = i + m[0], jj = j + m[1];
                if (ii < 0 || ii >= n || jj < 0 || jj >= n) continue;
                if (used[ii][jj]) continue;

                used[ii][jj] = true;
                q.push({ii, jj});
            }
        }
        return false;
    }

public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        findAllDistances(grid);
        return getAnswerUsingBinSearch();
    }
};
