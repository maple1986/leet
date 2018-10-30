#ifndef DPREL_H
#define DPREL_H

#include <vector>
#include <set>
#include <algorithm>

using namespace std;
class DPRel
{
public:
    DPRel();
    void static test();
    int rob_dp(vector<int>& nums)
    {
        int n=nums.size();
        if(n==0)
        {
            return 0;
        }
        else
        {
            int dp[n];
            dp[0]=nums[0];
            for(int i=1;i<n;i++)
            {
                if(i==1)
                    dp[i]=max(dp[0],nums[1]);
                else
                    dp[i]=max(dp[i-2]+nums[i],dp[i-1]);
            }
            return dp[n-1];
        }
    }

    int deleteAndEarn(vector<int>& nums)
    {
        //multiset<int> mset(nums.begin(), nums.end());
        //multiset<int>::iterator it = mset.begin();
        if(nums.empty()) return 0;
        int max_n = *max_element(nums.begin(), nums.end());
        //int min_n = std::min_element(nums.begin(), nums.end());
        vector<int> dp(max_n+1, 0);
        for(int i = 0; i < nums.size(); ++i)
        {
            dp[nums[i]] += nums[i];
        }
        dp_deleteAndEarn(dp);

        return dp[max_n];
    }

    int dp_deleteAndEarn(vector<int>& dp)
    {
        int n = dp.size();
        for(int i=2; i<n; ++i)
        {
            dp[i] = max(dp[i-2]+dp[i], dp[i-1]);
        }
        return 0;
    }

    int deleteAndEarn2(vector<int>& nums)
    {

    }

    int maxProfit(vector<int>& prices)
    {
        if(prices.empty()) return 0;
//        int num = prices.size();
//        auto max_it = max_element(prices.begin(), prices.end());
//        auto min_it = max_element(prices.begin(), prices.end());
//        if(max_it - min_it > 0)
//        {
//            return *max_it - *min_it;
//        }
        vector<int> dp(prices.size(), 0);
        for(int i=1; i<prices.size(); ++i)
        {
            int delta = prices[i] - prices[i-1] + dp[i-1];
            dp[i] = delta>0?delta:0;
        }
        int res = *max_element(dp.begin(), dp.end());
        return res>0?res:0;
    }
    int maxProfit2(vector<int>& prices) {
        if(prices.size() == 0) return 0;
        int result = 0;
        int cur_min = prices[0];
        for(int i = 1; i < prices.size(); i++){
            if(cur_min >= prices[i]) {
                cur_min = prices[i];
                continue;
            }
            result = prices[i] - cur_min > result ? prices[i] - cur_min : result;
        }
        return result;
    }

    int maxSubArray(vector<int>& nums)
    {
        if(nums.empty()) return 0;
        int cur = 0;
        int res = 0;
        for(int i=0; i<nums.size(); ++i)
        {
            if(nums[i] > 0)
            {
                cur += nums[i];
            }
            else
            {
                if(cur + nums[i]>0)
                {
                    cur += nums[i];
                }
                else
                {
                    cur = 0;
                }
            }
            res = max(cur, res);
        }
        return res>0?res:*max_element(nums.begin(), nums.end());
    }

    int maxProfit_cooldown(vector<int>& prices)
    {
        if(prices.empty()) return 0;
        vector<int> dp(prices.size(), 0);
        int i=1;
        for(; i<prices.size(); ++i)
        {
            if(i == 1)
                dp[i] = prices[i] - prices[i-1];
            else
                dp[i] = max(dp[i-2]+ prices[i]-prices[i-1], dp[i-1]);
        }
        return dp[i-1]>0?dp[i-1]:0;
    }

    int longestPalindromeSubseq(string s)
    {
        int n = s.size();
        if(n <= 1) return n;
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int l = 1; l <= n; ++l)
        {
            for(int i=0; i<=n-l; ++i)
            {
                int j = l + i - 1;
                if(i == j)
                {
                    dp[i][j] = 1;
                    continue;
                }
                if(s[i] == s[j])
                {
                    dp[i][j] = dp[i+1][j-1] + 2;
                }
                else
                {
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            }
        }
        return dp[0][n-1];
    }

