#ifndef INTERVALREL_H
#define INTERVALREL_H

#include <vector>
#include <algorithm>

using namespace std;
class IntervalRel
{
public:
    struct Interval {
        int start;
        int end;
        Interval() : start(0), end(0) {}
        Interval(int s, int e) : start(s), end(e) {}
    };

    class RangeModule {
    public:
        RangeModule() {

        }

        void addRange(int left, int right) {
            if(_ranges.empty())
            {
                _ranges.emplace_back(left, right);
                return;
            }
            vector<pair<int, int>> res;
            int index = 0;
            while(index < _ranges.size() && _ranges[index].second < left)
            {
                res.push_back(_ranges[index++]);
            }
            while(index < _ranges.size() && _ranges[index].first <= right)
            {
                left  = min(left, _ranges[index].first);
                right = max(right, _ranges[index].second);
                index++;
            }
            res.emplace_back(left, right);
            while(index < _ranges.size())
            {
                res.push_back(_ranges[index++]);
            }
            _ranges.swap(res);
            return;
        }

        bool queryRange(int left, int right) {

            if(_ranges.empty()) return false;
            auto it = lower_bound(_ranges.begin(), _ranges.end(), make_pair(left, right),\
                                  [](const pair<int,int>& a, const pair<int,int>& b){return a.first < b.first;});
            if(it!=_ranges.end() && it->first == left)
            {
                return it->second >= right;
            }
            if(it == _ranges.begin())
            {
                return false;
            }
            return (--it)->second >= right;
            /*
            int l = 0, r = _ranges.size()-1;
            while(l <= r)
            {
                int mid = l + (r-l)/2;
                if(_ranges[mid].first < left)
                {
                    l = mid+1;
                }
                else if(_ranges[mid].first > left)
                {
                    r = mid-1;
                }
                else
                {
                    r = mid;
                    break;
                }
            }
            if(_ranges[r].first > left) return false;
            return _ranges[r].second > right;
            */
        }

        void removeRange(int left, int right) {
            if(_ranges.empty())
            {
                return;
            }
            vector<pair<int, int>> res;
            int index = 0;
            while(index < _ranges.size() && _ranges[index].second < left)
            {
                res.push_back(_ranges[index++]);
            }
            while(index < _ranges.size() && _ranges[index].first < right)
            {
                //left  = max(left, _ranges[index].first);
                //right = min(right, _ranges[index].second);
                if(left > _ranges[index].first)
                    res.emplace_back(_ranges[index].first, left);
                if(right < _ranges[index].second)
                    res.emplace_back(right, _ranges[index].second);
                index++;
            }
            //if(left < right)
            //    res.emplace_back(left, right);
            while(index < _ranges.size())
            {
                res.push_back(_ranges[index++]);
            }
            _ranges.swap(res);
            return;
        }

        vector<pair<int, int>> _ranges;
    };

    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
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
        return intervals;
    }

    vector<Interval> insert1(vector<Interval>& intervals, Interval newInterval)
    {
        if(intervals.empty())
        {
            intervals.push_back(newInterval);
            return intervals;
        }

        int l = 0, r = intervals.size()-1;
        int xstart = -1;
        while(l <= r)
        {
            int mid = l + (r-l)/2;
            if(intervals[mid].end < newInterval.start)
            {
                l = mid+1;
            }
            else if(intervals[mid].end > newInterval.start)
            {
                r = mid-1;
            }
        }
        l = xstart, r = intervals.size()-1;
        while(l <= r)
        {
            int mid = l + (r-l)/2;
            if(intervals[mid].end < newInterval.start)
            {

            }
            else
            {

            }
        }
        int xend = l;
        if(xstart != xend)
        {
            auto it = intervals.begin();
            intervals.erase(it+xstart, it+xend+1);
        }
        else
        {
            if(xstart == intervals.size()-1)
            {

            }
        }
        return intervals;
    }

    vector<Interval> insert2(vector<Interval>& intervals, Interval newInterval)
    {
        if(intervals.empty())
        {
            intervals.push_back(newInterval);
            return intervals;
        }
        int xstart = -1, xend = -1, newstart = -1;
        for(int i=0; i<intervals.size(); ++i)
        {
            if(max(newInterval.start, intervals[i].start) <= min(newInterval.end, intervals[i].end))
            {
                xend = i;
                if(xstart == -1) xstart = i;
            }
            if(newInterval.start < intervals[i].start && newstart == -1)
            {
                newstart = i;
            }
        }
        if(xstart == -1)
        {
            if(newstart == -1)
            {
                intervals.emplace_back(newInterval);
            }
            else
            {
                intervals.insert(intervals.begin()+newstart, newInterval);
            }
        }
        else
        {
            Interval xIn1 = intervals[xstart], xIn2 = intervals[xend];
            intervals.erase(intervals.begin()+xstart, intervals.begin()+xend+1);
            intervals.insert(intervals.begin()+xstart, Interval(min(xIn1.start, newInterval.start), max(xIn2.end, newInterval.end)));
        }
        return intervals;
    }

    vector<Interval> insert3(vector<Interval>& intervals, Interval newInterval)
    {
        if(intervals.empty())
        {
            intervals.push_back(newInterval);
            return intervals;
        }
        vector<Interval> res;
        int index = 0;
        while(index < intervals.size() && intervals[index].end < newInterval.start)
        {
            res.push_back(intervals[index++]);
        }
        while(index < intervals.size() && intervals[index].start <= newInterval.end)
        {
            newInterval.start = min(newInterval.start, intervals[index].start);
            newInterval.end   = max(newInterval.end, intervals[index].end);
            index++;
        }
        res.push_back(newInterval);
        while(index < intervals.size())
        {
            res.push_back(intervals[index++]);
        }
        return res;
    }

    vector<Interval> insert4(vector<Interval> &intervals, Interval newInterval) {
        if(intervals.empty())
        {
            return {newInterval};
        }
        auto func = [](const Interval& l, const Interval& r)
        {return l.start < r.start;};
        //auto it  = lower_bound(intervals.begin(), intervals.end(), fuc);
        //auto it2 = upper_bound(intervals.begin(), intervals.end(), fuc);
    }

    static void test();
};

#endif // INTERVALREL_H
