// https://leetcode.com/problems/minimum-cost-to-convert-string-i/
// TLE because of copying string objects.
// See FloydWarshall directory with more effective approach.

class Solution {
private:
    struct Step {
        long long cost;
        string curStr;
        size_t nextCharIdx;
        Step(long long cost, string s, size_t nextIdx) : cost(cost), curStr(s),
            nextCharIdx(nextIdx) {}
        bool operator<(const Step& rhs) const {
            return this->cost >= rhs.cost;
        }
    };
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        // the graph can have multiple edges,
        // in this case, need to choose the edge with minimum cost.
        unordered_map<char, unordered_map<char, int>> g;
        for (size_t i = 0; i < original.size(); i++) {
            char from = original[i], to = changed[i];
            int c = cost[i];
            if (g.find(from) == g.end()) {
                g[from] = unordered_map<char, int>();
            }
            if (g[from].find(to) == g[from].end()) g[from][to] = c;
            else g[from][to] = min(g[from][to], c);
        }

        // Dijkstra's algorithm
        unordered_map<string, long long> transformsWithMinCost;
        transformsWithMinCost[source] = 0;

        // minheap by first field (cost)
        priority_queue<Step> pq;
        pq.push(Step(transformsWithMinCost[source], source, 0));
        while (!pq.empty()) {
            long long curCost = pq.top().cost;
            string curStr = pq.top().curStr;
            size_t startIdx = pq.top().nextCharIdx;
            pq.pop();

            if (curStr == target) return curCost; // found

            if (transformsWithMinCost[curStr] < curCost) continue;

            for (size_t i = startIdx; i < curStr.size(); i++) {
                if (curStr[i] == target[i]) continue;
                char from = curStr[i];
                for (auto const& [to, w] : g[from]) {
                    curStr[i] = to;
                    long long newCost = curCost + w;
                    size_t nextIdx = startIdx;
                    if (target[i] == curStr[i]) { // mini-optimization in order to skip the first letters that are already considered (but TLE anyway).
                        nextIdx++;
                    }
                    if (transformsWithMinCost.find(curStr) == transformsWithMinCost.end() || newCost < transformsWithMinCost[curStr]) {
                        transformsWithMinCost[curStr] = newCost;
                        pq.push(Step(newCost, curStr, nextIdx));
                    }
                }
                break;
            }
        }
        return -1;
    }
};
