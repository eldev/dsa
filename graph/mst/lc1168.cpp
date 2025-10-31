// https://leetcode.com/problems/optimize-water-distribution-in-a-village/
//

class Solution {
private:
    int Prim(const vector<vector<pair<int,int>>>& g) const {
        int n = g.size();
        // min heap (by cost)
        auto comp = [](const pair<int,int>& a, const pair<int,int>& b) {
            return a.second > b.second;
        };
        priority_queue<pair<int,int>, std::vector<pair<int,int>>, decltype(comp)> pq(comp);

        vector<int> minCost(n, std::numeric_limits<int>::max()); // +inf
        vector<int> parent(n, -1);
        vector<bool> visited(n, false);

        // Start from the dummy vertex 0.
        parent[0] = -1;
        minCost[0] = 0;
        pq.push(make_pair(0, minCost[0]));

        while (!pq.empty()) {
            auto f = pq.top();
            pq.pop();
            int vertex = f.first, cost = f.second;
            visited[vertex] = true;
            // if (minCost[vertex] < cost) continue; // mini optimization
            for (const auto& edge : g[vertex]) {
                int to = edge.first, edgeCost = edge.second;

                if (edgeCost >= minCost[to] || visited[to]) continue;
                parent[to] = vertex;
                minCost[to] = edgeCost;
                pq.push({to, minCost[to]});
            }
        }
        for (int i = 1; i < n; i++) { // Note: need to ignore a dummy vertex 0!
            if (parent[i] == -1) return -1; // No MST
        }
        int totalMinCost = 0;
        for (int i = 1; i < n; i++) totalMinCost += minCost[i];
        return totalMinCost;
    }

public:
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        // Idea: add a dummy (additional) vertex 0
        // and each well can be represented as an edge from vertex 0 to the well's vertex
        // with cost == wells[i].
        vector<vector<pair<int,int>>> g(n + 1, vector<pair<int,int>>());
        for (int i = 0; i < wells.size(); i++) {
            g[0].push_back(make_pair(i+1, wells[i]));
            g[i+1].push_back(make_pair(0, wells[i]));
        }
        for (const auto& pipe : pipes) {
            int from = pipe[0], to = pipe[1], cost = pipe[2];
            g[from].push_back(make_pair(to, cost));
            g[to].push_back(make_pair(from, cost));
        }
        return Prim(g);
    }
};
