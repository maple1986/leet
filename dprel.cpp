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
}
