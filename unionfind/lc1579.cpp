// https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/
class Solution {
private:
    bool isTraversable(int n, const vector<vector<pair<int,int>>>& g, int personType) const {
        vector<bool> visited(n, false);
        queue<int> q;
        visited[0] = true;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& edge : g[u]) {
                int type = edge.first, to = edge.second;
                if (type == 3 || type == personType) {
                    if (visited[to]) continue;
                    visited[to] = true;
                    q.push(to);
                }
            }
        }
        for (bool v : visited) if (!v) return false;
        return true;
    }

    class UnionFind {
    private:
        vector<int> parent;
        vector<int> rank;
    public:
        UnionFind(int n) {
            rank.resize(n, 0);
            parent.resize(n);
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

    int rmEdgesByPersonType(const vector<vector<int>>& edges, UnionFind& uf, int personType) {
        int ans = 0;
        for (const auto& edge: edges) {
            int type = edge[0], u = edge[1], v = edge[2];
            if (type != personType) continue;
            u--;
            v--;
            int pu = uf.find(u);
            int pv = uf.find(v);
            if (pu == pv) ans++;
            else uf.Union(u, v);
        }
        return ans;
    }
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        // 1. Let's check if graph is traversable
        vector<vector<pair<int,int>>> g(n, vector<pair<int,int>>());
        for (const auto& edge : edges) {
            int type = edge[0], u = edge[1], v = edge[2];
            u--;
            v--;
            g[u].push_back(make_pair(type, v));
            g[v].push_back(make_pair(type, u));
        }
        if (!isTraversable(n, g, 1)) return -1;
        if (!isTraversable(n, g, 2)) return -1;

        // 2. If the graph is traversable, we should remove only extra edges.
        // Firstly, remove extra edges by type 3.
        UnionFind uf1(n), uf2(n);
        int ans = 0;
        for (const auto& edge: edges) {
            int type = edge[0], u = edge[1], v = edge[2];
            if (type != 3) continue;
            u--;
            v--;
            int pu = uf1.find(u);
            int pv = uf1.find(v);
            if (pu == pv) ans++;
            else {
                uf1.Union(u, v);
                uf2.Union(u, v);
            }
        }

        // 3. Remove extra edges for each person.
        ans += rmEdgesByPersonType(edges, uf1, 1);
        ans += rmEdgesByPersonType(edges, uf2, 2);

        return ans;
    }
};
