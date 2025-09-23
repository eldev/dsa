// https://leetcode.com/problems/min-cost-to-connect-all-points

// Prim's algorithm for a dense graph.
class Prim {
private:
    pair<long, long> getMinEdge(size_t n, const set<long>& used, const set<long>& notused, const vector<vector<long>>& g) {
        bool found = false;
        pair<long, long> minEdge;
        long minWeight = std::numeric_limits<long>::max();
        for (long u : used) {
            for (long v : notused) {
                if (g[u][v] <= minWeight) {
                    minWeight = g[u][v];
                    minEdge = make_pair(u, v);
                    found = true;
                }
            }
        }
        if (!found) return make_pair(-1, -1);
        return minEdge;
    }
public:
    long minCostConnectPoints(size_t n, const vector<vector<long>>& g) {
        long totalMinCost = 0;
        set<long> used;
        set<long> notused;

        // Start from vertex 0.
        used.insert(0);
        for (int i = 1; i < n; i++) notused.insert(i);

        // We added vertex 0, so (n-1) vertices remain to be added.
        for (size_t iteration = 0; iteration < n - 1; iteration++) {
            auto e = getMinEdge(n, used, notused, g);
            long u = e.first, v = e.second;
            if (u == -1 && v == -1) {
                // No MST!
                return -1; // But actually in this task it is not possible.
            }
            // Add v to the used set and remove it from the notused set.
            used.insert(v);
            notused.erase(v);
            totalMinCost += g[u][v];
        }
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
