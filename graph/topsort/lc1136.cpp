// https://leetcode.com/problems/parallel-courses
// DFS, Kahn, (possible) cycle
class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<vector<int>> g(n);
        vector<int> indegree(n, 0);
        for (const auto& edge : relations) {
            int from = edge[0], to = edge[1];
            from--; to--; // indexing from 0
            g[from].push_back(to);
            indegree[to]++; // incoming edge
        }

        queue<pair<int,int>> q; // vertex, current depth
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(make_pair(i, 1));
            }
        }
        int maxDepth = 0;
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            int from = p.first, depth = p.second;
            maxDepth = max(maxDepth, depth);
            for (int to : g[from]) {
                indegree[to]--;
                if (indegree[to] == 0) q.push(make_pair(to, depth + 1));
            }
        }
        // need to check if all indegree is 0
        for (int i = 0; i < n; i++) if (indegree[i] > 0) return -1; // we have a cycle
        return maxDepth;
    }
};
