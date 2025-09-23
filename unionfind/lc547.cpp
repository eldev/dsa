// https://leetcode.com/problems/number-of-provinces

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
public:
    UnionFind(size_t n) {
        parent.resize(n);
        // at the beginning, each city is its own parent.
        for (size_t i = 0; i < n; i++) parent[i] = i;
        rank.resize(n, 0);
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]); // path compression
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

    int getCount() {
        // need to find a count of unique parents
        set<int> unique;
        for (size_t i = 0; i < parent.size(); i++) {
            // need to call find() in order to update parent of it
            // (path compression). Otherwise, it's possible to calculate
            // irrelevant parent.
            find(i);

            unique.insert(parent[i]);
        }
        return unique.size();
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        UnionFind uf(isConnected.size());
        for (int i = 0; i < isConnected.size(); i++) {
            for (int j = 0; j < isConnected[i].size(); j++) {
                if (isConnected[i][j] == 1) {
                    uf.Union(i, j);
                }
            }
        }
        return uf.getCount();
    }
};
