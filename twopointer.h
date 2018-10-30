#ifndef TWOPOINTER_H
#define TWOPOINTER_H
#include <vector>
using namespace std;
class TwoPointer
{
public:
    TwoPointer();
    static void test();
    int lengthOfLIS(vector<int>& nums)
    {
        if(nums.empty()) return 0;
        int max_length = 1;
        int low = 0, high = 0;
        while(high < nums.size()-1)
        {
            if(nums[high] < nums[++high])
            {
                max_length = max(max_length, high-low+1);
            }
            else
            {
                low = high;
            }
        }
        return max_length;
    }
};

#endif // TWOPOINTER_H
