#include "backtrack.h"
#include <iostream>

using namespace std;
backtrack::backtrack()
{

}

void backtrack::test()
{
    backtrack bt;
    //cout << bt.addBinary1("11", "1") << endl;
    bt.permute({1, 2, 3});
    bt.letterCasePermutation2("C");
    bt.subsets3({1, 2, 3});
    vector<string> res = bt.readBinaryWatch(2);
//    for(const auto& s : res)
//    {
//        printf("%s\n", s.c_str());
//    }
    vector<int> v1 = {1,1,2};
    vector<vector<int>> res1 = bt.permuteUnique(v1);
    for(auto s1 : res1)
    {
        //bt.printVec(s1);
    }

    res1.clear();
    res1 = bt.combinationSum3(3, 7);
    for(auto s1 : res1)
    {
        //bt.printVec(s1);
    }

    res1.clear();
    vector<int> v2 = {2,3,6,7};
    res1 = bt.combinationSum(v2, 7);
    res1.clear();

    v2 = bt.grayCode(2);
    bt.printVec(v2);

    bt.findStrobogrammatic(2);

    int i = bt.countNumbersWithUniqueDigits(3);
    vector<int> nums1 = {1, 2, 3};
    res1  = bt.subsets5(nums1);
    string word = "word";
    res = bt.generateAbbreviations(word);
    res = bt.generateParenthesis(3);
    //bt.nextPermutation(nums1);
    string s = "abcd";
    vector<vector<string>> res2 = bt.partition(s);

    i=0;
}
