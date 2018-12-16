#include "intervalrel.h"


void IntervalRel::test()
{
    //["RangeModule","addRange","removeRange","queryRange","queryRange","queryRange"]
    //[[],[10,20],[14,16],[10,14],[13,15],[16,17]]
    RangeModule obj;
    obj.addRange(10, 20);
    obj.removeRange(14, 16);
    bool param_2 = obj.queryRange(10, 14);
    param_2 = obj.queryRange(13, 15);
    param_2 = obj.queryRange(16, 17);
}
