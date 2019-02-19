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
    vector<int> nums1= {1, 3, 2};
    arr.nextPermutation1(nums1);
    vector<int> nums2= {1,5,1,1,6,4};
    arr.wiggleSort2(nums2);
    vector<int> v = {0,1,2,4,5,7};
    arr.summaryRanges(v);
}
