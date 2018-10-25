#include "divideandconquer.h"

DivideAndConquer::DivideAndConquer()
{

}

void DivideAndConquer::test()
{
    DivideAndConquer dac;
    vector<int> nums = {7,-6,5,3,-6,4};
    dac.maxSubArray(nums);
    dac.mergesort(nums, 0, nums.size()-1);

    int i = 0;
}
