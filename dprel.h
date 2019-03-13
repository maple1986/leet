#ifndef DPREL_H
#define DPREL_H

#include <vector>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <numeric>
#include "utils.h"
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
        vector<int> dp(prices.size(), 0);
        for(int i=1; i<prices.size(); ++i)
        {
            int delta = prices[i] - prices[i-1] + dp[i-1];
            dp[i] = delta>0?delta:0;
        }
        int res = *max_element(dp.begin(), dp.end());
        return res>0?res:0;
        /*
        if(prices.empty()) return 0;
        //vector<int> dp(prices.size(), 0);
        int lowest = prices[0];
        int maxpro = 0;
        for(int i=1; i<prices.size(); ++i)
        {
            //int delta = prices[i] - prices[i-1] + dp[i-1];
            //dp[i] = delta>0?delta:0;
            if(prices[i] > lowest)
            {
                maxpro = max(maxpro, prices[i]-lowest);
            }
            else
            {
                lowest = prices[i];
            }
        }
        return maxpro;
        */
    }
    int maxProfit12(vector<int>& prices) {
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

    int maxProfit2(vector<int>& prices) {
        if(prices.size() < 2) return 0;
        int res = 0;
        for(int i=1; i<prices.size(); ++i)
        {
            int delta = prices[i] - prices[i-1];
            if(delta > 0) res += delta;
        }
        return res;
    }
    //{3,3,5,0,0,3,1,4};
    int maxProfit3(vector<int>& prices) {
        if(prices.size() < 2) return 0;
        int res = 0;
        int k = 2;
        int n = prices.size();
        vector<vector<int>> profits(k+1, vector<int>(n, 0));
        for(int i=1; i<=k; ++i)
        {
            for(int j=0; j<prices.size(); ++j)
            {
                for(int s=0; s<j; ++s)
                {
                    int tmp = prices[j]-prices[s]+profits[i-1][s];
                    profits[i][j] = max(profits[i][j], tmp);
                    profits[i][j] = max(profits[i][j], profits[i][j-1]);
                }
                //Utils::printV(profits[i]);
            }
            Utils::printVV(profits);
        }

        return *max_element(profits[k].begin(), profits[k].end());
    }

    int maxProfit(vector<int>& prices, int fee)
    {

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

    int maxSubArray12(vector<int>& nums) {
        if(nums.empty()) return 0;
        int maxEndingHere = nums[0];
        int maxSofar = nums[0];
        for(int i=1; i<nums.size(); ++i)
        {
            maxEndingHere = maxEndingHere>0?maxEndingHere+nums[i]:nums[i];
            maxSofar = max(maxSofar, maxEndingHere);
        }
        return maxSofar;
    }

    int maxSubArray13(vector<int>& nums) {
        if(nums.empty()) return 0;
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        int res = dp[0];
        for(int i=1; i<nums.size(); ++i)
        {
            dp[i] = dp[i-1]>0?dp[i-1]+nums[i]:nums[i];
            res = max(res, dp[i]);
        }
        return res;
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

    //"cbbd"

    string longestPalindrome(string s)
    {
        int n = s.size();
        if(n <= 1) return s;
        int res = 1;
        int left  = 0;
        int right = 0;
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int l=1; l<=n; ++l)
        {
            for(int i=0; i+l<=n; ++i)
            {
                int j =l+i-1;
                if(i == j)
                {
                    dp[i][j] = 1;
                    continue;
                }
                if(i+1 == j)
                {
                    dp[i][j] = (s[i]==s[j]?2:0);
                    continue;
                }
                if(s[i] == s[j] && dp[i+1][j-1])
                {
                    dp[i][j] = dp[i+1][j-1]+2;
                }
                else
                {
                    dp[i][j] = 0;
                }
            }
        }

        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(res < dp[i][j])
                {
                    left = i;
                    right = j;
                    res = dp[i][j];
                }
            }
        }

        return s.substr(left, right-left+1);
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


    int numWays2(int n, int k) {
        if(n == 0) return 0;
        if(n == 1) return k;
        if(n == 2) return k*k;
        vector<int> dp(n+1, 0);
        dp[1] = k, dp[2] = k*k;
        for(int i=3; i<=n; ++i)
        {
            dp[i] = dp[i-1]*(k-1) + dp[i-2]*(k-1);
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
        int l1 = s1.length();
        int l2 = s2.length();
        m_ = vector<vector<int>>(l1+1, vector<int>(l2+1, INT_MAX));
        return dp(s1, l1, s2, l2);
    }

    int dp(const string& s1, int i, const string& s2, int j)
    {
        if(i == 0 && j ==0) return 0;
        if(m_[i][j] !=INT_MAX)
        {
            return m_[i][j];
        }
        if(i == 0)
        {
            m_[i][j] = dp(s1, i, s2, j-1) + s2[j-1];
            return m_[i][j];
        }
        if(j == 0)
        {
            m_[i][j] = dp(s1, i-1, s2, j) + s1[i-1];
            return m_[i][j];
        }
        if(s1[i-1] == s2[j-1])
        {
            m_[i][j] = dp(s1, i-1, s2, j-1);
            return m_[i][j];
        }
        else
        {
            m_[i][j] =  min(dp(s1, i, s2, j-1)+s2[j-1], dp(s1, i-1, s2, j)+s1[i-1]);
            return m_[i][j];
        }
    }

    int minimumDeleteSum_dp(string s1, string s2)
    {
        int l1 = s1.length();
        int l2 = s2.length();
        vector<vector<int>> dp(l1+1, vector<int>(l2+1, 0));
        dp[0][0] = 0;
        int sum1 = 0, sum2 = 0;
        for(int i=1; i<=l1; ++i)
        {
            dp[i][0] = 0;
            sum1 += s1[i-1];
        }
        for(int i=1; i<=l2; ++i)
        {
            dp[0][i] = 0;
            sum2 += s2[i-1];
        }
        for(int i=1; i<=l1; ++i)
        {
            for(int j=1; j<=l2; ++j)
            {
                if(s1[i-1] == s2[j-1])
                {
                    dp[i][j] = dp[i-1][j-1] + 2*s1[i-1];
                }
                else
                {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return sum1 + sum2 - dp[l1][l2];
    }


    int minDistance(string word1, string word2)
    {
        if(word1.empty() || word2.empty())
        {
            return word1.empty()?word2.size():word1.size();
        }
        int l1 = word1.length();
        int l2 = word2.length();
        m_ = vector<vector<int>>(l1+1, vector<int>(l2+1, INT_MAX));
        return dp1(word1, l1, word2, l2);
    }

    int dp1(const string& s1, int i, const string& s2, int j)
    {
        if(i == 0 && j ==0) return 0;
        if(m_[i][j] !=INT_MAX)
        {
            return m_[i][j];
        }
        if(i == 0)
        {
            m_[i][j] = j;
            return m_[i][j];
        }
        if(j == 0)
        {
            m_[i][j] = i;
            return m_[i][j];
        }
        if(s1[i-1] == s2[j-1])
        {
            m_[i][j] = dp1(s1, i-1, s2, j-1);
            return m_[i][j];
        }
        else
        {
            m_[i][j] =  min(dp1(s1, i, s2, j-1)+1, dp1(s1, i-1, s2, j)+1);
            return m_[i][j];
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
        int n = pairs.size();
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

    int depth_len(int i, int& depth, vector<vector<int>>& relations)
    {
        for(int k=0; k<relations[i].size(); ++k)
        {

        }
        return 0;
    }

     int findLength(vector<int>& A, vector<int>& B)
     {
         int len1 = A.size();
         int len2 = B.size();

         vector<vector<int>> dp(len1+1, vector<int>(len2+1, 0));
         dp[len1][len2] = 0;
         for(int i=0; i<len1; ++i)
         {
             for(int j=0; j<len2; ++j)
             {
                 if(A[len1-i-1] == B[len2-j-1])
                 {
                     dp[i][j] = dp[i+1][j+1]+1;
                 }
                 else
                 {
                     dp[i][j] = max(dp[i][j+1], dp[i+1][j]);
                 }
             }
         }
         int max_elem = 0;
         for(int i=0; i<=len1; ++i)
         {
             max_elem = max(max_elem, *max_element(dp[i].begin(), dp[i].end()));
         }
         return max_elem;
     }

    int maxSubarry(string s1, string s2)
    {
        int len1 = s1.length();
        int len2 = s2.length();

        vector<vector<int>> dp(len1+1, vector<int>(len2+1, 0));
        dp[len1][len2] = 0;
        for(int i=0; i<len1; ++i)
        {
            for(int j=0; j<len2; ++j)
            {
                if(s1[len1-i-1] == s2[len2-j-1])
                {
                    dp[i][j] = dp[i+1][j+1]+1;
                }
                else
                {
                    dp[i][j] = 0;
                }
            }
        }
        int max_elem = 0;
        for(int i=0; i<=len1; ++i)
        {
            max_elem = max(max_elem, *max_element(dp[0].begin(), dp[0].end()));
        }
        return max_elem;
    }

    void dp2()
    {

    }

    int step[2][2] = {{0,1},{1,0}};
    int minPathSum(vector<vector<int>>& grid)
    {
        int m = grid.size();
        if(!m) return 0;
        int n = grid[0].size();
        if(!n) return 0;
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        dp[0][0] = grid[0][0];
        for(int i=1; i<m; ++i)
        {
            dp[i][0] = dp[i-1][0]+grid[i][0];
        }
        for(int j=1; j<n; ++j)
        {
            dp[0][j] = dp[0][j-1]+grid[0][j];
        }

        for(int i=1; i<m; ++i)
        {
            for(int j=1; j<n; ++j)
            {
                dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]);
                //dp[i][j] = min(dp[i][j-1]+grid[0][j];
            }
        }

        return dp[m-1][n-1];
    }

    int integerBreak(int n) {

    }

    int countNumbersWithUniqueDigits(int n)
    {

    }
    //[1,2,3,1]
    int rob2(vector<int>& nums)
    {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];

        int pre1 = 0, cur1 = 0;
        for(int i=0; i<nums.size()-1; ++i)
        {
            int temp = pre1;
            pre1 = cur1;
            cur1 = max(temp + nums[i], pre1);
        }
        int pre2 = 0, cur2 = 0;
        for(int i=1; i<nums.size(); ++i)
        {
            int temp = pre2;
            pre2 = cur2;
            cur2 = max(temp + nums[i], pre2);
        }
        return max(cur1, cur2);
    }

    int lengthOfLIS(vector<int>& nums)
    {
        if(nums.empty()) return 0;
        int n = nums.size();
        vector<int> dp(n, 1);
        dp[0] = 1;
        int ans = 1;
        for(int i=1; i<n; ++i)
        {
            for(int j=0; j<i; ++j)
            {
                if(nums[i]>nums[j])
                {
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }

    int findTargetSumWays494(vector<int>& nums, int S) {
        int n = nums.size();
        if(!n) return 0;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(S > sum || S < -sum) return 0;
        vector<vector<int>> dp(n+1, vector<int>(2*sum+1, 0));
        dp[0][sum] = 1;
        for(int i=0; i<n; ++i)
        {
            int cur = nums[i];
            for(int j=0; j<2*sum+1; ++j)
            {
                if(dp[i][j])
                {
                    dp[i+1][j+cur] += dp[i][j];
                    dp[i+1][j-cur] += dp[i][j];
                }
            }
        }
        return dp[n][S+sum];
    }

    int lenLongestFibSubseq873(vector<int>& A)
    {
        if(A.size() < 3) return 0;
        int res = 0;
        unordered_set<int> m(A.begin(), A.end());

        for(int i=0; i<A.size(); ++i)
        {
            for(int j=i+1; j<A.size(); ++j)
            {
                int a = A[i];
                int b = A[j];
                int c = a+b;
                int l = 2;
                while(m.count(c))
                {
                    a = b;
                    b = c;
                    c = a+b;
                    l++;
                }
                res = max(res, l);
            }
        }
        return res;
    }

    int findSubstringInWraproundString(string p)
    {
        int n = p.size();
        if(n <= 1) return n;
        set<char> m;
        int res = 0;
        vector<int> dp(n);
        for(int len=1; len<=n; ++len)
        {
            m.clear();
            for(int start=0; start<=n-len; ++start)
            {
                int end = start+len-1;
                if(1==len)
                {
                    dp[start] = 1;
                    if(!m.count(p[start]))
                    {
                        m.insert(p[start]);
                        res++;
                    }
                }
                else
                {
                    if(dp[start])
                    {
                        if((p[end-1] == 'z' && p[end] == 'a') || p[end]-p[end-1] == 1)
                        {
                            dp[start] = 1;
                            if(!m.count(p[start]))
                            {
                                m.insert(p[start]);
                                res++;
                            }
                        }
                        else
                        {
                            dp[start] = 0;
                        }
                    }
                }
            }
        }
        return res;
    }

    int findSubstringInWraproundString1(string p)
    {
        int n = p.size();
        if(n <= 1) return n;
        vector<int> m(26, 0);
        int res = 0;
        int curLen = 1;
        for(int i=0; i<n; ++i)
        {
            if(i > 0 && (p[i] - p[i-1] == 1 || p[i] == 'a' && p[i-1] == 'z'))
            {
                ++curLen;
            }
            else
            {
                curLen = 1;
            }
            m[p[i]-'a'] = max(m[p[i]-'a'], curLen);
        }

        for(int i: m)
        {
            res += i;
        }
        return res;
    }

    int maxSubArray53(vector<int>& nums)
    {
        if(nums.empty()) return 0;
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        int maxSum = dp[0];
        for(int i=1; i < nums.size(); ++i)
        {
            dp[i] = dp[i-1]>0?nums[i]+dp[i-1]:nums[i];
            maxSum = max(maxSum, dp[i]);
        }
        return maxSum;
    }


    int maxSubArray53_2(vector<int>& nums)
    {
        if(nums.empty()) return 0;
        int maxEndingHere = nums[0], maxSofar = nums[0];
        for(int i=1; i < nums.size(); ++i)
        {
            maxEndingHere = max(maxEndingHere+nums[i], nums[i]);
            maxSofar = max(maxSofar, maxEndingHere);
        }
        return maxSofar;
    }

    int maxProduct152(vector<int>& nums)
    {
        int n = nums.size();
        if(n == 0) return 0;
        vector<int> positive(n, 0);
        vector<int> negative(n, 0);
        positive[0] = nums[0];
        negative[0] = nums[0];
        int ans = nums[0];
        for(int i=1; i<nums.size(); ++i)
        {
            positive[i] = max(max(positive[i-1]*nums[i], nums[i]), negative[i-1] * nums[i]);
            negative[i] = min(min(positive[i-1]*nums[i], nums[i]), negative[i-1] * nums[i]);
            ans = max(positive[i], ans);
        }
        return ans;
    }

    int numSubarrayProductLessThanK713(vector<int>& nums, int k)
    {
        if(nums.empty()) return 0;
        if( k == 0) return 0;
        vector<int> dp(nums.size(), -1);
        int cur_product = 1;
        if(nums[0] < k)
        {
            dp[0] = 0;
            cur_product = nums[0];
        }
        for(int i=1; i<nums.size(); ++i)
        {
            if(dp[i-1] < 0)
            {
                if(nums[i] < k)
                {
                    dp[i] = i;
                    cur_product = nums[i];
                }
                else
                {
                    cur_product = 1;
                }
            }
            else
            {
                cur_product *= nums[i];
                if(cur_product < k)
                {
                    dp[i] = dp[i-1];
                }
                else
                {
                    int j = dp[i-1];
                    while(cur_product/nums[j] >= k)
                    {
                        j++;
                    }
                    if(j < i)
                    {
                        dp[i] = -1;
                    }
                }
            }
        }
    }

    int numFactoredBinaryTrees(vector<int>& A)
    {
        if(A.size() < 2) return A.size();
        sort(A.begin(), A.end());
        map<int, int> m;
        for(int i=0; i<A.size(); ++i)
        {
            m.insert(make_pair(A[i], i));
        }
        vector<int> dp(A.size(), 1);
        for(int i=1; i<A.size(); ++i)
        {
            for(int j=0; j<i; ++j)
            {
                if(A[i]%A[j] == 0)
                {
                     int key = A[i]/A[j];
                     auto it = m.find(key);
                     if(it != m.end())
                     {
                        dp[i] += dp[j]*dp[it->second];
                     }

                }
            }
        }
        return accumulate(dp.begin(), dp.end(), 0);
    }

    int maxLen(vector<int> &a)
    {
        if(a.size() <= 2) return a.size();
        unordered_map<int, int> dict;
        int res = 0;
        int cur = 0;
        for(int i=0; i<a.size(); ++i)
        {
            if(dict.count(a[i]))
            {
                dict[a[i]] = i;
                cur++;
            }
            else
            {
                if(dict.size() < 2)
                {
                    dict[a[i]] = i;
                    cur++;
                }
                else
                {
                    auto it = dict.begin();
                    int end1 = dict.begin()->second;
                    int end2 = (++it)->second;
                    end1 > end2?dict.erase(it):dict.erase(dict.begin());
                    dict[a[i]] = i;
                    int end = end1>end2?end2:end1;
                    cur = i- end;
                }
            }
            res = max(res, cur);
        }
        return res;
    }

    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K)
    {

    }

    vector<int> _sums;
    vector<vector<int>> m_;


    bool wordBreak(string& s, vector<string>& wordDict)
    {
        if(wordDict.empty() || s.empty()) return false;
        int n = s.size();
        unordered_set<string> wordDictIndex(wordDict.begin(), wordDict.end());
        vector<int> dp(n+1, 0);
        dp[0] = 1;
        for(int i=1; i<=n; ++i)
        {
            for(int j=0; j<i; ++j)
            {
                string s1 = s.substr(j, i-j);
                if(wordDictIndex.count(s1) && dp[j])
                {
                    dp[i] = 1;
                }
            }
        }
        return dp[n];
    }

    vector<string> wordBreak2(string s, vector<string>& wordDict) {
        if(wordDict.empty() || s.empty()) return {};
        int n = s.size();
        unordered_map<string, int> wordDictIndex;
        for(int i=0; i<wordDict.size(); ++i)
        {
            wordDictIndex[wordDict[i]] = i;
        }
        vector<vector<int>> dp(n+1, vector<int>());
        dp[0] = {-1};

        for(int i=1; i<=n; ++i)
        {
            for(int j=0; j<i; ++j)
            {
                string s1 = s.substr(j, i-j);
                if(wordDictIndex.count(s1) && !dp[j].empty())
                {
                    vector<int> tmp = dp[j];
                    //for()
                }
            }
        }
        return {};
    }

    int maxEnvelopes(vector<pair<int, int>>& envelopes)
    {
        int n = envelopes.size();
        if(n <= 1) return n;
    }

    string encode(string &s) {

    }

    int minFlipsMonoIncr1(string S) {
        int n = S.length();
        if(n<=1) return 0;
        vector<int> dp0(n+1, 0);
        vector<int> dp1(n+1, 0);
        //dp0[0] = S[0]-'0';
        for(int i=0; i<n; ++i)
        {
            dp0[i+1] = dp0[i] + S[i] - '0';
        }
        //dp1[n] = '1' - S[n-1];
        for(int i=n-1; i>=0; --i)
        {
            dp1[i] = dp1[i+1] + '1' - S[i];
        }
        int res = n;
        for(int i=0; i<=n; ++i)
        {
            res = min(res, dp0[i] + dp1[i]);
        }

        return res;
    }

    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if(obstacleGrid.empty() || obstacleGrid[0].empty()) return 0;
        int n = obstacleGrid.size();
        int m = obstacleGrid[0].size();
        vector<vector<int>> mem(n, vector<int>(m, 0));
        if(obstacleGrid[0][0] == 1) return 0;
        mem[0][0] = 1;

        for(int i=1; i<m; ++i)
        {
            if(obstacleGrid[0][i] == 1 || mem[0][i-1] == 0)
                mem[0][i] = 0;
            else mem[0][i] = 1;
        }

        for(int i=1; i<n; ++i)
        {
            if(obstacleGrid[i][0] == 1 || mem[i-1][0] == 0)
                mem[i][0] = 0;
            else mem[i][0] = 1;
        }


        for(int i=1; i<n; ++i)
        {
            for(int j=1; j<m; ++j)
            {
                if(obstacleGrid[i][j] == 0)
                {
                    mem[i][j] = mem[i-1][j] + mem[i][j-1];
                }
                else
                {
                    mem[i][j] = 0;
                }
            }
        }
        return mem[n-1][m-1];
    }

    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        vector<vector<int>> count(n+2, vector<int>(n+2, 0));
        for(int l=1; l<=n; ++l)
        {
            for(int i=1; i<=n-l+1; ++i)
            {
                int j = i+l-1;
                for(int k=i; k<=j; ++k)
                {
                    int cur = count[i][k-1] + count[k+1][j] + nums[i-1]*nums[k]*nums[j+1];
                    printf("len[%d], s[%d], c[%d]\n", l, i, cur);
                    count[i][j] = max(count[i][j], cur);
                }
                Utils::printVV(count);
            }
        }
        return count[1][n];
    }
    vector<int> cheapestJump(vector<int> &A, int B) {
        int n = A.size();
        if(!n|| !B) return {};
        vector<int> dp(n, -1);
        dp[0] = A[0];
        vector<vector<int>> steps(n, vector<int>());
        steps[0] = {1};
        /*
        for(int i=1; i<=B; ++i)
        {
            if(A[i] != -1 && dp[0] != -1)
            {
                dp[i] = dp[0] + A[i];
                steps[i].push_back(1);
                steps[i].push_back(i+1);
            }

        }
        */
        for(int i=1; i<n; ++i)
        {
            if(A[i] != -1)
            {
                for(int j=i-B; j<i; ++j)
                {
                    if(j<0) continue;
                    if(dp[j] != -1)
                    {
                        //dp[i] = (dp[i]==-1)?dp[j]+A[i]:min(dp[i], dp[j]+A[i]);
                        if(dp[i] == -1)
                        {
                            dp[i] = dp[j]+A[i];
                            steps[i] = steps[j];
                            steps[i].push_back(i+1);
                        }
                        else
                        {
                            if(dp[i] > dp[j] + A[i])
                            {
                                steps[i] = steps[j];
                                steps[i].push_back(i+1);
                                dp[i] = dp[j] + A[i];
                            }
                            else if(dp[i] == dp[j] + A[i])
                            {
                                if(steps[i].size()-1 < steps[j].size())
                                {
                                    steps[i] = steps[j];
                                    steps[i].push_back(i+1);
                                }
                            }
                        }
                    }
                }
            }
        }
        //Utils::printV(steps[n-1]);
        return steps[n-1];
    }

    int matched(string &S, int endIndex, string &T, int s) {
        for(int i=0; i != endIndex && s < T.length(); ++i)
        {
            if(S[i] == T[s]) s++;
        }
        return s;
    }

    string minWindow(string &S, string &T) {
        // Write your code here
        int n = S.length();
        int t = T.length();
        if(n == 0 || t == 0) return "";
        if(t > n) return "";
        if(t == n) return S==T?S:"";
        vector<int> dp0(n, 0);
        for(int l=t; l<=n; ++l)
        {
            vector<int> dp1(n, 0);
            for(int i=0; i<n-l; ++i)
            {
                dp1[i] = matched(S, i+t, T, dp0[i]);
                if(dp1[i] == t)
                {
                    dp1[i] == t;
                }
            }
            dp0.swap(dp1);
            Utils::printV(dp0);
        }
        return "";
    }
    //[9,3,6,2,7]
    int longestIncreasingSubsequence(vector<int> &nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        vector<int> dp(n, 1);
        //dp[0] = 1;
        int ans = 1;
        for(int i=1; i<n; ++i)
        {
            for(int j=0; j<i; ++j)
            {
                if(nums[i]>nums[j])
                {
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
    //[1,3,5,4,7]
    int findNumberOfLIS(vector<int> &nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        vector<pair<int, int>> dp(n, {1,1});
        int ans = 1;
        for(int i=1; i<n; ++i)
        {
            for(int j=0; j<i; ++j)
            {
                if(nums[i]>nums[j])
                {
                    //dp[i] = max(dp[i], dp[j]+1);
                    if(dp[j].first+1 > dp[i].first)
                    {
                        dp[i].first = dp[j].first+1;
                        dp[i].second= dp[j].second;
                    }
                    else if(dp[j].first+1 == dp[i].first)
                    {
                        dp[i].second += dp[j].second;
                    }
                }
            }
            ans = max(ans, dp[i].first);
        }
        int res = 0;
        for(int i=0; i<n; ++i)
        {
            if(dp[i].first == ans)
                res += dp[i].second;
        }
        return res;
    }

    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        if(matrix.empty() || matrix[0].empty())
            return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> sum(m+1, vector<int>(n+1, 0));
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                sum[i][j+1] = sum[i][j]+matrix[i][j];
            }
        }
        int maxArea = 0;
        vector<int> res(n+1, 0);
        for(int l=1; l<=m; ++l)
        {
            for(int j=0; j<n; ++j)
            {
                for(int i=0; i+l<m; ++i)
                {

                }
            }
        }
        return maxArea;
    }

    int splitArray(vector<int>& nums, int m)
    {
        int n = nums.size();
        vector<vector<int>> mem_(m+1, vector<int>(n, INT_MAX));
        vector<int> sum_(n, 0);
        sum_[0] = nums[0];
        for(int i=1; i<n; ++i)
        {
            sum_[i] = sum_[i-1] + nums[i];
        }
        if(m == 1) return sum_[n-1];
        for(int i=0; i<n; ++i)
        {
            mem_[1][i] = sum_[i];
        }
        for(int i=2; i<=m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                for(int k=0; k<j; ++k)
                {
                    if(k<i-2) continue;
                    mem_[i][j] = min(mem_[i][j], max(mem_[i-1][k], sum_[j] - sum_[k]));
                }
            }
        }
        //Utils::printVV(mem_);
        return mem_[m][n-1];
    }

    int splitArray2(vector<int>& nums, int m) {
        int n = nums.size();
        //dp[i][k] means max sum of k parts of elements 0..i
        vector<vector<long>> dp(n, vector<long>(m+1, INT_MAX));
        //sum array is used to calculate range sum of i..j
        vector<long> sum(n, 0);
        for (int i = 0; i < n; i++) {
            sum[i] = i == 0 ?nums[0] :(sum[i-1] + nums[i]);
        }
        // build dp from 0 to n-1 emelents
        for (int i = 0; i < nums.size(); i++) {
            //elements from 0 to indexi can be divided to i+1 parts mostly;
            int maxDivide = min(m, i+1);
            //for each dividing choice
            for (int k = 1; k <= maxDivide; k++) {
                if (k == 1) {
                    dp[i][k] = sum[i];
                    continue;
                }
                //divide 0..i to k parts, so i can be with i-1; i-1, i-2...; i-1, i-2..k-1;
                for (int j = i; j >= k-1; j--) {//0..k-2 can be divided to mostly k-1 parts
                    long partsum = sum[i] - sum[j] + nums[j];
                    if (partsum > dp[i][k]) break; //early termination
                    dp[i][k] = min(dp[i][k], max(partsum, dp[j-1][k-1]));
                }
            }
        }
        return dp[n-1][m];
    }


    int numDecodings2(string s) {
        int n = s.length();
        if(n == 0 || s[0] == '0') return 0;
        const int Mod = 10e9 + 7;
        vector<long> dp(n, 0);
        if(s[0] == '*') dp[0] = 9;
        else dp[0] = 1;
        for(int i=1; i<n; ++i)
        {
            if(s[i] == '0') dp[i] = 0;
            else if(isdigit(s[i])) dp[i] = dp[i-1];
            else dp[i] = 9*dp[i-1];

            if(s[i-1] != '*' && s[i] != '*')
            {
                int twodigit = (s[i-1]-'0')*10 + s[i]-'0';
                if(twodigit>=10 && twodigit<=26)
                {
                    if(i>1)
                        dp[i] += dp[i-2];
                    else dp[i] += 1;
                }
            }
            else if(s[i-1] == '*' && s[i] == '*')
            {
                if(i>1)
                    dp[i] += dp[i-2]*15;
                else
                    dp[i] += 15;
            }
            else if(s[i-1] == '*')
            {
                if(s[i] >= 0 && s[i] <= 6)
                {
                    dp[i] += dp[i-2]*2;
                }
            }
            else
            {
                if(s[i-1] == 1)
                {
                    dp[i] += dp[i-2]*9;
                }
                else if(s[i-1] == 2)
                {
                    dp[i] += dp[i-2]*6;
                }
            }

        }
        return dp[n-1]%Mod;
    }

    int LeastSubsequences(vector<int> &arrayIn) {
        int n = arrayIn.size();
        if(n <= 1) return n;
        vector<int> ends(n, -1);
        ends[0] = arrayIn[0];
        int len = 0;
        for(int i=1; i<arrayIn.size(); ++i)
        {
            if(arrayIn[i] < ends[0]) ends[0] = arrayIn[i];
            else if(arrayIn[i] >= ends[len]) ends[++len] = arrayIn[i];
            else
            {
                auto it = upper_bound(ends.begin(), ends.begin()+len, arrayIn[i]);
                *it = arrayIn[i];
            }
        }
        return len+1;
    }

    int uniquePath(int height, int width) {
        // Write your code here
        int MOD = 1e9+7;
        vector<vector<long>> dp(height+1, vector<long>(width+1, 0));
        dp[1][1] = 1;
        for(int i=0; i<height; ++i)
        {
            dp[i][1] = 1;
        }
        for(int i=0; i<width; ++i)
        {
            dp[1][i] = 1;
        }
        for(int i=2; i<=height; ++i)
        {
            for(int j=2; j<=width; ++j)
            {
                //dp[i][j] = dp
            }
        }
    }

    bool cardGame2(vector<int> &cost, vector<int> &damage, int totalMoney, int totalDamage) {
        // Write your code here
        if(totalDamage == 0) return true;
        if(totalMoney == 0) return false;
        //vector<vector<int>> dp(totalMoney+1, vector<int>(totalDamage+1, 0));
        //for(int i=1; i<=totalMoney)
        if(totalDamage == 0) return true;
        if(totalMoney == 0) return false;
        int m = cost.size();
        vector<vector<int>> dp(m+1, vector<int>(totalMoney+1, 0));
        for(int i=1; i<=m; ++i)
        {
            for(int j=1; j<=totalMoney; ++j)
            {
                dp[i][j] = dp[i-1][j];
                if(j >= cost[i-1])
                    dp[i][j] = max(dp[i][j], dp[i-1][j-cost[i-1]]+damage[i-1]);
                //Utils::printVV(dp);
                //if(dp[i][j] >= totalDamage) return true;
            }
        }
        Utils::printVV(dp);
        return false;
    }

    int pickFruits(vector<int> &arr) {
        // Write your code here.
        int n = arr.size();
        if(n <= 2) return n;
        int l = 0, r = 0;
        int count = 2;
        unordered_map<int, int> fruits;
        int res = 0;
        for(; r<n; ++r)
        {
            fruits[arr[r]]++;
            while(fruits.size() > 2)
            {
                if(fruits[arr[l]]-- == 1)
                {
                    fruits.erase(arr[l]);
                }
                l++;
            }
            res = max(res, r-l+1);
        }
        return res;
    }

    int putBox(vector<int> &box, vector<int> &position) {
        // Write your code here
        
    }

    int maintenance(int n, int m, vector<pair<int, int>> &badcomputers) {
        // Write your code here
    }

    int numOfPlan(int n, int totalProfit, int totalCost, vector<int> &a, vector<int> &b) {
        // Write your code here
        /*
        int m = a.size();
        vector<vector<int>> dp(m+1, vector<int>(totalCost+1, 0));
        for(int i=1; i<=m; ++i)
        {
            for(int j=1; j<=totalMoney; ++j)
            {
                dp[i][j] = dp[i-1][j];
                if(j >= cost[i-1])
                    dp[i][j] = max(dp[i][j], dp[i-1][j-cost[i-1]]+damage[i-1]);
            }
        }
        Utils::printVV(dp);
        return false;
        */
        return 0;
    }

    int getMoneyAmount(int n) {
        if(n < 2) return 0;
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        for(int i=1; i<n; ++i)
        {
            dp[i][i+1] = i;
        }
        for(int len=3; len<=n; ++len)
        {
            for(int i=1; i<n; ++i)
            {
                int j = i+len-1;
                if(j > n) continue;
                int Min = INT_MAX;
                for(int k=i+1; k<j; ++k)
                {
                    int localMax = k + max(dp[i][k-1], dp[k+1][j]);
                    Min = min(Min, localMax);
                }
                dp[i][j] = Min;
                Utils::printVV(dp);
            }
        }
        return dp[1][n];
    }

    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        if(startFuel >= target) return 0;
        int n = stations.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
        for(int i=0; i<n; ++i)
        {
            dp[i][0] = startFuel;
            //dp[0][i] = startFuel;
        }
/*
        for(int j=1; j<=n; ++j)
        {
            for(int i=1; i<=n; ++i)
            {
                //dp[i] = max(dp[i], dp[i-1]+stations[j][1]);
                if(dp[i-1][j-1] >= stations[i-1][0])
                {
                    dp[i][j] = dp[i-1][j-1] + stations[i-1][1];
                    Utils::printVV(dp);
                }
                else dp[i][j] = dp[i-1][j];
                if(dp[i][j] >= target) return j;
            }
        }
*/
        //{{15,457},{156,194},{160,156},{230,314},{390,159},{621,20},{642,123},{679,301}};
        for(int i=1; i<=n; ++i)
        {
            for(int j=1; j<=i; ++j)
            {
                if(dp[i-1][j-1] >= stations[i-1][0])
                {
                    dp[i][j] = dp[i-1][j-1] + stations[i-1][1];
                }
                if( j<=i-1)
                    dp[i][j] = max(dp[i][j], dp[i-1][j]);
                //dp[i][j] = max(dp[i-1][j-1], 0);
                Utils::printVV(dp);
            }
        }
        return -1;
    }
    int minRefuelStops1(int target, int startFuel, vector<vector<int>>& stations) {
        if(startFuel >= target) return 0;
        int n = stations.size();
        vector<int> dp(n+1, 0);
        dp[0] = startFuel;
        for(int i=1; i<=n; ++i)
        {
            for(int j=i; j>=1; --j)
            {
                if(dp[j-1] >= stations[i-1][0])
                {
                    dp[j] = max(dp[j], dp[j-1] + stations[i-1][1]);
                }
            }
            Utils::printV(dp);
        }

        for(int j=1; j<=n; ++j)
        {
            if(dp[j] >= target) return j;
        }

        return -1;
    }

    int backPack(int m, vector<int> &A) {
        // write your code here
        int n = A.size();
        if(n == 0 || m == 0) return 0;
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        for(int i=1; i<=n; ++i)
        {
            for(int j=1; j<=m; ++j)
            {
                if(j < A[i-1])
                {
                    dp[i][j] = dp[i-1][j];
                    continue;
                }
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-A[i-1]]+A[i-1]);

            }
        }
        Utils::printVV(dp);
        return dp[n][m];
    }

    int backPack1(int m, vector<int> &A) {
        int n = A.size();
        if(n == 0 || m == 0) return 0;
        vector<int> dp(m+1, 0);
        for(int i=1; i<=n; ++i)
        {
            //for(int j=1; j<=m; ++j)
            //{
            for(int j=m; j>=1; --j)
            {
                if(j < A[i-1])
                {
                    continue;
                }
                dp[j] = max(dp[j], dp[j-A[i-1]]+A[i-1]);
            }
            Utils::printV(dp);
        }
        return dp[m];
    }

    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size(), n = nums2.size();
        if(k == 0) return {};
        string ans;
        for(int k1=0; k1<min(m, k); ++k1)
        {
            string res;
            int k2 = k-k1;
            string s1 = Klarge(nums1, k1);
            string s2 = Klarge(nums2, k2);
            int i1=0, i2=0;
            while(i1<k1 && i2<k2)
            {
                if(s1[i1] <= s2[i2])
                {
                    res += s2[i2];
                    i2++;
                }
                else
                {
                    res += s1[i1];
                    i1++;
                }
            }
            if(i1<k1) res += s1.substr(i1);
            else if(i2<k2) res += s2.substr(i2);
            if(res > ans) ans.swap(res);
        }
        vector<int> v;
        for(char c: ans)
        {
            if(v.empty() && c == '0') continue;
            v.push_back(c-'0');
        }
        return v;
    }

    string Klarge(vector<int>& nums, int k)
    {
        string res;
        int abandon = nums.size()-k;
        for(int i=0; i<nums.size(); ++i)
        {
            while(!res.empty() && res.back()-'0'<nums[i] && abandon>0)
            {
                res.pop_back();
                abandon--;
            }
            res.push_back(nums[i]-'0');
        }
        while(abandon>0)
        {
            res.pop_back();
            abandon--;
        }
        return res;
    }

    int integerReplacement(int n) {
        if(n == 1) return 0;
        mem_ = vector<int>(n+1, -1);
        int step = 0;
        //n_ = n;
        for(int i=1; i<=n; i*=2)
        {
            mem_[i] = step;
            step++;
        }
        return helper(n);
    }
    int helper(int n)
    {
        if(mem_[n] != -1) return mem_[n];
        int step = 0;
        if(n&1 == 0)
            step = helper(n/2);
        else
            step = 2+min(helper((n-1)/2), helper((n+1)/2));
        return mem_[n] = step;
    }
    vector<int> mem_;

    int integerReplacement1(int n) {

    }

    bool canPartition(vector<int>& nums) {
        if(nums.size()<=1) return false;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int n = nums.size();
        if(sum%2) return false;
        int target = sum/2;
        vector<vector<int>> dp(n, vector<int>(sum+1, 0));
        sort(nums.begin(), nums.end());
        dp[0][0] = 1;
        for(int i=1; i<=n; ++i)
        {
            for(int j=nums[i-1]; j<=target; ++j)
            {
                if(dp[i-1][j-nums[i-1]])
                    dp[i-1][j] = 1;
            }
        }
        return dp[n][target];
    }

    int minCut(string s) {
        int n = s.size();
        if(n<=1) return 0;
        vector<vector<int>> isParlin(n, vector<int>(n, 0));
        vector<int> minCuts(n, 0);
        iota(minCuts.begin(), minCuts.end(), 0);
        for(int i=0; i<n; ++i) isParlin[i][i] = 1;
        for(int len=2; len<=n; ++len)
        {
            for(int i=0; i<n; ++i)
            {
                int j = i+len-1;
                if(j>=n) continue;
                if(s[i]==s[j]&&((j-i<2)||isParlin[i+1][j-1]))
                {
                    isParlin[i][j] = 1;
                    minCuts[j+1] = min(minCuts[j+1], 1 + minCuts[i]);
                }   
            }
        }
        return minCuts[n-1];
    }

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        if(dungeon.empty() || dungeon[0].empty()) return 1;
        int m = dungeon.size(), n = dungeon[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, INT_MAX));
        dp[m-1][n-1] = max(1, 1-dungeon[m-1][n-1]);
        for(int i=m-1; i>=0; --i)
        {
            for(int j=n-1; j>=0; --j)
            {
                if(i == m-1 && j == n-1) continue;
                dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1])-dungeon[i][j]);
            }
            Utils::printVV(dp);
        }
        return dp[0][0];
    }
};



#endif // DPREL_H
