// https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/
// no negative cycles by task's constraints

class Solution {
private:
    const long INF = 1000000+1; // enough for the task's constraints

    vector<vector<long>> FloydWarshall(int n, const vector<vector<pair<int, int>>>& g) const {
        vector<vector<long>> d(n, vector<long>(n, INF));
        // dp init
        for (int i = 0; i < n; i++) {
            d[i][i] = 0;
            for (const auto& e : g[i]) {
                int to = e.first, w = e.second;
                d[i][to] = w;
            }
        }
        // dp step
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }

        return d;
    }
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<pair<int, int>>> g(n, vector<pair<int,int>>());
        for (const vector<int>& edge : edges) {
            int from = edge[0], to = edge[1], w = edge[2];
            g[from].push_back(make_pair(to, w));
            g[to].push_back(make_pair(from, w));
        }

        auto distances = FloydWarshall(n, g);
        int ans = 0;
        int minNeighbors = INF;
        for (int i = 0; i < n; i++) {
            int citiesCount = 0;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (distances[i][j] <= distanceThreshold) citiesCount++;
            }
            if (citiesCount <= minNeighbors) {
                minNeighbors = citiesCount;
                ans = i;
            }
        }
        return ans;
    }
};
