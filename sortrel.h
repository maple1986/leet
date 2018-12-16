#ifndef SORTREL_H
#define SORTREL_H

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};


class sortrel
{
public:
    sortrel();
    static void test();
    int findRadius(vector<int>& houses, vector<int>& heaters)
    {
        if(houses.empty() || heaters.empty()) return 0;
        int max_radius = 0;
        sort(heaters.begin(), heaters.end());
        for(int i=0; i<houses.size(); ++i)
        {
            auto it = lower_bound(heaters.begin(), heaters.end(), houses[i]);
            int cur_radius = 0;
            if(it == heaters.end())
            {
                max_radius = max(max_radius, houses[i]-heaters.back());
                continue;
            }
            else if(*it == houses[i])
            {
                continue;
            }
            else
            {
                cur_radius = *it - houses[i];
                if(it != heaters.begin())
                {
                    cur_radius = min(cur_radius, houses[i]-(*(it-1)));
                }
            }
            max_radius = max(max_radius, cur_radius);
        }
        return max_radius;
    }

    static bool compareFn(const Interval& x1, const Interval& x2)
    {
        if(x1.start < x2.start)
        {
            return true;
        }
        else if( x1.start > x2.start)
        {
            return false;
        }
        else
        {
            return x1.end < x2.end;
        }
    }

    vector<Interval> merge(vector<Interval>& intervals)
    {
        vector<Interval> res;
        if(intervals.empty()) return res;
        std::sort(intervals.begin(), intervals.end(), sortrel::compareFn);
        res.push_back(*intervals.begin());
        for(int i=1; i < intervals.size(); ++i)
        {
            if(res.back().end >= intervals[i].end)
            {
                //do nothing
            }
            else if(res.back().end >= intervals[i].start)
            {
                res.back().end = intervals[i].end;
            }
            else
            {
                res.push_back(intervals[i]);
            }
        }

        return res;
    }

    vector<Interval> merge1(vector<Interval>& intervals)
    {
        //vector<Interval> res;
        if(intervals.empty()) return intervals;
        std::sort(intervals.begin(), intervals.end(),
                  [](const Interval& in1, const Interval& in2)
                  {if(in1.start < in2.start) return true;
                    else if( in1.start > in2.start)
                        return false;
                    else
                        return in1.end < in2.end;});
        //res.push_back(*intervals.begin());
        for(int i=1; i < intervals.size()-1;)
        {
            /*
            if(res.back().end >= intervals[i].end)
            {
                //do nothing
            }
            else if(res.back().end >= intervals[i].start)
            {
                res.back().end = intervals[i].end;
            }
            else
            {
                res.push_back(intervals[i]);
            }
            */
            if(intervals[i].end >= intervals[i+1].end)
            {
                intervals.erase(intervals.begin()+i+1);
            }
            else if(intervals[i].end > intervals[i+1].start)
            {
                intervals[i].end = intervals[i+1].end;
            }
            else
            {
                ++i;
            }
        }
        return intervals;
    }

    int maximumProduct628(vector<int>& nums)
    {
        int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
        int min1 = INT_MAX, min2 = INT_MAX;
        for(int i : nums)
        {
            if(i < min1)
            {
                min2 = min1;
                min1 = i;
            }
            else if( i < min2)
            {
                min2 = i;
            }

            if(i > max1)
            {
                max3=max2;
                max2=max1;
                max1=i;
            }
            else if( i > max2)
            {
                max3=max2;
                max2=i;
            }
            else if( i > max3)
            {
                max3 = i;
            }

        }

        int res1 = max1*max2*max3;
        int res2 = max1*min1*min2;
        return max(res1, res2);
    }


    int findUnsortedSubarray(vector<int>& nums)
    {
        vector<int> tmp(nums);
        sort(tmp.begin(), tmp.end());
        int start = 0;
        int end   = nums.size()-1;
        while(tmp[start] == nums[start])
        {
            start++;
        }
        while(tmp[end] == nums[end])
        {
            end--;
        }
        if(end <= start)
        {
            return 0;
        }
        return end - start +1;
    }

    vector<int> findClosestElements(vector<int>& arr, int k, int x)
    {

    }


    int subarraryK(vector<int>& nums, int k)
    {
        if(nums.empty()) return 0;
        vector<int> sums(nums.size()+1, 0);
        int res = 0;
        for(int i=1; i<=nums.size(); ++i)
        {
            sums[i] = sums[i-1] + nums[i-1];
        }
        for(int i=0; i<nums.size(); ++i)
        {
            for(int j=i+1; j<=nums.size(); ++j)
            {
                if(sums[j] - sums[i] == k)
                {
                    res++;
                }
            }
        }
        return res;
    }

