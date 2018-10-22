#ifndef GREEDY_H
#define GREEDY_H

#include <vector>

using namespace std;
class greedy
{
public:
    greedy();
    static void test();
    int rob(vector<int>& nums)
    {
        int size = nums.size();
        if(size != 0)
            return maxRob(size, nums);
    }

    int maxRob(int n, vector<int>& nums)
    {
        if(n<0)
        {
            return 0;
        }
        int res = max(maxRob(n-2, nums)+ nums[n], maxRob(n-1, nums));
        return res;
    }
};

#endif // GREEDY_H
