// https://leetcode.com/problems/path-with-maximum-probability

// На самом деле в этой задаче это "типа" алгоритм Дейкстры
// (алгоритм Дейкстры предназначен для поиска кратчайших путей, а в этой задаче поиск пути с максимальной вероятностью).
// Единственная причина, по которой алгоритм может быть применен в этой задаче - это то, что произведения
// вероятностей (значения <= 1) не увеличиваются, поэтому не могут возникнуть циклы.
// Классический алгоритм Дейкстры как раз не может применяться для поиска максимальных путей,
// т.к. он будет наворачивать циклы бесконечно, тем самым увеличивая стоимость пути до бесконечности.

class Dijkstra {
public:
    double maxProbability(int n, const vector<vector<pair<int, double>>>& g, int start_node, int end_node) {
        vector<int> parent(n, -1);
        vector<double> maxProb(n, 0);
        // max heap
        priority_queue<pair<double,int>> pq;

        parent[start_node] = -1;
        maxProb[start_node] = 1.0;
        pq.push(make_pair(maxProb[start_node], start_node));
        while (!pq.empty()) {
            double w = pq.top().first;
            int u = pq.top().second;
            pq.pop();

	    // На самом деле следующий if можно удалить,
	    // т.к. если maxProb[u] уже посчитан и значение больше, чем w,
	    // то ранее ниже в цикле for всего его соседи уже были посчитаны с учетом наибольшего maxProb[u] (см. "if (curProb > maxProb[v])")
	    // соответственно, для текущего w мы уже ничего в pq не добавим. Для эффективности добавим этот if,
	    // но на корректность алгоритма никак не влияет. 
            if (w < maxProb[u]) continue; // just for efficiency

            for (const auto& edge : g[u]) {
                int v = edge.first;
                double w_uv = edge.second;
                double curProb = w * w_uv;
                if (curProb > maxProb[v]) {
                    maxProb[v] = curProb;
                    parent[v] = u;
                    pq.push(make_pair(maxProb[v], v));
                }
            }
        }
        if (parent[end_node] == -1) {
            // there is no path from start_node to target_node.
            return 0;
        }
        return maxProb[end_node];
    }
};

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        vector<vector<pair<int, double>>> g(n, vector<pair<int,double>>());
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1];
            double w = succProb[i];
            g[u].push_back(make_pair(v, w));
            g[v].push_back(make_pair(u, w));
        }
        return Dijkstra().maxProbability(n, g, start_node, end_node);
    }
};
