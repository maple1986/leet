#ifndef NSUM_H
#define NSUM_H

#include <vector>
#include <map>
#include <unordered_map>
using namespace std;
class NSum
{
public:
    NSum();
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        unordered_map<int, int> hash;
        for(int i=0; i<nums.size(); ++i)
        {
            auto it = hash.find(target-nums[i]);
            if(it != hash.end())
            {
                res.push_back(i);
                res.push_back(it->second);
                break;
            }
            hash[nums[i]] = i;
        }
        return res;
    }

};

#endif // NSUM_H
