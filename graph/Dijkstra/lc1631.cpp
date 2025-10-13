// https://leetcode.com/problems/path-with-minimum-effort/
// Вариация применения алгоритма Дейкстры: тот же принцип,
// но будем использовать минимальную кучу, чтобы в приоритете доставать те клетки,
// у которых минимальная разница высот между соседними клетками (см. ниже коммент).
class Solution {
private:
    const vector<pair<int, int>> legalMoves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    };

public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        return Dijkstra(heights);
    }

    // Approach 1: Dijkstra
    struct AdjacentCell {
        long i, j;
        long dist;
    };
    int Dijkstra(vector<vector<int>>& heights) {
        long n = heights.size(), m = heights[0].size();
        vector<vector<vector<AdjacentCell>>> g(n, vector<vector<AdjacentCell>>(m));
        for (long i = 0; i < n; i++) {
            for (long j = 0; j < m; j++) {
                for (const auto& lm : legalMoves) {
                    long ii = i + lm.first, jj = j + lm.second;
                    if (ii < 0 || ii >= n || jj < 0 || jj >= m) continue;
                    long dist = std::abs(heights[i][j] - heights[ii][jj]);
                    g[i][j].push_back({ii, jj, dist});
                }
            }
        }

        auto cmp = [](const AdjacentCell& lhs, const AdjacentCell& rhs) {
            return lhs.dist > rhs.dist; // in order to make a MIN heap
        };
        priority_queue<AdjacentCell, std::vector<AdjacentCell>, decltype(cmp)> pq(cmp);
        const long INF = std::numeric_limits<long>::max();
        vector<vector<long>> minDist(n, vector<long>(m, INF));
        minDist[0][0] = 0;
        pq.push({0, 0, minDist[0][0]});
        while (!pq.empty()) {
            const auto c = pq.top();
            pq.pop();
            for (const auto& adj: g[c.i][c.j]) {
                long curDist = max(adj.dist, c.dist); // здесь отличие от оригинального алгоритма
                if (minDist[adj.i][adj.j] <= curDist) continue;
                minDist[adj.i][adj.j] = curDist;
                pq.push({adj.i, adj.j, minDist[adj.i][adj.j]});
            }
        }
        return minDist[n-1][m-1];
    }
};