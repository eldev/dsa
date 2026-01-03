// https://leetcode.com/problems/redundant-connection
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
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        UnionFind uf(n+1); // vertices indexing from 1
        pair<int,int> ans; // "If there are multiple answers, return the answer that occurs last in the input"
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            if (uf.find(u) == uf.find(v)) {
                ans = make_pair(u, v);
            } else {
                uf.Union(u, v);
            }
        }
        return {ans.first, ans.second};
    }

    // invalid solution.
    // See input: [[9,10],[5,8],[2,6],[1,5],[3,8],[4,9],[8,10],[4,10],[6,8],[7,9]]
    // vector<int> invalidSolution(vector<vector<int>>& edges) {
    //     int n = edges.size();
    //     vector<bool> used(n + 1, false);
    //     pair<int,int> ans; // "If there are multiple answers, return the answer that occurs last in the input"
    //     for (const auto& edge : edges) {
    //         int u = edge[0], v = edge[1];
    //         if (used[u] && used[v]) ans = make_pair(u, v);
    //         used[u] = used[v] = true;
    //     }
    //     return {ans.first, ans.second};
    // }
};
