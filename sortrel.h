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
};

#endif // SORTREL_H
