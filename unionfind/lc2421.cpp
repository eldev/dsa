// https://leetcode.com/problems/number-of-good-paths
class Solution {
private:
    class UnionFind {
    private:
        vector<int> parent;
        vector<int> rank;
    public:
        UnionFind(int n) {
            rank.resize(n, 0);
            parent.resize(n, 0);
            for (int i = 0; i < n; i++) parent[i] = i;
        }
        int find(int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }
        void Union(int x, int y) {
            int px = find(x);
            int py = find(y);
            if (px == py) return;
            if (rank[px] < rank[py]) {
                parent[px] = py;
            } else if (rank[px] > rank[py]) {
                parent[py] = px;
            } else {
                parent[px] = py;
                rank[py]++;
            }
        }
    };
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        // 1. Prepare
        vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        map<int, vector<int>> valToVertices;
        for (int i = 0; i < vals.size(); i++) {
            int val = vals[i];
            if (valToVertices.count(val) == 0) valToVertices[val] = vector<int>();
            valToVertices[val].push_back(i);
        }
        UnionFind uf(n);

        // 2. Need to form a graph from the smalles values to highest.
        int ans = 0;
        for (const auto& [val, vertices] : valToVertices) {
            for (int vertex : vertices) {
                for (int neighbour : g[vertex]) {
                    if (vals[neighbour] <= val) {
                        uf.Union(neighbour, vertex);
                    }
                }
            }

            unordered_map<int, int> ufCounter;
            for (int vertex : vertices) {
                int parent = uf.find(vertex);
                if (ufCounter.count(parent) == 0) ufCounter[parent] = 0;
                ufCounter[parent]++;
            }
            for (const auto& [ufParnet, count] : ufCounter) {
                ans += (count * (count+1)/2);
            }
        }
        return ans;
    }
};
