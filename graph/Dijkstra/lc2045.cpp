// https://leetcode.com/problems/second-minimum-time-to-reach-destination
class Solution {
private:
    int calcNextTime(int curTime, const int time, const int change) const {
        int ans = curTime;
        if ((curTime / change) % 2 == 1) {
            // wait for a green signal
            ans += change - (curTime % change);
        }
        ans += time;
        return ans;
    }
    // approach 1 (TLE)
    int approach1(int n, vector<vector<int>>& edges, int time, int change) {
        vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            u--; v--; // indexing from 0
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // min heap: {time to reach vertex, vertex}
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push(make_pair(0, 0));
        vector<int> destTimes;
        destTimes.reserve(2);
        while (destTimes.size() < 2) {
            auto top = pq.top();
            pq.pop();
            int curTime = top.first, u = top.second;
            if (u == n-1) {
                // reach destination vertex
                if (destTimes.empty() || destTimes[0] < curTime)
                    destTimes.push_back(curTime); // we need a value which is strictly larger than the minimum value
                if (destTimes.size() >= 2) break;
            }
            int toTime = calcNextTime(curTime, time, change);
            for (int to : g[u]) {
                pq.push(make_pair(toTime, to));
            }
        }
        return destTimes[1];
    }

    const int INF = std::numeric_limits<int>::max();

    int approach2(int n, const vector<vector<int>>& edges, int time, int change) {
        vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            u--; v--; // indexing from 0
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> minDistances(n, INF);
        vector<int> secondMinDistances(n, INF);

        // min heap: {time to reach vertex, vertex}
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        minDistances[0] = 0;
        pq.push(make_pair(0, 0));

        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            int curTime = top.first, u = top.second;

            int toTime = calcNextTime(curTime, time, change);
            for (int to : g[u]) {
                if (toTime < minDistances[to]) {
                    secondMinDistances[to] = minDistances[to];
                    minDistances[to] = toTime;
                } else if (minDistances[to] < toTime && toTime < secondMinDistances[to]) {
                    secondMinDistances[to] = toTime;
                } else {
                    continue;
                }
                pq.push(make_pair(toTime, to));
            }
        }
        return secondMinDistances[n-1];
    }

    // approach 3: actually, we can use a BFS approach
    // since all edges have the same weight (time).
    // Time complexity would be better than the Dijkstra approach.
    // (see Editorial).
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        return approach2(n, edges, time, change);
    }
};
