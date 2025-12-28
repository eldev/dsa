// https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/
class Solution {
private:
    typedef long long ll;
    const ll INF = std::numeric_limits<ll>::max();

    vector<vector<ll>> Dijkstra(int n, const vector<vector<pair<ll,ll>>>& g) const {
        vector<vector<ll>> parents(n);
        vector<ll> minDist(n, INF);
        priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq; // minheap by dist (the first field of the pair)
        minDist[0] = 0;
        pq.push(make_pair(minDist[0], 0));
        while (!pq.empty()) {
            auto p = pq.top();
            pq.pop();
            ll curCost = p.first, curNode = p.second;
            if (curCost > minDist[curNode]) continue;

            for (const auto edge : g[curNode]) {
                ll to = edge.first, edgeCost = edge.second;
                if (curCost + edgeCost < minDist[to]) {
                    parents[to] = vector<ll>();
                    parents[to].push_back(curNode);
                    minDist[to] = curCost + edgeCost;
                    pq.push(make_pair(minDist[to], to));
                } else if (curCost + edgeCost == minDist[to]) {
                    parents[to].push_back(curNode);
                }
            }
        }

        return parents;
    }

    vector<set<int>> constructDag(int n, const vector<vector<ll>>& parents) const {
        vector<set<int>> dag(n);
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(n-1);
        visited[n-1] = true;
        while (!q.empty()) {
            int to = q.front();
            q.pop();
            for (ll from : parents[to]) {
                dag[from].insert(to);
                if (!visited[from]) {
                    visited[from] = true;
                    q.push(from);
                }
            }
        }
        return dag;
    }

    int calculateTotalNumberOfWays(int n, vector<set<int>>& dag) const {
        // Topological sorting (Kahn's algorithm)
        vector<ll> indeg(n, 0);
        for (int u = 0; u < n; u++) {
            for (int to : dag[u]) {
                indeg[to]++;
            }
        }

        vector<ll> dp(n, 0);
        dp[0] = 1;
        queue<ll> q;
        for (int u = 0; u < n; u++) {
            if (indeg[u] == 0) q.push(u);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int to : dag[u]) {
                dp[to] += dp[u];
                dp[to] %= (1000000000 + 7);
                indeg[to]--;
                if (indeg[to] == 0) q.push(to);
            }
        }

        return dp[n-1];
    }

public:
    int countPaths(int n, vector<vector<int>>& roads) {
        // 1. Use the Dijkstra's algorithm to define the shortest paths
        vector<vector<pair<ll,ll>>> g(n);
        for (const auto& edge : roads) {
            ll u = edge[0], v = edge[1], cost = edge[2];
            g[u].push_back(make_pair(v, cost));
            g[v].push_back(make_pair(u, cost));
        }
        auto parents = Dijkstra(n, g);

        // 2. Construct a DAG.
        auto dag = constructDag(n, parents);

        // 3. Calculate a total number of ways to arrive at n-1 intersection.
        return calculateTotalNumberOfWays(n, dag);
    }
};
