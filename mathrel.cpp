#include "mathrel.h"

MathRel::MathRel()
{

}

void MathRel::test()
{
    MathRel ma;
    int i = ma.binaryGap(22);
    i = ma.studentAttandance2(3);
    i = ma.maximumSwap(2736);
    vector<vector<int>> recs = {{1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4}};
    bool r = ma.isRectangleCover(recs);
    i = 0;
}
