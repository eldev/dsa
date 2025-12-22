// https://leetcode.com/problems/combination-sum-iii

class Solution {
private:
    void helper(vector<vector<int>>& ans, vector<int>& curNumbers, int curSum, int lastNum, int k, int target) const {
        if (curSum == target && curNumbers.size() == k) {
            ans.push_back(curNumbers);
        }
        if (curSum >= target) return; // the numbers are only positive

        // Each number is used at most once,
        // so need to start from lastNum + 1.
        for (int i = lastNum + 1; i <= 9; i++) {
            curNumbers.push_back(i);
            helper(ans, curNumbers, curSum + i, i, k, target);
            curNumbers.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        vector<int> curNumbers;
        helper(ans, curNumbers, 0, 0, k, n);
        return ans;
    }
};
