#include "stringrel.h"

void StringRel::test()
{
    string num1("99");
    string num2("9");
    StringRel str;
    //str.multiply(num1, num2);
    //str.validWordAbbreviation("internationalization", "i12iz4n");
    //printf("res=[%d]\n",str.canPermutePalindrome("abcc"));
    //printf("res=[%s]\n",str.shortestPalindrome("aaabbbb").c_str());
    //printf("contest = [%s]", str.findContestMatch(8).c_str());
    string time = "21:19";
    //str.nextClosestTime(time);
    //printf("time = %s\n", time.c_str());
    //printf("res=[%s]\n",str.shortestPalindrome("aaabbbb").c_str());
    vector<int> num = {0,1,2,4,5,7};
    //str.summaryRanges(num);
    vector<string> dict = {"deer", "cart", "cane", "make"};
    str.ValidWordAbbr(dict);
    str.findStrobogrammatic(2);
}
