// https://leetcode.com/problems/top-k-frequent-elements/
class Solution {
public:
    // Time: O(N * logK), where N is a length of nums.
    // Space: O(K).
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, long> counter;
        for (int n : nums) {
            if (counter.count(n) == 0) counter[n] = 0;
            counter[n]++;
        }
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // min heap by the first value (by count)
        for (const auto& [num, count] : counter) {
            pq.push(make_pair(count, num));
            if (pq.size() > k) pq.pop();
        }
        vector<int> ans;
        while (!pq.empty()) {
            auto f = pq.top();
            pq.pop();
            ans.push_back(f.second);
        }
        return ans;
    }
};
