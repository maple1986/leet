#ifndef MATHREL_H
#define MATHREL_H

#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;
class MathRel
{
public:
    MathRel();
    static void test();
    int binaryGap(int N)
    {
        int maxGap = 0;
        int last = -1, pos = 0;
        while (N)
        {
            if(N&0x01)
            {
               if(last != -1)
               {
                    maxGap = std::max(maxGap, pos - last);
                    last = pos;
               }
               else
               {
                   last = pos;
               }
            }
            N = N >> 1;
            ++pos;
        }

        return maxGap;
    }

    double maxSubAverange(vector<int>& nums, int k)
    {
        if(k == 0) return 0.0;
        if(nums.size() <= k)
        {
            int sum = std::accumulate(nums.begin(), nums.end(), 0);
            return static_cast<double>(sum)/k;
        }
        int sum_k = std::accumulate(nums.begin(), nums.begin()+k, 0);
        double max_average_k = static_cast<double>(sum_k)/k;
        for(int i=k; i<nums.size(); ++i)
        {
            sum_k += nums[i] - nums[i-k];
            max_average_k = max(max_average_k, static_cast<double>(sum_k)/k);
        }
        return max_average_k;
    }

};

#endif // MATHREL_H
