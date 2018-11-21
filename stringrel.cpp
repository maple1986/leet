#include "stringrel.h"

void StringRel::test()
{
    string num1("99");
    string num2("9");
    StringRel str;
    str.multiply(num1, num2);
    printf("res=[%d]\n",str.canPermutePalindrome("abcc"));
    printf("res=[%s]\n",str.shortestPalindrome("aaabbbb").c_str());
    printf("contest = [%s]", str.findContestMatch(8).c_str());
}
