// https://leetcode.com/problems/permutations

class Solution {
private:
    void helper(vector<vector<int>>& permutations, vector<int>& curPrmtn, const vector<int>& nums) const {
        if (curPrmtn.size() == nums.size()) {
            permutations.push_back(curPrmtn);
            return;
        }

        for (int v : nums) {
            // all integers are unique by constraints, so it's enough to check
            // if curPrmtn does not contain the current value.
            if (find(curPrmtn.begin(), curPrmtn.end(), v) == curPrmtn.end()) {
                curPrmtn.push_back(v);
                helper(permutations, curPrmtn, nums);
                curPrmtn.pop_back();
            }
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> curPrmtn;
        helper(ans, curPrmtn, nums);
        return ans;
    }
};
