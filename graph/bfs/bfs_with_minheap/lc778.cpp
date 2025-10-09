// https://leetcode.com/problems/swim-in-rising-water

class Solution {
private:
    const vector<vector<long>> moves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    };
public:
    int swimInWater(vector<vector<int>>& grid) {
        long n = grid.size();
        vector<vector<long>> minDist(n, vector<long>(n, std::numeric_limits<long>::max()));
        auto comp = [](const vector<long>& a, const vector<long>& b) {
            return a[2] < b[2];
        };
        priority_queue<vector<long>, std::vector<vector<long>>, decltype(comp)> pq(comp); // min heap for vectors

        // Start from (0, 0)
        minDist[0][0] = grid[0][0];
        pq.push({0, 0, minDist[0][0]});

        while (!pq.empty()) {
            auto f = pq.top();
            pq.pop();
            long i = f[0], j = f[1], dist = f[2];

            if (minDist[i][j] < dist) continue;
            for (const auto& mv : moves) {
                long ii = i + mv[0], jj = j + mv[1];
                if (ii < 0 || ii >= n || jj < 0 || jj >= n) continue;
                long t = max<long>(grid[ii][jj], dist);
                if (minDist[ii][jj] <= t) continue;
                minDist[ii][jj] = t;
                pq.push({ii, jj, minDist[ii][jj]});
            }
        }
        return minDist[n-1][n-1];
    }
};
