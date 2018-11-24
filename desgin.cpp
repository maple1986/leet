#include "desgin.h"

void ZigzagIterator2::test()
{
    vector<int> result;
    vector<vector<int>> vecs = {{1,2,3},{4,5,6,7},{8,9}};
    ZigzagIterator22 solution(vecs);
    while (solution.hasNext()) result.push_back(solution.next());
    int i = 0;
}


