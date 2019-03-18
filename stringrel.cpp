#include "stringrel.h"

void StringRel::test()
{
    string num1("99");
    string num2("9");
    StringRel str;
    vector<string> words = {"aba","ababababca","acb","cb"};
    str.wordsCompression(words);
    string p = "ABABABA";
    string p2 ="ABCDABD";
    vector<int> next(p2.size(), 0);
    str.calcNext(p2, next);
    string S = "heeellooo";
    words = {"hello", "hi", "helo"};
    int i = str.expressiveWords(S, words);
    //i = str.Sunday("substringsearching", "search");
    //i = str.KMP("cdeabab", "abab");
    S = "3[a]2[bc]";
    string res1 = str.decodeString(S);
    S = "Mg(OH)2";
    res1 = str.countOfAtoms2(S);
    /*
    string s1 = "abc";//"abababababababa";
    string word = "cde";//"cvb";
    string ans = str.getAns(s1, word);
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
    */
    string A = "abcd", B ="cdabcdab";
    i = str.repeatedStringMatch(A, B);
    string a="abc";
    string b="c";
    bool b1= str.canGetString(a,b);

    str.wordsCompression2({A, B});
    string C = "jcwsijl", D = "sijljcwsijljcwsijljcwsijljcwsijljcwsijljcwsijljcwsijljcwsijljcwsijljc";
    i = str.repeatedString(C, D);
    string a1="abcde<<";
    string a2="abcd<e<";
    //string res = str.inputStream(a1, a2);
    a1 = "abcd";
    vector<int> indexes = {0, 2};
    vector<string> source = {"a", "cd"};
    vector<string> dest = {"eee", "ffff"};

    string res = str.findReplaceString(a1, indexes, source, dest);
    i = 0;
}
