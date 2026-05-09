// https://leetcode.com/problems/the-maze-iii/

class Solution {
private:
    const int INF = std::numeric_limits<int>::max();

    const vector<vector<int>> legalMoves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    };

    struct Cell {
        int i, j;
        int dist;
        Cell(int i, int j, int d): i(i), j(j), dist(d) {}
        bool operator<(const Cell& rhs) const {
            return dist > rhs.dist;
        }
    };

    Cell getFinalCell(const vector<vector<int>>& maze, int i, int j, int di, int dj, const vector<int>& dstn) const {
        int n = maze.size(), m = maze[0].size();
        int dist = 0;
        while (i >= 0 && i < n && j >= 0 && j < m && maze[i][j] == 0) {
            // по условию при встрече с dstn мяч останавливается,
            // поэтому мы должны вернуть эту клетку
            if (i == dstn[0] && j == dstn[1])
                return Cell(i, j, dist);
            dist++;
            i += di;
            j += dj;
        }
        i -= di;
        j -= dj;
        dist--;
        return Cell(i, j, dist);
    }

    string Dijkstra(const vector<vector<int>>& maze, const vector<int>& source, const vector<int>& destination) const {
        string ans;
        bool found = false;
        int n = maze.size(), m = maze[0].size();
        vector<vector<int>> minDist(n, vector<int>(m, INF));
        // parent[i][j] будет содержать вектор пар (iParent,jParent), откуда
        // пришли в клетку (i,j). Это надо, чтобы потом
        // найти лексикографически минимальный вариант из возможных.
        vector<vector<vector<pair<int,int>>>> parent(
            n, vector<vector<pair<int,int>>>(m, vector<pair<int,int>>())
        );
        priority_queue<Cell> pq;
        minDist[source[0]][source[1]] = 0;
        pq.push(Cell(source[0], source[1], minDist[source[0]][source[1]]));

        while (!pq.empty()) {
            const auto f = pq.top();
            pq.pop();
            int i = f.i, j = f.j, dist = f.dist;
            if (i == destination[0] && j == destination[1]) {
                found = true;
                // конечная точка достигнута, поэтому нет смысла
                // рассматривать дальнейшие шаги алгоритма, т.к.
                // в этом случае путь будет только больше.
                continue;
            }
            for (const auto& move : legalMoves) {
                auto to = getFinalCell(maze, i, j, move[0], move[1], destination);
                if (to.dist == 0) continue;
                to.dist += dist;
                if (minDist[to.i][to.j] > to.dist) {
                    minDist[to.i][to.j] = to.dist;
                    // Очищаем вектор parent, т.к. нашли путь короче.
                    parent[to.i][to.j].clear();
                    parent[to.i][to.j].push_back(make_pair(i,j));
                    pq.push(to);
                } else if (minDist[to.i][to.j] == to.dist) {
                    // у нас могут быть несколько вариантов
                    // достичь клетки (to.i, to.j) с одинаковым
                    // коротким расстоянием. Поэтому надо добавить в вектор parent.
                    parent[to.i][to.j].push_back(make_pair(i,j));
                    pq.push(to);
                }
            }
        }
        if (!found) return "impossible";

        // DFS-ом (в обратном направлении) надо из возможных вариантов найти
        // лексикографически минимальный вариант.
        vector<char> curPath;
        dfs(parent, destination[0], destination[1], source[0], source[1], ans, curPath);
        return ans;
    }

    void dfs(const vector<vector<vector<pair<int,int>>>>& parent, int i, int j, int iStart, int jStart, string& ans, vector<char>& curPath) const {
        if (i == iStart && j == jStart) {
            string p(curPath.rbegin(), curPath.rend()); // added in the reversed order
            if (ans == "" || p < ans) ans = p;
            return;
        }
        for (const auto& p : parent[i][j]) {
            char direction = defineDirection(i, j, p.first, p.second);
            curPath.push_back(direction);
            dfs(parent, p.first, p.second, iStart, jStart, ans, curPath);
            curPath.pop_back();
        }
    }

    char defineDirection(int i, int j, int pi, int pj) const {
        if (i < pi && j == pj) return 'u';
        if (i > pi && j == pj) return 'd';
        if (i == pi && j < pj) return 'l';
        if (i == pi && j > pj) return 'r';
        return 0;
    }

public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        if (maze.empty() || maze[0].empty()) return "impossible";
        return Dijkstra(maze, ball, hole);
    }
};
