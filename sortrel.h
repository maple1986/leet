#ifndef SORTREL_H
#define SORTREL_H

#include <vector>
#include <algorithm>
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
        int radius = max(abs(houses.front()-heaters.front()), abs(houses.back() - heaters.back()));
        //int radius = *(houses.begin())-*(heaters.begin());
        for(int i=1; i<heaters.size(); ++i)
        {
            radius = max(radius, (heaters[i]-heaters[i-1])/2);
        }
        return radius;
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
};

#endif // SORTREL_H
