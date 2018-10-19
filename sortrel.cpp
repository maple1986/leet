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
}
