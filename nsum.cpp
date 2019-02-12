#include "nsum.h"

NSum::NSum()
{

}

void NSum::test()
{
    NSum ns;
    vector<int> v = {1, 2, 3, 4, -1, -2, -3, -5, -6};
    ns.twoSum(v, -5);
    ns.threeSum(v);
    //ns.fourSum(v, 0);
    vector<int> v3 = {-2,-3,-4,-5,-100,99,1,4,4,4,5,1,0,-1,2,3,4,5};
    ns.threeSum3(v3);
    vector<int> v1 = {1,1,2,2,3,3,4,4,5,5};
    int i = ns.threeSumMulti2(v1, 8);
    vector<int> v2 = {-4,-7,-2,2,5,-2,1,9,3,9,4,9,-9,-3,7,4,1,0,8,5,-7,-7};
    i = ns.threeSumClosest(v2, 29);
    i = 0;
}
