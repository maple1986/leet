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
        bt.printVec(s1);
    }
}