    int minFlipsMonoIncr(string S)
    {
        int n = S.size();
        if(n<2) return 0;
        int min_flip = 20001;
        for(int i=-1; i<n; ++i)
        {
            int flip = 0;
             for(int j=0; j<=i; ++j)
            {
                if(S[j] != '0')
                {
                    flip++;
                }
            }
            for(int k=i+1; k<n; ++k)
            {
                if(S[k] != '1')
                {
                    flip++;
                }
            }
            min_flip = min(min_flip, flip);
        }
        return min_flip;
    }

    int minFlipsMonoIncr2(string S)
    {
        int n = S.size();
        if(n<2) return 0;
        int min_flip = 20001;
        vector<int> l(n, 0);
        vector<int> r(n, 0);
        l[0] = S[0] - '0';
        r[n-1] = '1' - S[n-1];
        for(int i=1; i<n; ++i)
        {
            l[i] = l[i-1] + S[i] - '0';
        }

        for(int i=n-2; i>=0; --i)
        {
            r[i] = r[i+1] + 1 - S[i];
        }

        for(int i=0; i<n; ++i)
        {
            min_flip = min(min_flip, l[i]+r[i+1]);
        }
        //min_flip = min(min_flip, l[n-1]);
        //min_flip = min(min_flip, r[0]);
        return min_flip;
    }

