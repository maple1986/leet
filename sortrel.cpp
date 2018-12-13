#include "sortrel.h"

sortrel::sortrel()
{

}

void sortrel::test()
{
    Interval it1(9, 100);
    Interval it2(5, 105);
    Interval it3(0, 100);
    vector<Interval> v;
    v.push_back(it1);
    v.push_back(it2);
    v.push_back(it3);
    sortrel sortl;
    sortl.merge(v);
    vector<int> v1 = {282475249,622650073,984943658,144108930,470211272,101027544,457850878,458777923};
    vector<int> v2 = {823564440,115438165,784484492,74243042,114807987,137522503,441282327,16531729,823378840,143542612};
    vector<int> v3 = {1,5};
    vector<int> v4 = {10};

    sortl.findRadius(v3, v4);
    vector<int> v5 = {1,1,1,2};
    sortl.subarraySum(v5, 2);

    vector<int> nums1 = {1,7,11};
    vector<int> nums2 = {2,4,6};
    sortl.kSmallestPairs1(nums1, nums2, 3);
    vector<int> nums3 = { 61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 62 };
    sortl.bubbleSort(nums3);

    vector<int> num4 = {2,4,3,5,1};
    sortl.reversePairs(num4);
    int i = 0;
}
