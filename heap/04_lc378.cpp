// https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix
class Solution {
private:
    struct Item {
        int val;
        int i, j;
        Item(int val, int i, int j): val(val), i(i), j(j) {}
        bool operator<(const Item& rhs) const {
            return val >= rhs.val;
        }
    };
public:
    // The main idea is to define a min value among all rows.
    // So we can init a minheap by the first values of each row
    // and push the next element of the current row at each step.
    // Time complexity: O(N^2 * logN).
    // Space: O(N) since need to keep at most one value of each row in the heap.
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        if (n == 0) return -1;
        priority_queue<Item> pq; // minheap by val
        // Push the first value of each row
        for (int i = 0; i < n; i++) pq.push(Item(matrix[i][0], i, 0));

        while (!pq.empty()) {
            auto f = pq.top();
            pq.pop();

            if (--k == 0) return f.val;
            int nextCol = f.j + 1;
            if (nextCol >= n) continue;
            pq.push(Item(matrix[f.i][nextCol], f.i, nextCol));
        }
        return -1;
    }
};
