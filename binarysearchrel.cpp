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

    vector<int> v1 = {5,7,7,8,8,10};
    vector<int> v2 = {-1};
    bs.searchRange(v1, 8);
    vector<int> nums = {0,1,1,1,2,3,6,7,8,9};

    vector<int> res = bs.findClosestElements(nums, 9, 4);
    vector<vector<int>> mat = {{1,3,5,7},{10,11,16,20},{23,30,34,50}};
    bool bres1 = bs.searchMatrix(mat, 10);
    int i = 0;
}
