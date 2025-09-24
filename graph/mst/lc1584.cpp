// https://leetcode.com/problems/min-cost-to-connect-all-points

// Prim's algorithm for a dense graph.
// Time Complexity: O(N^2)
class Prim {
public:
    long minCostConnectPoints(size_t n, const vector<vector<long>>& g) {
        vector<bool> used(n, false);
        // parent[i] is a parent vertex of the i'th vertex in the MST.
        vector<long> parent(n, -1);
        // minDist[i] is a weight of the edge (parent[i] <-> i) in the MST.
        vector<long> minDist(n, std::numeric_limits<long>::max());

        minDist[0] = 0;
        parent[0] = -1; // the vertex 0 would be a root of the MST
        for (size_t iteration = 0; iteration < n; iteration++) {
            long to = -1; // the next vertex that should be added to the MST
            for (long i = 0; i < n; i++) {
                if (!used[i] && (to == -1 || minDist[i] < minDist[to])) {
                    to = i;
                }
            }
            if (to == -1) {
                return -1; // No MST
            }

            used[to] = true;

            // The new 'to' vertex was added to the MST,
            // so need to re-calculate minDist and parent for the remaining vertices
            // that are not in the MST.
            for (long newTo = 0; newTo < n; newTo++) {
                if (!used[newTo] && g[to][newTo] < minDist[newTo]) {
                    minDist[newTo] = g[to][newTo];
                    parent[newTo] = to;
                }
            }
        }

        long totalMinCost = 0;
        for (long c : minDist) totalMinCost += c;
        return totalMinCost;
    }
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        size_t n = points.size();
        // Connect each pair of points with a weighted edge.
        vector<vector<long>> g(n, vector<long>(n));
        for (int i = 0; i < n; i++) {
            long ix = points[i][0], iy = points[i][1];
            for (int j = 0; j < n; j++) {
                long jx = points[j][0], jy = points[j][1];
                g[i][j] = g[j][i] = abs(ix - jx) + abs(iy - jy);
            }
        }
        // Use Prim's algorithm for dense graphs to define
        // the min cost of the MST.
        return Prim().minCostConnectPoints(n, g);
    }
};
