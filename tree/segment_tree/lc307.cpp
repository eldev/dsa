// https://leetcode.com/problems/range-sum-query-mutable/description/
class SegmentTree {
private:
    int n;
    vector<int> t;
    
    void build(vector<int>& nums, int x, int xl, int xr) {
        if (xr - xl == 1) {
            t[x] = nums[xl];
        } else {
            int m = (xl + xr) / 2;
            build(nums, 2 * x + 1, xl, m); // left subtree
            build(nums, 2 * x + 2, m, xr); // right subtree
            t[x] = t[2*x+1] + t[2*x+2];
        }
    }

public:
    SegmentTree(vector<int>& nums) {
        this->n = nums.size();
        this->t = vector<int>(4 * n);
        build(nums, 0, 0, n);
    }

    void update(int idx, int val, int x=0, int xl=0, int xr=-1) {
        if (xr == -1) xr = n;
        if (xr - xl == 1) {
            t[x] = val;
        } else {
            int m = (xl + xr) / 2;
            if (idx < m) update(idx, val, 2*x+1, xl, m); // update left subtree
            else update(idx, val, 2*x+2, m, xr); // update right subtree
            t[x] = t[2*x+1] + t[2*x+2];
        }
    }

    // [l, r)
    int sum(int l, int r, int x=0, int xl=0, int xr=-1) {
        if (xr == -1) xr = n;
        if (l <= xl && xr <= r) return t[x];
        if (r <= xl || xr <= l) return 0;
        int m = (xl + xr) / 2;
        int ls = sum(l, r, 2*x+1, xl, m);
        int rs = sum(l, r, 2*x+2, m, xr);
        return ls + rs;
    }
};

class NumArray {
private:
    SegmentTree* t;
public:
    NumArray(vector<int>& nums) {
        t = new SegmentTree(nums);
    }
    
    void update(int index, int val) {
        this->t->update(index, val);
    }
    
    int sumRange(int left, int right) {
        // need a sum in [left, right] (right inclusively),
        // so should set right + 1.
        return this->t->sum(left, right + 1);
    }
};
