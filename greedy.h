#ifndef GREEDY_H
#define GREEDY_H

#include <vector>
#include <map>
using namespace std;
class greedy
{
public:
    greedy();
    static void test();
    int rob(vector<int>& nums)
    {
        int size = nums.size();
        if(size != 0)
            return maxRob(size-1, nums);
        return 0;
    }

    int maxRob(int n, vector<int>& nums)
    {
        if(n<0)
        {
            return 0;
        }
        map<int, int>::iterator it = _values.find(n);
        if(it != _values.end())
        {
            return it->second;
        }
        int res = max(maxRob(n-2, nums)+ nums[n], maxRob(n-1, nums));
        _values.insert(make_pair(n, res));
        return res;
    }

    int monotoneIncreasingDigits(int N)
    {
        //if(N == 0) return 0;
        if(N <= 10) return N-1;
        string strN = to_string(N);
        string res;
        for(int i=0; i<strN.length(); ++i)
        {
            char last = res.empty()?'1':res.back();
            for(char c = last; c <= '9'; ++c)
            {
                if(res + repeat(c, strN.length()-1) > strN)
                {

                }
            }
        }
        return stoi(res);
    }

    string repeat(char c, int n)
    {
        string res;
        while(n--)
        {
            res += c;
        }
        return res;
    }

    string removeKdigits(string num, int k) {
        if(num.length() == k) return "0";
        if(k == 0) return num;
    }

    /*
     * for ( int i = 1; i < k; i++)
    reservoir[i] = stream[i];
for (i = k; stream != null; i++) {
    p = random(0, i);
    if (p < k) reservoir[p] = stream[i];
return reservoir;
    */
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return true;
        vector<bool> res(n, false);
        res[0] = true;
        for(int i=0; i<n; ++i)
        {
            if(!res[i]) continue;
            int sIdx = i, eIdx = min(n-1, i+nums[i]);
            for(int j=sIdx; j<=eIdx; ++j)
            {
                res[j] = true;
            }
        }
        return res[n-1];
    }

    bool canJumpGreedy(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return true;
        int reach = 0;
        for(int i=0; i<n; ++i)
        {
            if(i > reach || reach >= n-1) break;
            reach = max(reach, i+nums[i]);
        }
        return reach >= n-1;
    }

    int canJump2(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        vector<int> dp(n, 0); 
        for(int i=0; i<n; ++i)
        {
            
        }
        //return reach >= n-1?step:-1;
    }
private:
    std::map<int, int> _values;


};

#endif // GREEDY_H
