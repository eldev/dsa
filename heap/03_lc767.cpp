// https://leetcode.com/problems/reorganize-string/

class Solution {
private:
    struct CharCounter {
        char c;
        int count;
        CharCounter(char c, int count) : c(c), count(count) {}
        bool operator<(const CharCounter& rhs) const {
            return count < rhs.count;
        }
    };
public:
    string reorganizeString(string s) {
        unordered_map<char, int> counter;
        for (char c : s) {
            if (counter.find(c) == counter.end()) counter[c] = 0;
            counter[c]++;
        }

        priority_queue<CharCounter> maxheap;
        for (const auto& [c, count] : counter)
            maxheap.push(CharCounter(c, count));

        vector<char> ans;
        ans.reserve(s.size());
        while (!maxheap.empty()) {
            auto cc = maxheap.top();
            maxheap.pop();
            // Case 1: handle the first letter
            if (ans.empty()) {
                ans.push_back(cc.c);
                cc.count--;
                if (cc.count > 0) maxheap.push(cc);
                continue;
            }

            // Case 2: last letter does not equal to the maxheap top letter
            char lastLetter = ans[ans.size() - 1];
            if (lastLetter != cc.c) {
                ans.push_back(cc.c);
                cc.count--;
                if (cc.count > 0) maxheap.push(cc);
                continue;
            }

            // lastLetter equals to the maxheap top letter

            // Case 3: if heap is empty, it means that there is no
            // a possible rearrangement.
            if (maxheap.empty()) {
                return "";
            }

            // Case 4: consider another top element from the heap
            auto cc2 = maxheap.top();
            maxheap.pop();
            ans.push_back(cc2.c);
            cc2.count--;
            if (cc.count > 0) maxheap.push(cc);
            if (cc2.count > 0) maxheap.push(cc2);
        }

        return string(ans.begin(), ans.end());
    }
};
