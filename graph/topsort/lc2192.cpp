// https://leetcode.com/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/
class Solution {
public:
    // Time:
    //   1. iterate through edges (O(E))
    //   2. iterate through vertices, i.e. initialization of a queue (O(V))
    //   3. each vertex considered once in the Kahn's algorithm
    //   but we need to consider all outgoing edges (O(E))
    //   and we need to copy ancestors => O(V * V)
    // => total O(E + V + E + V*V)=O(E + V*V)
    // Space: O(E + V + V*V) = O(E + V*V)
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        vector<int> indegree(n, 0);
        for (const auto& edge : edges) {
            int from = edge[0], to = edge[1];
            indegree[to]++;
            g[from].push_back(to);
        }

        vector<set<int>> ancestors(n);
        // Kahn's algorithm (topological sorting)
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) q.push(i);
        }
        
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int to : g[cur]) {
                indegree[to]--;
                if (indegree[to] == 0) q.push(to);
                for (int ancestor : ancestors[cur]) ancestors[to].insert(ancestor);
                ancestors[to].insert(cur);
            }
        }

        vector<vector<int>> ans;
        ans.reserve(n);
        for (int i = 0; i < n; i++) ans.push_back(vector<int>(ancestors[i].begin(), ancestors[i].end()));
        return ans;
    }
};
