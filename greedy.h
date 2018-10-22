#ifndef GREEDY_H
#define GREEDY_H

#include <vector>
#include <map>
using namespace std;
class greedy
{
public:
    greedy();
    static void test();
    int rob(vector<int>& nums)
    {
        int size = nums.size();
        if(size != 0)
            return maxRob(size-1, nums);
        return 0;
    }

    int maxRob(int n, vector<int>& nums)
    {
        if(n<0)
        {
            return 0;
        }
        map<int, int>::iterator it = _values.find(n);
        if(it != _values.end())
        {
            return it->second;
        }
        int res = max(maxRob(n-2, nums)+ nums[n], maxRob(n-1, nums));
        _values.insert(make_pair(n, res));
        return res;
    }
private:
    std::map<int, int> _values;
};

#endif // GREEDY_H
