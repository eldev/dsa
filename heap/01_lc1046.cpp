// https://leetcode.com/problems/last-stone-weight
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq; // max heap
        for (int s : stones) pq.push(s);
        while (pq.size() > 1) {
            int x = pq.top();
            pq.pop();
            int y = pq.top();
            pq.pop();
            int newStone = x - y;
            if (newStone == 0) continue;
            if (newStone < 0) newStone *= -1;
            pq.push(newStone);
        }
        return pq.size() > 0 ? pq.top() : 0;
    }
};
