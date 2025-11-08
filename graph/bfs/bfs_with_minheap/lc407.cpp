// https://leetcode.com/problems/trapping-rain-water-ii/
// Пробовал использовать vector<>(h, i, j) вместо Cell,
// но с векторами ловил TLE (думаю, у вектора накладные расходы на конструкторе/деструкторе).

class Solution {
private:
    const vector<vector<int>> moves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    };
    class Cell {
    public:
        int h;
        int i;
        int j;

        Cell(int h, int i, int j)
            : h(h), i(i), j(j) {}

        bool operator<(const Cell& other) const {
            // Reverse comparison to simulate a min-heap
            return h >= other.h;
        }
    };
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size(), n = heightMap[0].size();
        priority_queue<Cell> pq; // min heap
        vector<vector<int>> minH(m, vector<int>(n, std::numeric_limits<int>::max())); // +inf
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 || i == m-1 || j == 0 || j == n-1) {
                    minH[i][j] = heightMap[i][j];
                    pq.push(Cell(minH[i][j], i, j));
                }
            }
        }
        while (!pq.empty()) {
            auto f = pq.top();
            pq.pop();
            int h = f.h, i = f.i, j = f.j;
            if (minH[i][j] < h) continue; // mini-optimization
            for (const auto& move : moves) {
                int ii = i + move[0], jj = j + move[1];
                if (ii < 0 || ii >= m || jj < 0 || jj >= n) continue;
                if (minH[ii][jj] <= max(h, heightMap[ii][jj])) continue;
                minH[ii][jj] = max(h, heightMap[ii][jj]);
                pq.push(Cell(minH[ii][jj], ii, jj));
            }
        }

        int total = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (minH[i][j] > heightMap[i][j])
                    total += minH[i][j] - heightMap[i][j];
            }
        }
        return total;
    }
};
