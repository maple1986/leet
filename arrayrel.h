#ifndef ARRAYREL_H
#define ARRAYREL_H

#include <vector>
#include <string>

using namespace std;
class ArrayRel
{
public:
    ArrayRel();
    vector<string> findMissingRanges(vector<int> &nums, int lower, int upper)
    {
        vector<string> res;
        if(nums.empty())
        {
            res.push_back(generateString(lower, upper));
            return res;
        }

        if(long(nums.front())-long(lower) > 0)
        {
            res.push_back(generateString(lower, nums.front()-1));
        }
        for(int i=1; i<nums.size(); ++i)
        {
            if(long(nums[i]) - long(nums[i-1]) > 1)
            {
                res.push_back(generateString(nums[i-1]+1, nums[i]-1));
            }
        }
        if(long(upper) - long(nums.back()) > 0)
        {
            res.push_back(generateString(nums.back()+1, upper));
        }
        return res;
    }

    string generateString(int lower, int upper)
    {
        if(lower == upper)
        {
            return to_string(lower);
        }
        else// if( upper-lower > 1)
        {
            return to_string(lower) + "->" + to_string(upper);
        }
    }
};

#endif // ARRAYREL_H
