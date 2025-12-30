// https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph
class Solution {
private:
    struct UnionFind {
        vector<int> parent;
        vector<int> rank;
        UnionFind(size_t n) {
            parent.resize(n);
            for (int i = 0; i < n; i++) parent[i] = i;
            rank.resize(n, 0);
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
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        // Note: since the graph is undirected and it is possible
        // to visit the same edge or vertex more than once,
        // a connected component of vertices will have
        // the same minimum cost = w1 & w2 & ... & wi
        // (w1, w2, ... wi are edge weights among vertices
        // of this connected component). So we can use UnionFind
        // to union vertices of the same connected component
        // and keep mincosts in a separate vector.
        UnionFind uf(n);
        vector<int> mincost(n, std::numeric_limits<int>::max());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            int uPrevCost = mincost[uf.find(u)];
            int vPrevCost = mincost[uf.find(v)];
            uf.Union(u, v);
            int parent = uf.find(u);
            mincost[parent] = min(mincost[parent], uPrevCost & vPrevCost & mincost[parent] & w);
        }

        vector<int> ans(query.size());
        for (int i = 0; i < query.size(); i++) {
            int u = query[i][0], v = query[i][1];
            int pu = uf.find(u);
            int pv = uf.find(v);
            if (pu != pv) ans[i] = -1;
            else ans[i] = mincost[pu];
        }
        return ans;
    }
};
