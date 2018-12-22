#include "hashrel.h"
#include <iostream>

hashRel::hashRel()
{

}

void hashRel::test()
{
    hashRel h;
    string s = h.frequencySort("abcdefgg");
    cout << s.c_str() << endl;
    vector<int> nums = {4,0,-4,-2,2,5,2,0,-8,-8,-8,-8,-1,7,4,5,5,-4,6,6,-3};
    int i = h.longestConsecutive(nums);
}
