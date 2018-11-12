#ifndef DPREL_H
#define DPREL_H

#include <vector>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <map>

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

private:
    vector<int> _sums;
    vector<vector<int>> m_;
};

#endif // DPREL_H
