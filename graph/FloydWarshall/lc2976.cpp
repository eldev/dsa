// https://leetcode.com/problems/minimum-cost-to-convert-string-i/
// Also see an attempt using Dijkstra algorithm (TLE).

class Solution {
private:
    const long long INF = std::numeric_limits<long long>::max();
    vector<vector<long long>> FloydWarshall(const vector<unordered_map<int, int>>& charsGraph) const {
        vector<vector<long long>> minCosts(26, vector<long long>(26, INF));
        // dp init
        for (int i = 0; i < 26; i++) {
            minCosts[i][i] = 0;
            for (auto const& [to, cost] : charsGraph[i]) {
                minCosts[i][to] = cost;
            }
        }
        // dp step
        for (int k = 0; k < 26; k++) {
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < 26; j++) {
                    if (minCosts[i][k] == INF || minCosts[k][j] == INF) continue; // no edge
                    minCosts[i][j] = min(minCosts[i][j], minCosts[i][k] + minCosts[k][j]);
                }
            }
        }
        return minCosts;
    }
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        // 1. Find a min cost for each possible char transformation.
        vector<unordered_map<int, int>> charsGraph(26, unordered_map<int,int>());
        for (size_t i = 0; i < original.size(); i++) {
            int from = original[i] - 'a', to = changed[i] - 'a';
            int c = cost[i];
            if (charsGraph[from].find(to) == charsGraph[from].end()) {
                charsGraph[from][to] = c;
                continue;
            }
            charsGraph[from][to] = min(charsGraph[from][to], c);
        }

        // 2. Define a total cost for source -> target transformation (if it is possible).
        auto minCharCosts = FloydWarshall(charsGraph);
        long long ans = 0;
        for (size_t i = 0; i < source.size(); i++) {
            if (source[i] == target[i]) continue;
            int from = source[i] - 'a';
            int to = target[i] - 'a';
            if (minCharCosts[from][to] == INF) return -1;
            ans += minCharCosts[from][to];
        }
        return ans;
    }
};
