#include "twopointer.h"

TwoPointer::TwoPointer()
{

}

void TwoPointer::test()
{
    TwoPointer tp;
    vector<int> nums = {10,9,2,5,3,7,101,18};
    tp.lengthOfLIS(nums);
    string str = "eqgkcwGFvjjmxutystqdfhuMblWbylgjxsxgnoh";
    int i = tp.lengthOfLongestSubstringKDistinct(str, 16);
    string S = "cnhczmccqouqadqtmjjzl";
    string T = "mm";
    string res = tp.minWindow(S, T);
    i = 0;
}
