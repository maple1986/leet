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
    vector<string> emails = {"zh.ang+fs@123.com", "zliu.ang+fs@123.com"};
    str.countGroups1(emails);

    vector<int> num3 ={4,3,2,7,8,2,3,1};
    //str.findDisappearedNumbers(num3);
    string A = "abcd", B ="cdabcdab";
    int i = str.repeatedStringMatch(A, B);
    string a="abc";
    string b="c";
    bool b1= str.canGetString(a,b);
    i = str.Sunday("substringsearching", "search");
    str.wordsCompression2({A, B});
    string C = "jcwsijl", D = "sijljcwsijljcwsijljcwsijljcwsijljcwsijljcwsijljcwsijljcwsijljcwsijljc";
    i = str.repeatedString(C, D);
    string a1="abcde<<";
    string a2="abcd<e<";
    string res = str.inputStream(a1, a2);
    i = 0;
}
