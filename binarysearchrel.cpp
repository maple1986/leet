#include "binarysearchrel.h"

binarySearchRel::binarySearchRel()
{

}

void binarySearchRel::test()
{
    binarySearchRel bs;
    vector<vector<int>> matrix;
    vector<int> line1 = {0, 1, 2, 3, 4, 5};
    vector<int> line2 = {10, 11, 12, 13, 14, 15};
    matrix.push_back(line1);
    matrix.push_back(line2);
    bs.kthSmallest(matrix, 7);
}
