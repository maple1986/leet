#include <vector>
#include <priority_queue>

using namespace std;

vector<int> smallestRange(vector<vector<int>> &nums)
{
    if (nums.empty())
        return {};
    if (nums.size() == 1)
        return {nums[0][0], nums[0][0]};
    int n = nums.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> iter(nums.size(), 0);
    int maxN = INT_MIN;
    for (int i = 0; i < n; ++i)
    {
        if (nums[i].empty())
            return {};
        maxN = max(maxN, nums[i][0]);
        pq.push({nums[i][0], i});
    }
    //vector<int> res({pq.top().first, maxN});
    //int lastPop = pq.top().second;
    int res1 = pq.top().first, res2 = maxN;
    while (true)
    {
        auto cur = pq.top();
        pq.pop();
        lastPop = cur.second;
        iter[lastPos]++;
        if (iter[lastPos] >= nums[lastPos].size())
            break;
        pq.push({nums[iter[lastPos]], lastPos});
        maxN = max(maxN, nums[iter[lastPos]]);
        if (res2 - res1 > maxN - pq.top().first)
        {
            res1 = pq.top().first;
            res2 = maxN;
        }
    }
    return {res1, res2};
}

int consecutiveNumbersSum(int N)
{
    if(N<2) return 1;
    int res=0, size=1;
    for(int m=1;;m++)
    {
        int mx = N-m*(m-1)/2;
        if(mx<=0)break;
        if(mx%m==0) res++;
    }
    return res;
}