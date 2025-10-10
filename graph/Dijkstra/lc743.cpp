// https://leetcode.com/problems/network-delay-time/
// Алгоритм Дейкстры, но с ориентированным графом.

class Solution {
public:
    // Dijkstra
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        k--; // indexing from 0
        vector<vector<pair<int, int>>> g(n, vector<pair<int,int>>());
        for (const auto& edge : times) {
            int u = edge[0], v = edge[1], t = edge[2];
            u--; v--;
            g[u].push_back(make_pair(v, t));
        }

        vector<int> parent(n, -1);
        vector<int> minDist(n, std::numeric_limits<int>::max());
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        
        // start from k
        minDist[k] = 0;
        parent[k] = -1;
        pq.push(make_pair(minDist[k], k));
        while (!pq.empty()) {
            int curDist = pq.top().first;
            int vertex = pq.top().second;
            pq.pop();

            for (const auto& edge : g[vertex]) {
                int to = edge.first, dist = edge.second;
                if (curDist + dist >= minDist[to]) continue;
                minDist[to] = curDist + dist;
                parent[to] = vertex;
                pq.push(make_pair(minDist[to], to));
            }
        }
        for (int i = 0; i < n; i++) {
            if (i == k) continue;
            if (parent[i] == -1) return -1;
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, minDist[i]);
        }
        return ans;
    }
};
