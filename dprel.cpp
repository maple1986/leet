#include "dprel.h"

DPRel::DPRel()
{

}

void DPRel::test()
{
    DPRel dprel;
    //int j = dprel.uniquePath(4, 5);
    vector<int> cost = {1,1,2,2}, damage = {1,2,4,5};
    int totalMoney = 4, totalDamage = 10;
    dprel.cardGame2(cost, damage, totalMoney, totalDamage);
    string s = dprel.longestPalindrome("abacab");
    vector<int> nums = {7,1,5,3,6,4};
    dprel.deleteAndEarn(nums);
    dprel.maxProfit(nums);

    vector<int> nums2 = {1,2,3,0,2};
    dprel.maxProfit_cooldown(nums2);
    //dprel.longestPalindromeSubseq("bbbab");
    dprel.minFlipsMonoIncr2("00110");
    dprel.minFlipsMonoIncr1("00110");
    vector<int> num3 = {0,1,1,0};
    dprel.minCostClimbingStairs(num3);

    printf("num of ways = [%d]\n", dprel.numWays(3, 1) == dprel.numWays1(3, 1));

    vector<int> num4 = {1, 2, 3, 8, 9, 10};
    dprel.numberOfArithmeticSlices(num4);

    dprel.countSubstrings1("aaa");

    int i = dprel.minimumDeleteSum_dp("delete", "leet");
    i = dprel.minDistance("eat", "sea");

    vector<int> nums5 = {1,2,3,2,1};
    vector<int> nums6 = {3,2,1,4,7};
    i = dprel.findLength(nums5, nums6);
    vector<int> num7 = {1,2,3,1};
    i = dprel.rob2(num7);
    vector<int> num8 = {4,10,4,3,8,9};
    i = dprel.lengthOfLIS(num8);
    vector<int> num9 = {1,1,1,1,1};
    i = dprel.findTargetSumWays494(num9, 3);
    i = dprel.findSubstringInWraproundString("zadcd");
    vector<int> num10 = {2, 4, 5, 10};
    i = dprel.numFactoredBinaryTrees(num10);
    vector<int> num11 = {3,2,3,1,5,2,5,1};
    i = dprel.maxLen(num11);
    string s1 = "leetcode";
    vector<string> dict = {"leet", "code"};
    i = dprel.wordBreak(s1, dict);
    vector<vector<int>> vv1 = {{0,0,0},{0,1,0},{0,0,0}};
    i = dprel.uniquePathsWithObstacles(vv1);
    vector<int> num12 = {3, 1, 5, 8};
    //i = dprel.maxCoins(num12);
    vector<int> num13 = {1,2,3,4,5};
    i = dprel.maxProfit3(num13);
    vector<int> num14 = {0,0,0,0,0,0};
    dprel.cheapestJump(num14, 3);
    string in1 = "jmeqksfrsdcmsiwvaovztaqenprpvnbstl";
    string in2 = "ms";
    string si = dprel.minWindow(in1, in2);
    vector<int> num15 = {1, 4, 4};
    i = dprel.splitArray(num15, 3);
    i = i+1;
}
