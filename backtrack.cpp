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
}
