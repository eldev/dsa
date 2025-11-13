// https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/

class Solution {
private:
    const vector<vector<int>> moves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    };
    class Cell {
    public:
        int i, j;
        int t;
        Cell(int i, int j, int t): i(i), j(j), t(t) {}
        bool operator<(const Cell& rhs) const {
            return this->t >= rhs.t; // for min-heap
        }
    };
public:
    int minimumTime(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        if (m == 0 || n == 0) return -1;
        // Если первые соседние клетки содержат числа > 1,
        // то точно не сможем добраться до клетки (m-1, n-1).
        // Иначе можно просто перемещаться между (0, 0) и (0,1) (например)
        // чтобы намотать любое нужное время (задача не запрещает снова посещать
        // уже посещенные поля).
        if (grid[0][1] > 1 && grid[1][0] > 1) return -1;

        vector<vector<int>> minDist(m, vector<int>(n, std::numeric_limits<int>::max()));
        priority_queue<Cell> pq;

        // Start from (0, 0) at time 0.
        minDist[0][0] = 0;
        pq.push(Cell(0, 0, minDist[0][0]));
        while (!pq.empty()) {
            auto f = pq.top();
            pq.pop();
            int i = f.i, j = f.j, t = f.t;
            if (minDist[i][j] < t) continue;
            for (const auto& move : moves) {
                int ii = i + move[0], jj = j + move[1];
                if (ii < 0 || ii >= m || jj < 0 || jj >= n) continue;
                int newTime;
                if (grid[ii][jj] <= t + 1) {
                    newTime = t + 1;
                } else {
                    // если время соседней клетки (ii, jj) имеет ту же четность,
                    // что и время t, то в (ii, jj) попадем в момент времени 1 + grid[ii][jj],
                    // потому что мы затратим четное кол-во секунд, наматывая время до grid[ii][jj],
                    // между (i, j) и той клеткой, откуда к ней пришли
                    // (1 секунда туда и 1 секунда обратно).
                    // Если разная четность, то попадем в момент времени grid[ii][jj].
                    int diff = (grid[ii][jj] - t) % 2;
                    newTime = grid[ii][jj] + (1 - diff);
                }
                if (minDist[ii][jj] <= newTime) continue;
                minDist[ii][jj] = newTime;
                pq.push(Cell(ii, jj, minDist[ii][jj]));
            }
        }
        return minDist[m-1][n-1];
    }
};
