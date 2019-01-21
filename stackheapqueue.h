#ifndef STACKHEAPQUEUE_H
#define STACKHEAPQUEUE_H

#include <vector>
#include <deque>
using namespace std;
class StackHeapQueue
{
public:
    StackHeapQueue();
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        deque<int> maxs;
        for(int i=0; i<nums.size(); ++i)
        {
            if(maxs.empty() || nums[i] <= maxs.back())
            {
                maxs.push_back(nums[i]);
            }
            else
            {
                while(!maxs.empty() && maxs.back()< nums[i])
                {
                    maxs.pop_back();
                }
                maxs.push_back(nums[i]);
            }
            if(i >= k)
            {
                if(maxs.front() == nums[i-k])
                    maxs.pop_front();
                res.push_back(maxs.front());
            }
        }
        return res;
    }
};

#endif // STACKHEAPQUEUE_H
