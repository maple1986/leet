#ifndef TWOPOINTER_H
#define TWOPOINTER_H
#include <vector>
#include <set>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;
class TwoPointer
{
public:
    TwoPointer();
    static void test();
    int lengthOfLIS(vector<int>& nums)
    {
        if(nums.empty()) return 0;
        int max_length = 1;
        int low = 0, high = 0;
        while(high < nums.size()-1)
        {
            if(nums[high] < nums[++high])
            {
                max_length = max(max_length, high-low+1);
            }
            else
            {
                low = high;
            }
        }
        return max_length;
    }

    int lengthOfLongestSubstringKDistinct(string &s, int k) {
        if(0 == k) return 0;
        unordered_map<char, int> dict;

        int maxlen = 0, start = 0;
        for(int i=0; i<s.length(); ++i)
        {
            char index = s[i];
            dict[index]++;
            if(k < dict.size())
            {
                while(--dict[s[start++]] != 0);
                dict.erase(s[start-1]);
            }
            maxlen = max(maxlen, i - start + 1);
        }
        return maxlen;
    }
};

#endif // TWOPOINTER_H
