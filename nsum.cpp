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
    ns.fourSum(v, 0);
}
