// https://leetcode.com/problems/combination-sum/

class Solution {
private:
    void helper(vector<vector<int>>& ans, const vector<int>& candidates, int target, vector<int>& cur, int curSum, int lastIdx) const {
        if (curSum == target) {
            ans.push_back(cur);
            return;
        }
        if (curSum > target) return; // the candidates are only positive numbers

        // Start iterating from lastIdx in order to avoid duplicate combinations.
        for (int i = lastIdx; i < candidates.size(); i++) {
            cur.push_back(candidates[i]);
            helper(ans, candidates, target, cur, curSum + candidates[i], i);
            cur.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> cur;
        helper(ans, candidates, target, cur, 0, 0);
        return ans;
    }
};
