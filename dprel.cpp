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

    vector<int> num3 = {0,1,1,0};
    dprel.minCostClimbingStairs(num3);

    printf("num of ways = [%d]\n", dprel.numWays(3, 1) == dprel.numWays1(3, 1));

    vector<int> num4 = {1, 2, 3, 8, 9, 10};
    dprel.numberOfArithmeticSlices(num4);
}