    int subarraySum(vector<int>& nums, int k)
    {
        vector<int> sum;
        sum.push_back(0);
        unordered_map<int, int> m;
        for(int n: nums)
            sum.push_back(sum.back() + n);
        int ret = 0;
        for(int n : sum){
            if(m.find(n) != m.end())
                ret += m[n];
            m[n + k]++;
        }
        return ret;
    }

    int countRangeSum(vector<int>& nums, int lower, int upper)
    {
        if(nums.empty()) return 0;
        sort(nums.begin(), nums.end());
        auto it_start = lower_bound(nums.begin(), nums.end(), lower);
        auto it_end =   upper_bound(nums.begin(), nums.end(), upper);
        return it_end - it_start;
    }

    vector<pair<int, int>> kSmallestPairs1(vector<int>& nums1, vector<int>& nums2, int k)
    {
        int m = nums1.size();
        int n = nums2.size();

        vector<vector<int>> sum(n, vector<int>(m, 0));
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<m; ++j)
            {
                sum[i][j] = nums1[j] + nums2[i];
            }
        }
        priority_queue<pair<int, pair<int, int>>> pq;
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<m; ++j)
            {
                if(pq.size() >= k)
                {
                    if(pq.top().first > sum[i][j])
                    {
                        pq.pop();
                        pq.push(make_pair(sum[i][j], make_pair(nums1[j], nums2[i])));
                    }
                }
                else
                {
                    pq.push(make_pair(sum[i][j], make_pair(nums1[j], nums2[i])));
                }
            }
        }
        vector<pair<int, int>> res;

        while(!pq.empty())
        {
            res.push_back(pq.top().second);
            pq.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }

    vector<pair<int, int>> kSmallestPairs2(vector<int>& nums1, vector<int>& nums2, int k)
    {
        int m = nums1.size();
        int n = nums2.size();
        priority_queue<pair<int, pair<int, int>>> pq;
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<m; ++j)
            {
                int sum = nums1[j] + nums2[i];
                if(pq.size() >= k)
                {
                    if(pq.top().first > sum)
                    {
                        pq.pop();
                        pq.push(make_pair(sum, make_pair(nums1[j], nums2[i])));
                    }
                }
                else
                {
                    pq.push(make_pair(sum, make_pair(nums1[j], nums2[i])));
                }
            }
        }
        vector<pair<int, int>> res;

        while(!pq.empty())
        {
            res.push_back(pq.top().second);
            pq.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }

    vector<int> bubbleSort(vector<int>& nums)
    {
        if(nums.size() < 2) return nums;
        for(int len = nums.size(); len > 1; len--)
        {
            for(int i=0; i<len-1; ++i)
            {
                if(nums[i] > nums[i+1])
                    swap(nums[i], nums[i+1]);
            }
        }
        return nums;
    }

    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);
    }
    int mergeSort(vector<int>& nums, int left, int right) {
        if (left >= right) return 0;
        int mid = left + (right - left) / 2;
        int res = mergeSort(nums, left, mid) + mergeSort(nums, mid + 1, right);
        for (int i = left, j = mid + 1; i <= mid; ++i) {
            while (j <= right && nums[i] / 2.0 > nums[j]) ++j;
            res += j - (mid + 1);
        }
        sort(nums.begin() + left, nums.begin() + right + 1);
        return res;
    }

    int reversePairs2(vector<int>& nums)
    {

    }

    int findMinArrowShots(vector<pair<int, int>>& points) {
        if(points.empty()) return 0;
        sort(points.begin(), points.end(), [&](pair<int, int> left, pair<int, int> right)
        {
            return left.second < right.second;
        });
        int res = 0;
        for(int i=0; i<points.size(); ++i)
        {
            for(int j=0; j<points.size(); ++j)
            {

            }
        }
        return res;
    }
//[[3,9],[7,12],[3,8],[6,8],[9,10],[2,9],[0,9],[3,9],[0,6],[2,8]]
    int findMinArrowShots2(vector<pair<int, int>>& points) {
        if(points.empty()) return 0;
        sort(points.begin(), points.end(), [&](pair<int, int> left, pair<int, int> right)
        {
            if(left.first == right.first)
            {
                return left.second < right.second;
            }
            return left.first < right.first;
        });
        int res = 1;
        pair<int, int> cur = points[0];
        for(int i=1; i<points.size(); ++i)
        {
            if(cur.second >= points[i].first)
            {
                cur.first = points[i].first;
                if(cur.second > points[i].second)
                {
                    cur.second = points[i].second;
                }
            }
            else
            {
                cur = points[i];
                res++;
            }
        }
        return res;
    }
};

#endif // SORTREL_H
