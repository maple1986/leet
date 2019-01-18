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
    vector<vector<int>> matrix1 = {{1,5,9},{10,11,13},{12,13,15}};
    bs.kthSmallest3(matrix1, 8);

    vector<int> v1 = {5,7,7,8,8,10};
    vector<int> v2 = {-1};
    bs.searchRange(v1, 8);
    vector<int> nums = {0,1,1,1,2,3,6,7,8,9};

    vector<int> res = bs.findClosestElements3(nums, 3, 4);
    vector<vector<int>> mat = {{1,3,5,7},{10,11,16,20},{23,30,34,50}};
    bool bres1 = bs.searchMatrix(mat, 10);
    vector<int> salaries = {2,4,6,8,10,12,14,15};
    int cap = bs.getCap(salaries, 72);
    bres1 = bs.isPerfectSquare(808201);
    vector<int> v3 = {1, 2, 4, 5, 6, 9};
    vector<int> v4 = {0, 1, 1, 1, 1};
    cap = bs.findLowerBound(v4, 1);
    vector<int> v5 = {2, 2, 3, 4};
    cap = bs.triangleNumber(v5);
    vector<int> v6 = {1, 2, 3, 4, 5};
    salaries = bs.findClosestElements2(v6, 4, 4);
    vector<int> v7 = {1,3,1};
    cap = bs.smallestDistancePair(v7, 1);
    vector<int> v8 = {1,2,3,3,4,5};
    bres1 = bs.isPossible(v8);
    int i = 0;
}
