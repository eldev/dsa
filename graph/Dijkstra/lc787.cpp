// https://leetcode.com/problems/cheapest-flights-within-k-stops/

class Solution {
private:
    class Cell {
    public:
        int i;
        int steps;
        int dist;
        Cell(int i, int steps, int dist): i(i), steps(steps), dist(dist) {}
        bool operator<(const Cell& rhs) const {
            return this->dist >= rhs.dist; // for min-heap
        }
    };

    int Dijkstra(int n, vector<vector<pair<int,int>>> g, int src, int dst, int K) const {
        priority_queue<Cell> pq;
        pq.push(Cell(src, 0, 0));
        vector<int> minStops(n, std::numeric_limits<int>::max());

        while (!pq.empty()) {
            auto f = pq.top();
            pq.pop();
            int cur = f.i, steps = f.steps, dist = f.dist;
            if (cur == dst) return dist;
	    // В этой задаче не используем minDist и проверку типа "if (minDist[cur] < dist) continue"
	    // вместо этого используем minStops.
	    // Если steps >= minStops[cur], то это значит, что cur уже был рассмотрена ранее
	    // (т.к. алгоритм Дейкстры жадным образом сначала рассматривает вершины, до которых мин расстояние)
	    // то есть в предыдущий раз и меньше дистанция была, и меньше кол-во остановок.
            if (steps >= minStops[cur] || steps > K) continue;
            minStops[cur] = steps;
 
            for (const auto& p : g[cur]) {
                int to = p.first, cost = p.second;
                int newDist = dist + cost;
                pq.push(Cell(to, steps + 1, newDist));
            }
        }
        return -1;
    }

public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int,int>>> g(n, vector<pair<int,int>>());
        for (const auto& f : flights) {
            int from = f[0], to = f[1], cost = f[2];
            g[from].push_back(make_pair(to, cost));
        }
        return Dijkstra(n, g, src, dst, k);
    }
};
