#include "dprel.h"

DPRel::DPRel()
{

}

void DPRel::test()
{
    DPRel dprel;
    vector<int> nums = {7,1,5,3,6,4};
    dprel.deleteAndEarn(nums);
    dprel.maxProfit(nums);

    vector<int> nums2 = {1,2,3,0,2};
    dprel.maxProfit_cooldown(nums2);
    //dprel.longestPalindromeSubseq("bbbab");
    dprel.minFlipsMonoIncr2("00110");
}
