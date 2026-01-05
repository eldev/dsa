// https://leetcode.com/problems/all-paths-from-source-lead-to-destination
// DFS + Cycle
class Solution {
private:
    enum Colour {WHITE, GRAY, BLACK};
    void dfs(const vector<vector<int>>& g, vector<Colour>& states, int cur, const int destination, bool& ans) const {
        if (!ans) return;
        states[cur] = GRAY;
        if (g[cur].size() == 0 && cur != destination) {
            // there is a leaf which does not equal to destination
            ans = false;
            return;
        }
        for (int to : g[cur]) {
            if (states[to] == GRAY) {
                // there is a cycle
                ans = false;
                return;
            } else if (states[to] == WHITE) {
                dfs(g, states, to, destination, ans);
            }
        }
        states[cur] = BLACK;
    }
public:
    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<vector<int>> g(n);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].push_back(v); // directed graph
        }

        vector<Colour> states(n, WHITE);
        bool ans = true;
        dfs(g, states, source, destination, ans);
        if (states[destination] != BLACK) return false;
        return ans;
    }
};
