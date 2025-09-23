// https://leetcode.com/problems/connecting-cities-with-minimum-cost

// Prim

class Prim {
public:
    int minimumCost(int n, vector<vector<pair<int,int>>>& g) {
        vector<int> minCost(n, std::numeric_limits<int>::max()); // +inf
        vector<int> parent(n, -1);
        vector<bool> visited(n, false);
        // Need to use pairs of < cost, vertex >
        // in order to get an edge with the min cost at each step
        // via q.begin(). But NOTE: g uses a vector of pairs of < vertex, cost > format.
        set<pair<int, int>> q;

        // Start from vertex 0.
        q.insert(make_pair(0, 0));
        minCost[0] = 0;
        int needToVisit = n;
        while (needToVisit-- > 0 && !q.empty()) {
            int u = q.begin()->second;
            q.erase(q.begin());
            visited[u] = true;
            for (pair<int, int>& v : g[u]) {
                int to = v.first, cost = v.second;
                if (!visited[to] && cost < minCost[to]) {
                    q.erase(make_pair(minCost[to], to));
                    minCost[to] = cost;
                    parent[to] = u;
                    q.insert(make_pair(minCost[to], to));
                }
            }
        }

        // Check if a MST was built.
        int mstCost = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                return -1; // no MST!
            }
            mstCost += minCost[i];
        }
        return mstCost;
    }
};

// Kruskal

class UnionFind {
private:
    int n;
    vector<int> p;
    vector<int> rank;
public:
    UnionFind(int n) {
        this->n = n;
        this->rank.resize(n, 0);
        this->p.resize(n);
        for (int i = 0; i < n; i++) p[i] = i;
    }

    int find(int x) {
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
    }

    void Union(int x, int y) {
        int px = find(x), py = find(y);
        if (rank[px] < rank[py]) {
            p[px] = py;
        } else if (rank[px] > rank[py]) {
            p[py] = px;
        } else {
            p[px] = py;
            rank[py]++;
        }
    }
};

class Kruskal {
public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        UnionFind uf(n);
        // Sort by the edge's weight
        sort(connections.begin(), connections.end(), [](const auto& lhs, const auto& rhs) {
            return lhs[2] < rhs[2];
        });
        int totalCost = 0;
        for (const auto& edge : connections) {
            int u = edge[0], v = edge[1], w = edge[2];
            u--; v--;
            if (uf.find(u) != uf.find(v)) {
                // handle edge of the MST

                totalCost += w;
                uf.Union(u, v);
            }
        }
        // If UnionFind unions all vertices of the graph,
        // then the MST was built successfully.
        for (int i = 1; i < n; i++) {
            if (uf.find(i) != uf.find(0)) return -1;
        }

        return totalCost;
    }
};

// Solution

class Solution {
private:
    // 1. Prim's algorithm (Accepted)
    int usePrim(int n, vector<vector<int>>& connections) {
        vector<vector<pair<int,int>>> g(n, vector<pair<int,int>>());
        for (auto edge : connections) {
            int u = edge[0], v = edge[1], cost = edge[2];
            u--; v--; // indexing from 0
            g[u].push_back(make_pair(v, cost));
            g[v].push_back(make_pair(u, cost));
        }
        Prim p;
        return p.minimumCost(n, g);
    }

    // 2. Kruskal's algorithm (Accepted)
    int useKruskal(int n, vector<vector<int>>& connections) {
        Kruskal k;
        return k.minimumCost(n, connections);
    }

public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        return useKruskal(n, connections);
    }
};
