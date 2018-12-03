#include "array1.h"

array1::array1()
{

}

void array1::test()
{
    vector<int> findNums = {4,1,2};
    vector<int> nums = {1,3,4,2};
    array1 arr;
    vector<int> res  = arr.nextGreaterElement_st(findNums, nums);
    int i = 0;
    i = arr.nextGreaterElement(1999999999);
    i = 0;
}
