// https://leetcode.com/problems/kth-largest-element-in-a-stream/
class KthLargest {
private:
    int k;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minheap;
    void addScore(int score) {
        this->minheap.push(score);
        if (this->minheap.size() > k) this->minheap.pop();
    }
public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for (int n : nums) this->addScore(n);
    }
    
    int add(int val) {
        this->addScore(val);
        return this->minheap.top();
    }
};
