#ifndef BITREE_H
#define BITREE_H

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
class BITree
{
public:
    static void test();
};

class BITreeSolution
{
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> ret, clone = nums;
        int len = (int) nums.size();
        unordered_map<int, int> reflect;
        array.resize(len + 1);
        sort(clone.begin(), clone.end());
        for (int i = 0; i < len; ++ i)
            reflect[clone[i]] = i + 1;

        for (int i = len - 1; i >= 0; -- i) {
            clone[i] = query(reflect[nums[i]] - 1);
            add(reflect[nums[i]], 1);
        }
        return clone;
    }

private:
    vector<int> array;
    inline int lowbit(int pos) {
        return pos & -pos;
    }
    void add(int pos, int val) {
        long len = array.size();
        while (pos < len) {
            array[pos] += val;
            pos += lowbit(pos);
        }
    }
    int query(int pos) {
        int ret = 0;
        while (pos > 0) {
            ret += array[pos];
            pos -= lowbit(pos);
        }
        return ret;
    }
};

class FenwickTree
{
public:
    FenwickTree(int n):sums_(n+1, 0)
    {
    }

    void update(int x, int delta)
    {
        int n = sums_.size();
        while(x<n)
        {
            sums_[x] += delta;
            x += lowbit(x);
        }
        return;
    }

    int query(int x)
    {
        int sum = 0;
        while(x>0)
        {
            sum += sums_[x];
            x -= lowbit(x);
        }
        return sum;
    }

private:
    static inline int lowbit(int x) {return x&(-x);}
    vector<int> sums_;

};

class NumArray {
public:
    NumArray(vector<int> nums):nums_(std::move(nums)), tree_(nums.size()) {
        nums_ = nums;
        for(int i=0; i<nums.size(); ++i)
        {
            tree_.update(i+1, nums_[i]);
        }
    }

    void update(int i, int val) {
        tree_.update(i+1, val-nums_[i]);
        nums_[i] = val;
    }

    int sumRange(int i, int j) {
        return tree_.query(j+1)-tree_.query(i);
    }

    FenwickTree tree_;
    vector<int> nums_;
};

#endif // BITREE_H
