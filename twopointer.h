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

    string minWindow(string &S, string &T) {
        // Write your code here
        int m = S.length(), n = T.length();
        if(m < n) return "";
        int l=0, r=0, len=INT_MAX;
        string res;
        for(int r=0; r<m; ++r)
        {
            //if(isSubseq(S, l, r, T))
            //{
                while(isSubseq(S, l, r, T))
                {
                    if(r-l+1 < len)
                    {
                        len = r-l+1;
                        res = S.substr(l, len);
                    }
                    l++;
                }
            //}
        }
        return len == INT_MAX?"":res;
    }


    bool isSubseq(string& S, int l, int r, string& T)
    {
        int m = r - l + 1;
        int n = T.length();
        if(m < n) return false;
        int i=l, j=0;
        for(; i<=r && j<n; ++i)
        {
            if(S[i] == T[j])
                j++;
        }
        return j == n;
    }
};

#endif // TWOPOINTER_H
