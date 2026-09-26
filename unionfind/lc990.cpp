// https://leetcode.com/problems/satisfiability-of-equality-equations/
// UnionFind implementation by unordered_map
class Solution {
private:
    struct UnionFind {
        unordered_map<int,int> parent;
        unordered_map<int,int> rank;
        bool contains(int x) const {
            return parent.contains(x);
        }
        void add(int x) {
            parent[x] = x;
            rank[x] = 0;
        }
        int find(int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }
        void Union(int x, int y) {
            int px = find(x);
            int py = find(y);
            if (px == py) return;
            if (rank[px] < rank[py]) {
                parent[px] = py;
            } else if (rank[px] > rank[py]) {
                parent[py] = px;
            } else {
                parent[px] = py;
                rank[py]++;
            }
        }
    };
public:
    // Idea: 1) consider ONLY '==' equations and group them in UnionFind
    // i.e. all equal values will have the same parent in terms of UnionFind.
    // 2) consider ONLY '!=': if one of values are not presented in UnionFind
    // add it as another group. Then need to check if the values have different
    // parents in UF. If values have the same parent => return false.
    // Time: O(E * Ackerman(N)), E=len(equations), N=number of values.
    // Space: O(N)
    bool equationsPossible(vector<string>& equations) {
        UnionFind uf;
        for (const auto& equation : equations) {
            int x = equation[0] - 'a';
            int y = equation[3] - 'a';
            if (equation[1] != '=') continue;
            if (!uf.contains(x)) uf.add(x);
            if (!uf.contains(y)) uf.add(y);
            uf.Union(x, y);
        }

        for (const auto& equation : equations) {
            int x = equation[0] - 'a';
            int y = equation[3] - 'a';
            if (equation[1] != '!') continue;
            // We should add these values as another group
            // if they are not presented in UF.
            // See input like: `["a!=a"]`
            if (!uf.contains(x)) uf.add(x);
            if (!uf.contains(y)) uf.add(y);
            if (uf.find(x) == uf.find(y)) return false;
        }
        return true;
    }
};
