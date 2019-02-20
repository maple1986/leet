#include "desgin.h"

void ZigzagIterator2::test()
{
    vector<int> result;
    vector<vector<int>> vecs = {{1,2,3},{4,5,6,7},{8,9}};
    ZigzagIterator22 solution(vecs);
    //while (solution.hasNext()) result.push_back(solution.next());
    int i = 0;
    //["LFUCache","put","put","get","put","get","get","put","get","get","get"]
    //[[2],[1,1],[2,2],[1],[3,3],[2],[3],[4,4],[1],[3],[4]]
    LFUCache LFU(2);
    LFU.put(1, 1);
    LFU.put(2, 2);
    i = LFU.get(1);
    LFU.put(3, 3);
    i = LFU.get(2);
    i = LFU.get(3);
    LFU.put(4, 4);
    i = LFU.get(1);
    i = LFU.get(3);
    i = LFU.get(4);
}