    int climbstairs(int n)
    {
        if(n<=2) return n;
        vector<int> dp(n+1, 0);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        for(int i= 3; i<n+1; ++i)
        {
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }

    int climbstairs2(int n)
    {
        if(n<=2) return n;
        //vector<int> dp(n+1, 0);
        //int dp0 = 0;
        int dp0 = 1;
        int dp1 = 2;
        for(int i= 3; i<n+1; ++i)
        {
            //dp[i] = dp[i-1] + dp[i-2];
            int dp2 = dp0 + dp1;
            dp0 = dp1;
            dp1 = dp2;
        }
        return dp1;
    }

    int climbstairs3(int n)
    {
        if(n <= 2)
        {
            return n;
        }
        return climbstairs3(n-1) + climbstairs3(n-2);
    }


    int minCostClimbingStairs(vector<int>& cost)
    {
        int n = cost.size();
//        if(n == 0) return 0;
        if(n == 1) return cost[0];
//        if(n == 2) return cost[0];
        vector<int> min_Cost(n+1, 0);
        for(int i=2; i<=n; ++i)
        {
            min_Cost[i] = min((cost[i-1]+min_Cost[i-1]), (cost[i-2]+min_Cost[i-2]));
        }
        return min_Cost[n];
        //return min(min_Cost[n-1], min_Cost[n-2]);
    }

    void NumArray(vector<int> nums)
    {
        _sums.assign(nums.size()+1, 0);
        for(int i=0; i<nums.size(); ++i)
        {
            _sums[i+1] = _sums[i] + nums[i];
        }
    }

    int sumRange(int i, int j)
    {
        return _sums[j+1] - _sums[i];
    }


    int numWays(int n, int k)
    {
        if (n == 0) return 0;
        int same = 0, diff = k;
        for (int i = 2; i <= n; ++i) {
            int t = diff;
            diff = (same + diff) * (k - 1);
            same = t;
        }
        return same + diff;
    }

    int numWays1(int n, int k)
    {
        if (n == 0) return 0;
        if (n == 1) return k;
        vector<int> dp(n+1, 0);
        dp[1] = k;
        dp[2] = k*k;
        for (int i = 3; i <= n; ++i)
        {
            dp[i] = (dp[i-1] + dp[i-2])*(k-1);
        }
        return dp[n];
    }

    bool stoneGame(vector<int>& piles)
    {
        if(piles.size() == 2) return true;
        vector<int> dp(piles.size()/2, 0);
        return true;
        //for(int)
    }


    int numberOfArithmeticSlices(vector<int>& A)
    {
        if(A.size() < 3) return 0;
        int pre_delta = A[1] - A[0];
        int num = 2;
        vector<int> total;
        for(int i=2; i<A.size(); ++i)
        {
            int delta = A[i] - A[i-1];
            if(delta == pre_delta)
            {
                num++;
                if(i == A.size()-1 && num >= 3)
                {
                    total.push_back(num);
                }
            }
            else
            {
                if(num >= 3)
                {
                    total.push_back(num);
                }
                num = 2;
            }
            pre_delta = delta;
        }
        if(total.empty()) return 0;
        int max = *max_element(total.begin(), total.end());
        vector<int> dp(max+1, 0);
        //dp[3] = 1;
        for(int i=3; i<=max; ++i)
        {
            dp[i] = dp[i-1]+ i-2;
        }

        int res = 0;
        for(auto& i: total)
        {
            res += dp[i];
        }

        return res;
    }

    int numberOfArithmeticSlices2(vector<int>& A)
    {
        int count = 0;
        for (int i = 0; i < A.size(); i++)
        {
            int diff = A[i] - A[i+1];
            for (int j = i+2; j < A.size(); j++)
            {
                if (diff == A[j-1] - A[j])
                    count++;
                else
                    break;
            }
        }
        return count;
    }

    int numberOfArithmeticSlices3(vector<int>& A) {
        int n = A.size();

        //base case
        if(n <= 2)
            return 0;

        if(n == 3){
            if(A[2] - A[1] == A[1] - A[0])
                return 1;
            else
                return 0;
        }

        int total = 0;
        int count = 0;

        bool asEnd = false, asStart = false;
        for(int i = 2; i < n; i++){
            //find arithmetic series
            if( (A[i] - A[i - 1]) == (A[i - 1] - A[i - 2])){
                count++;
                if(!asStart)
                    asStart = true;
            }
            else{
                asEnd = true;
            }

            //count no. of sub arithmetic series
            if(asStart && asEnd){
                total += (count*(count + 1))/2;
                asStart = false;
                asEnd = false;
                count = 0;   //reset count
            }
        }
        if(asStart)
            total += (count*(count + 1))/2;
        return total;
    }

    int countSubstrings(string s)
    {
        /*
        int n = s.size();
        if(n <= 1) return n;
        int count = 0;
        for(int st=0; st<n; ++st)
        {
            for(int e=st; e<n; ++e)
            {
                if(isPalin(s.substr(s, e+1)))
                    count++;
            }
        }

        return count;
        */
        return 0;
    }

    int countSubstrings1(string s)
    {
        int n = s.size();
        if(n <= 1) return n;
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        int count = 0;
        for(int i=0; i<n; ++i)
        {
            dp[1][i] = 1;
        }
        count += n;
        for(int i=0; i<n-1; ++i)
        {
            if(s[i] == s[i+1])
            {
                dp[2][i] = 1;
                count++;
            }
        }
        for(int l=3; l<=n; ++l)
        {
            for(int i=0; i<n-l+1; ++i)
            {
                if((s[i] == s[i+l-1]) && dp[l-2][i+1])
                {
                    dp[l][i] = 1;
                    count++;
                }
            }
        }
        return count;
    }

    int minimumDeleteSum(string s1, string s2)
    {

        return 0;
    }

    int minDistance(string word1, string word2)
    {
        if(word1.empty() || word2.empty())
        {
            return word1.empty()?word2.size():word1.size();
        }
    }

    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs)
    {

        return 0;
    }

    int shoppingOffers_rec(vector<int>& price, vector<vector<int>>& special, vector<int>& needs)
    {
        vector<int> tmp = needs;
        for(auto & item: tmp)
        {
            //ifitem
        }
        return 0;
    }

    int findLongestChain(vector<vector<int>>& pairs)
    {
        if(pairs.empty()) return 0;
        vector<vector<int>> relations(n, vector<int>(n, 0));
        for(int i=0; i<pairs.size(); ++i)
        {
            for(int j=0; j<pairs.size(); ++j)
            {
                if(j == i) continue;
                if(pairs[j][0] > pairs[i][1])
                {
                    relations[i][j] = 1;
                }
            }
        }
    }

private:
    vector<int> _sums;
};

#endif // DPREL_H
