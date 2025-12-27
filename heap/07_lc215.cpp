// https://leetcode.com/problems/kth-largest-element-in-an-array

class Solution {
private:
    // Approach 1 (Acc). Min heap
    // Time: O(N * logK), Space: O(K).
    int useMinHeap(const vector<int>& nums, int k) const {
        priority_queue<int, vector<int>, greater<int>> minheap;
        for (int num : nums) {
            minheap.push(num);
            if (minheap.size() > k) minheap.pop();
        }
        return minheap.top();
    }

    // Approach 2 (Acc). Bin search
    int useBinSearch(const vector<int>& nums, int k) const {
        long l = nums[0], r = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < l) l = nums[i];
            if (nums[i] > r) r = nums[i];
        }
        l--;
        r++;

        int ans;
        vector<int> curNums(nums.begin(), nums.end()); // to avoid `nums` modifications
        vector<int> less;
        vector<int> equal;
        vector<int> greater;
        k = nums.size() - k + 1; // reformulate: need to find the k'th element in sorted array
        while (r - l > 1) {
            long m = (l + r) / 2;
            for (int num : curNums) {
                if (num < m) less.push_back(num);
                else if (num == m) equal.push_back(num);
                else greater.push_back(num);
            }

            if (less.size() + equal.size() >= k && equal.size() > 0 && less.size() < k) {
                ans = equal[0];
                break;
            }

            if (less.size() < k) {
                l = m;
                k -= (less.size() + equal.size());
                curNums = greater;
            } else {
                r = m;
                curNums = less;
            }
            less.clear();
            equal.clear();
            greater.clear();
        }
        return ans;
    }

public:
    int findKthLargest(vector<int>& nums, int k) {
        return useBinSearch(nums, k);
    }
};
