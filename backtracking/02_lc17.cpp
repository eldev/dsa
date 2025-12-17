// https://leetcode.com/problems/letter-combinations-of-a-phone-number

class Solution {
private:
    map<char, vector<char>> digitToLetters = {
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}},
    };

    void helper(vector<string>& combinations, vector<char>& cur, const string& digits, int fromIdx) const {
        if (cur.size() == digits.size()) {
            combinations.push_back(string(cur.begin(), cur.end()));
            return;
        }
        const vector<char>& letters = digitToLetters.at(digits[fromIdx]);
        for (char c : letters) {
            cur.push_back(c);
            helper(combinations, cur, digits, fromIdx + 1);
            cur.pop_back();
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        vector<string> combinations;
        vector<char> cur;
        helper(combinations, cur, digits, 0);
        return combinations;
    }
};
