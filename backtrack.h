#ifndef BACKTRACK_H
#define BACKTRACK_H
#include <vector>
#include <string>
#include <string.h>
#include <hashtable.h>
#include <set>

using namespace std;
class backtrack
{
public:
    backtrack();
    /*
    char mapping[9][5] =
    {
        "ABC",
        "DEF",
        "GHI",
        "JKL",
        "MNO",
        "PQRS",
        "TUV",
        "WXYZ",
    };
    */
    vector<string> mapping1 =
    {
        "ABC",
        "DEF",
        "GHI",
        "JKL",
        "MNO",
        "PQRS",
        "TUV",
        "WXYZ",
    };


    vector<string> letterCombinations(string digits) {
        vector<string> ret;
        for(int i=0; i<digits.size(); ++i)
        {
            int index = digits[i]-'1';
            if(ret.empty())
            {
                for(int j=0; j< mapping1[index].size();++j)
                {
                    string tmp;
                    tmp += mapping1[index][j];
                    ret.push_back(tmp);
                }
            }
            else
            {
                vector<string> tmp;
                for(int j=0; j<ret.size(); ++j)
                {
                    for(int k=0; k<mapping1[index].size(); ++k)
                    {
                        string tmp1 = ret[j];
                        tmp1 += mapping1[index][k];
                        tmp.push_back(tmp1);
                    }
                }
                ret.swap(tmp);
            }
        }
        return ret;
    }

    vector<string> letterCasePermutation(string S) {
        vector<string> ret;
        if(S.empty())
        {
            return ret;
        }
        ret.push_back(S);
        for(int i=0; i<S.size(); ++i)
        {

        }
        return ret;
    }

    int singleNumber(vector<int>& nums)
    {
        multiset<int> mset;
        for(int i=0; i< nums.size(); ++i)
        {
            mset.insert(nums[i]);
        }
        auto it = mset.begin();
        while(it != mset.end())
        {
            if(mset.count(*it) == 1)
            {
                return *it;
            }
            ++it;
        }
        return -1;
    }
    string addBinary(string a, string b) {
        string result;
        bool carry = false;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        if(a.size() > b.size())
        {
            swap(a, b);
        }
        auto c1 = b.begin();
        for(auto& c:a)
        {
           int cur=0;
           if(carry) cur++;
           if(c-'0') cur++;
           if(*c1-'0') cur++;
           switch (cur) {
           case 0:
               carry = false;
               result += '0';
               break;
           case 1:
               carry = false;
               result += '1';
               break;
           case 2:
               carry = true;
               result += '0';
               break;
           case 3:
               carry = true;
               result += '1';
               break;
           default:
               break;
           }
           c1++;
        }
        if(!carry)
        {
            result.append(c1, b.end());
        }
        else
        {
            while(c1!=b.end())
            {
                if(*c1 == '1')
                {
                    result += '0';
                }
                else
                {
                    result += '1';
                    result.append(++c1, b.end());
                    carry = false;
                    break;
                }
                c1++;
            }
        }
        if(carry)
        {
            result += '1';
        }
        reverse(result.begin(), result.end());
        return result;
    }
    string addBinary1(string a, string b)
    {
        if(a.size() > b.size()) swap(a, b);
        int m = a.size();
        int n = b.size();
        for(int i=m-1; i>=0; --i)
        {
            b[n-m+i] += a[i]-'0';
        }
        int carry = 0;
        for(int i=n-1; i>=0; --i)
        {
            if(carry) b[i]++;
            if(b[i] > '1')
            {
                b[i] -= 2;
                carry =1;
            }
            else
            {
                carry = 0;
            }
        }
        if(carry)b.insert(b.begin(), '1');
        return b;
    }
};

#endif // BACKTRACK_H
