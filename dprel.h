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
};

#endif // DPREL_H
