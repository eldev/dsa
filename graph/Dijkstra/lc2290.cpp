// https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner

class Solution {
private:
    const vector<vector<int>> moves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    };
    class Cell {
    public:
        int i, j;
        int dist;
        Cell(int i, int j, int dist): i(i), j(j), dist(dist) {}
        bool operator<(const Cell& rhs) const {
            // Reverse comparison to simulate a min-heap
            return this->dist >= rhs.dist;
        }
    };
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        priority_queue<Cell> pq;
        vector<vector<int>> minDist(m, vector<int>(n, std::numeric_limits<int>::max()));
        minDist[0][0] = 0;
        pq.push(Cell(0, 0, minDist[0][0]));
        while (!pq.empty()) {
            auto f = pq.top();
            pq.pop();
            int i = f.i, j = f.j, dist = f.dist;
            if (minDist[i][j] < dist) continue;
            for (const auto& move : moves) {
                int ii = i + move[0], jj = j + move[1];
                if (ii < 0 || ii >= m || jj < 0 || jj >= n) continue;
                int newDist;
                if (grid[ii][jj] == 1) {
                    newDist = dist + 1;
                } else {
                    newDist = dist;
                }
                if (minDist[ii][jj] <= newDist) continue;
                minDist[ii][jj] = newDist;
                pq.push(Cell(ii, jj, minDist[ii][jj]));
            }
        }
        return minDist[m-1][n-1];
    }
};
