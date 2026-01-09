// https://leetcode.com/problems/number-of-distinct-islands/
// BFS, сравнение шагов BFS.
// Здесь решение не очень оптимальное, т.к. есть два вложенных цикла в п. 2
// и каждое сравнение островов - это O(N*M) в худшем случае. То есть O(N^2 * M^2).
// Follow-up: как-то вычислить хэш для каждого острова (bfs шагов)
// и каждый хэш хранить в set. Таким образом у нас будет O(N*M).
class Solution {
private:
    const vector<vector<int>> moves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    };
    struct Island {
        // необходимо воспроизвести каждый шаг BFS,
        // то есть будем использовать 2-мерный bfsSteps,
        // чтобы записывать какие индексы moves были использованы для каждой
        // отдельной клетки. Одномерным вектором не обойтись,
        // см. контрпример:
        // [[1,1,0],[0,1,1],[0,0,0],[1,1,1],[0,1,0]]
        // тут есть 2 острова, которые не равны,
        // но если использовать одномерный bfsSteps,
        // то мы запишем [3, 1, 3] для обоих островов, хотя они разные.
        vector<vector<int>> bfsSteps;
        bool operator==(const Island& rhs) const {
            if (bfsSteps.size() != rhs.bfsSteps.size()) return false;
            for (int i = 0; i < bfsSteps.size(); i++) {
                if (bfsSteps[i].size() != rhs.bfsSteps[i].size()) return false;
                for (int j = 0; j < bfsSteps[i].size(); j++) {
                    if (bfsSteps[i][j] != rhs.bfsSteps[i][j]) return false;
                }
            }
            return true;
        }
    };

    Island bfs(const vector<vector<int>>& grid, vector<vector<bool>>& used, int startRow, int startCol) const {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> bfsSteps;
        queue<pair<int,int>> q;
        used[startRow][startCol] = true;
        q.push(make_pair(startRow, startCol));
        while (!q.empty()) {
            auto f = q.front();
            q.pop();
            int i = f.first, j = f.second;
            vector<int> curSteps;
            for (int idx = 0; idx < moves.size(); idx++) {
                const auto& move = moves[idx];
                int ii = i + move[0], jj = j + move[1];
                if (ii < 0 || ii >= n || jj < 0 || jj >= m) continue;
                if (grid[ii][jj] == 0 || used[ii][jj]) continue;

                curSteps.push_back(idx);
                used[ii][jj] = true;
                q.push(make_pair(ii, jj));
            }
            bfsSteps.push_back(curSteps);
        }
        return Island{bfsSteps: bfsSteps};
    }
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        // 1. BFS to identify each island
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> used(n, vector<bool>(m, false));
        vector<Island> islands;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 0 || used[i][j]) continue;
                Island island = bfs(grid, used, i, j);
                islands.push_back(island);
            }
        }

        // 2. Compare islands by BFS steps
        int ans = islands.size();
        // можно использовать UnionFind, но для простоты используем
        // вспомогательный сет, чтобы повторно не проверять уже использованные острова.
        unordered_set<int> usedIslands;
        for (int i = 0; i < islands.size(); i++) {
            usedIslands.insert(i);
            for (int j = i + 1; j < islands.size(); j++) {
                if (usedIslands.find(j) != usedIslands.end()) continue;
                if (islands[i] == islands[j]) {
                    usedIslands.insert(j);
                    ans--;
                }
            }
        }

        return ans;
    }
};
