// https://leetcode.com/problems/critical-connections-in-a-network/description/

class Solution {
private:
    long timer = 0;
    vector<long> tin;
    vector<long> up;
    vector<bool> used;
    vector<vector<int>> bridges; // answer

    void dfs(const vector<vector<int>>& g, int u, int p) {
        tin[u] = ++timer;
        up[u] = tin[u];
        used[u] = true;

        for (int to : g[u]) {
            if (to == p) continue;
            if (!used[to]) {
                dfs(g, to, u);
                up[u] = min(up[u], up[to]);
            } else {
                up[u] = min(up[u], tin[to]);
            }
        }

        if (up[u] == tin[u] && p != -1) {
            // bridge
            bridges.push_back({p, u});
        }
    }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        tin = vector<long>(n);
        up = vector<long>(n);
        used = vector<bool>(n, false);

        vector<vector<int>> g(n, vector<int>());
        for (auto& edge: connections) {
            int u = edge[0], v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(g, 0, -1); // -1 means there is no parent for starting vertex
        return this->bridges;
    }
};
