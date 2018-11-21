#ifndef SORTREL_H
#define SORTREL_H

#include <vector>
#include <algorithm>
#include <unordered_map>
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

    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
    {
        if(intervals.empty())
        {
            intervals.push_back(newInterval);
            return intervals;
        }
        auto it1 = std::lower_bound(intervals.begin(), intervals.end(), newInterval, sortrel::compareFn);
        auto it2 = std::upper_bound(intervals.begin(), intervals.end(), newInterval, sortrel::compareFn);
        if(it1 == it2)
        {
            if(newInterval.end >= it1->start)
            {
                it1->start = newInterval.start;
            }
            else
            {
                intervals.insert(it1, newInterval);
            }
        }
        else
        {
            if(newInterval.end < it2->start)
            {
                it1->end = max(it1->end, newInterval.end);
            }
            else
            {
                while(it2 != intervals.end())
                {
                    if(newInterval.end > it2->start)
                    {
                        ++it2;
                        intervals.erase(it2-1);
                    }
                    it2->end = max(newInterval.end, it2->end);
                    return intervals;
                }
                it2--;
                it2->end = newInterval.end;
            }
        }

        return intervals;
    }

    vector<Interval> insert1(vector<Interval>& intervals, Interval newInterval)
    {
        pair<vector<Interval>::iterator, vector<Interval>::iterator> range = \
                equal_range(intervals.begin(), intervals.end(), newInterval, \
                            [](const Interval& a, const Interval& b){return a.end < b.start;});
        auto it_start = range.first;
        auto it_end   = range.second;
        if(it_start == it_end)
        {
            intervals.insert(it_start, newInterval);
        }
        else
        {
            //while(it_)
        }
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


};

#endif // SORTREL_H
