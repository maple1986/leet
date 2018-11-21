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


}
