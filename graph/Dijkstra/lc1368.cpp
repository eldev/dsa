// https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/

class Solution {
private:
    const unordered_map<int, vector<int>> signToMove = {
        {1, {0, 1}},
        {2, {0, -1}},
        {3, {1, 0}},
        {4, {-1, 0}},
    };
    const int costToChangeSign = 1;

    class Cell {
    public:
        int i, j;
        int dist;
        Cell(int i, int j, int d): i(i), j(j), dist(d) {}
        bool operator<(const Cell& rhs) const {
            return this->dist >= rhs.dist; // to simulate a min-heap
        }
    };
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> minDist(m, vector<int>(n, std::numeric_limits<int>::max()));
        priority_queue<Cell> pq;
        minDist[0][0] = 0;
        pq.push(Cell(0, 0, minDist[0][0]));
        while (!pq.empty()) {
            auto f = pq.top();
            pq.pop();
            int i = f.i, j = f.j, dist = f.dist;
            if (minDist[i][j] < dist) continue; // mini-optimization (not required)
            for (const auto& pair : signToMove) {
                int sign = pair.first;
                int ii = i + pair.second[0], jj = j + pair.second[1];
                if (ii < 0 || ii >= m || jj < 0 || jj >= n) continue;
                int newDist = dist;
                if (sign != grid[i][j]) {
                    // if a sign of the current cell does not match
                    // to the current move, we should add a cost of sign change
                    newDist += costToChangeSign;
                }
                if (minDist[ii][jj] <= newDist) continue;
                minDist[ii][jj] = newDist;
                pq.push(Cell(ii, jj, minDist[ii][jj]));
            }

        }
        return minDist[m-1][n-1];
    }
};
