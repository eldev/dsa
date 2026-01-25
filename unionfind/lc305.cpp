// https://leetcode.com/problems/number-of-islands-ii/
class Solution {
private:
    const vector<vector<int>> moves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    };
    class UnionFind {
    private:
        unordered_map<long, long> parent;
        unordered_map<long, long> rank;
        unordered_set<long> uniqueParents;
    public:
        int getUniqueParentsCount() const {
            return uniqueParents.size();
        }
        void addValue(int x) {
            parent[x] = x;
            rank[x] = 0;
            uniqueParents.insert(x);
        }
        long find(long x) {
            if (parent.find(x) == parent.end()) return -1; // not found
            if (parent[x] != x) {
                uniqueParents.erase(parent[x]);
                parent[x] = find(parent[x]);
                uniqueParents.insert(parent[x]);
            }
            return parent[x];
        }
        void Union(long x, long y) {
            long px = find(x);
            if (px == -1) {
                addValue(x);
                px = x;
            }
            long py = find(y);
            if (py == -1) {
                addValue(y);
                py = y;
            }
            if (px == py) return;
            if (rank[px] < rank[py]) {
                uniqueParents.erase(parent[px]);
                parent[px] = py;
            } else if (rank[px] > rank[py]) {
                uniqueParents.erase(parent[py]);
                parent[py] = px;
            } else {
                uniqueParents.erase(parent[px]);
                parent[px] = py;
                rank[py]++;
            }
        }
    };

    long getIdx(long i, long j, long rows) const {
        return i * rows + j;
    }
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        UnionFind uf;
        vector<int> ans;
        ans.reserve(positions.size());
        for (const auto& pos : positions) {
            long i = pos[0], j = pos[1];
            long idx = getIdx(i, j, n);
            if (uf.find(idx) == -1) {
                uf.addValue(idx);
            }

            for (const auto& move : moves) {
                long ii = i + move[0], jj = j + move[1];
                if (ii < 0 || ii >= m || jj < 0 || jj >= n) continue;
                long neighborIdx = getIdx(ii, jj, n);
                if (uf.find(neighborIdx) == -1) continue; // not island
                uf.Union(idx, neighborIdx);
            }

            ans.push_back(uf.getUniqueParentsCount());
        }
        return ans;
    }
};
