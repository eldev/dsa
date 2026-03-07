// https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/
class Solution {
private:
    const vector<vector<long>> legalMoves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    };

    void bfs(const vector<vector<int>>& grid, vector<vector<bool>>& used, long n, long m, long i, long j) const {
        queue<pair<long,long>> q;
        used[i][j] = true;
        q.push(make_pair(i, j));
        while (!q.empty()) {
            auto f = q.front();
            q.pop();
            for (const auto& move : legalMoves) {
                long ii = f.first + move[0], jj = f.second + move[1];
                if (ii < 0 || ii >= n || jj < 0 || jj >= m) continue;
                if (used[ii][jj] || grid[ii][jj] != 1) continue;

                used[ii][jj] = true;
                q.push(make_pair(ii, jj));
            }
        }
    }

    int islandsCount(const vector<vector<int>>& grid) const {
        long n = grid.size(), m = grid[0].size();
        vector<vector<bool>> used(n, vector<bool>(m, false));
        int islands = 0;
        for (long i = 0; i < n; i++) {
            for (long j = 0; j < m; j++) {
                if (grid[i][j] == 1 && !used[i][j]) {
                    islands++;
                    if (islands > 1) return islands; // нет смысла рассматривать все острова
                    bfs(grid, used, n, m, i, j);
                }
            }
        }
        return islands;
    }

    long defineIslandSize(const vector<vector<int>>& grid) const {
        long n = grid.size(), m = grid[0].size();
        long size = 0;
        for (long i = 0; i < n; i++) {
            for (long j = 0; j < m; j++) {
                if (grid[i][j] != 1) continue;
                size++;
            }
        }
        return size;
    }

    // search articulation point
    void hasArticulationPoint(const vector<vector<int>>& grid, bool& articulationPoint) const {
        long n = grid.size(), m = grid[0].size();
        long timer = 0;
        vector<vector<long>> tin(n, vector<long>(m));
        vector<vector<long>> up(n, vector<long>(m));
        vector<vector<bool>> used(n, vector<bool>(m, false));
        for (long i = 0; i < n; i++) {
            for (long j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    dfs(grid, timer, tin, up, used, articulationPoint, i, j, -1, -1);
                    return;
                }
            }
        }
    }

    void dfs(const vector<vector<int>>& grid, long& timer, vector<vector<long>>& tin, vector<vector<long>>& up, vector<vector<bool>>& used, bool& articulationPoint, long ui, long uj, long pi, long pj) const {
        if (articulationPoint) return; // already found
        
        long n = grid.size(), m = grid[0].size();

        tin[ui][uj] = timer++;
        up[ui][uj] = tin[ui][uj];
        used[ui][uj] = true;
        int childrenCount = 0;

        for (const auto& move : legalMoves) {
            long ii = ui + move[0], jj = uj + move[1];
            if (ii < 0 || ii >= n || jj < 0 || jj >= m) continue;
            if (grid[ii][jj] != 1) continue;
            if (ii == pi && jj == pj) continue;
            if (!used[ii][jj]) {
                childrenCount++;
                dfs(grid, timer, tin, up, used, articulationPoint, ii, jj, ui, uj);
                up[ui][uj] = min(up[ui][uj], up[ii][jj]);
                if (up[ii][jj] >= tin[ui][uj] && pi != -1) {
                    articulationPoint = true;
                    return;
                }
            } else {
                up[ui][uj] = min(up[ui][uj], tin[ii][jj]);
            }
        }

        if (pi == -1 && childrenCount > 1) {
            articulationPoint = true;
        }
    }
public:
    // Рассмотрим разные случаи:
    // 1) если > 1 островов, то return 0
    // 2) если 0 островов, то return 0
    // 3) пусть у нас 1 остров. Но если он состоит из 1 или 2 клеток,
    // то return 1 или 2 (зависит от кол-ва клеток).
    // Пусть есть 1 остров, но он состоит из > 2 клеток.
    // Тогда надо понять, есть ли хоть 1 точка сочленения в этом графе?
    // Если есть, то ответ будет 1 (убираем эту точку).
    // Иначе ответ будет 2, т.к. всегда можно найти угловую граничную точку
    // и отрезать ее от всего остального острова двумя превращениями.
    // [1, 1, ...]
    // [1, ...]
    // Отрезаем клетки (0, 1) и (1,0)
    // [1, 0, ...]
    // [0, ...]. В итоге самая угловая левая клетка будет за 2 дня отрезана.
    int minDays(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        int islands = islandsCount(grid);
        if (islands != 1) return 0;

        long size = defineIslandSize(grid);
        if (size <= 2) return size;

        bool articulationPoint = false;
        hasArticulationPoint(grid, articulationPoint);
        return articulationPoint ? 1 : 2;
    }
};
