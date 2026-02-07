// https://leetcode.com/problems/matchsticks-to-square
// Also see comment: https://leetcode.com/problems/matchsticks-to-square/editorial/comments/975731/
// TODO: see editorial to solve using DP for O(N * 2^N)

class Solution {
private:
    // Time: O(4^N), Space: O(N) (N recursive calls)
    bool solution1(vector<int>& matchsticks) {
        long long perimeter = 0;
        for (long long v : matchsticks) perimeter += v;
        if (perimeter % 4 != 0) return false;

        bool ans = false;
        // Optimization: sort in descending order
        // to consider large values first and return false
        // if it is impossible to get a solution.
        sort(matchsticks.begin(), matchsticks.end(), std::greater<int>());
        vector<long long> sums(4, 0);
        helper(matchsticks, ans, 0, perimeter / 4, sums);
        return ans;
    }

    void helper(const vector<int>& matchsticks, bool& ans, size_t idx, const long long sideSize, vector<long long>& sums) const {
        if (ans) return;
        if (idx >= matchsticks.size()) {
            bool equal = true;
            long long val = sums[0];
            for (int i = 1; i < 4; i++) {
                if (val != sums[i]) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                ans = true;
            }
            return;
        }

        int val = matchsticks[idx];
        // try to add the val to each group if possible
        for (int i = 0; i < 4; i++) {
            if (sums[i] + val > sideSize) continue;
            sums[i] += val;
            helper(matchsticks, ans, idx + 1, sideSize, sums);
            if (ans) return;
            sums[i] -= val;
        }
    }
public:
    bool makesquare(vector<int>& matchsticks) {
        return solution1(matchsticks);
    }
};
