// https://leetcode.com/problems/generate-parentheses/

class Solution {
private:
    // curSum is a current sum of parentheses: +1 for '(' and -1 for ')'.
    void helper(vector<string>& ans, vector<char>& p, int n, int idx, int curSum) const {
        if (idx == 2*n) {
            if (curSum == 0) {
                ans.push_back(string(p.begin(), p.end()));
            }
            return;
        }
        if (curSum < 0) return; // example: curSum==-1 for p={'(', ')', ')'}

        if (curSum > 2*n - idx) return; // mini-optimization

        // '('
        p.push_back('(');
        helper(ans, p, n, idx + 1, curSum + 1);
        p.pop_back();

        // ')'
        p.push_back(')');
        helper(ans, p, n, idx + 1, curSum - 1);
        p.pop_back();
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        vector<char> p;
        p.reserve(2*n);
        helper(ans, p, n, 0, 0);
        return ans;
    }
};
