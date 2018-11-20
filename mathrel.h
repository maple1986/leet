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

    int NthDigit(int n)
    {
        int digit = 1;
        int nums  = 9;
        int past_nums = nums*digit;
        while(n - past_nums > 0)
        {
            nums *= 10;
            digit++;
            past_nums += nums*digit;
        }
        return 0;
    }

    bool studentAttandance(string s)
    {
        int absentCount = 0;
        int continuesLaterCount = 0;
        for(char c : s)
        {
            switch (c) {
            case 'P':
                continuesLaterCount = 0;
                continue;
            case 'A':
                absentCount++;
                continuesLaterCount = 0;
                break;
            case 'L':
                if(++continuesLaterCount > 2)
                    return false;
                break;
            default:
                break;
            }
        }
        return absentCount<2;
    }

    int studentAttandance2(int n)
    {
        if(n == 0) return 0;
        int res;

        dfs(n, 0, 0, 0, res);

        return res % _mod;
    }
    int _mod = pow(10, 9)+7;
    vector<char> _status = {'A', 'P', 'L'};
    void dfs(int n, int cur, int absent_count, int clater_count, int& res)
    {
        if(n == cur)
        {
            res = res%_mod+1;
            return;
        }
        for(int i=0; i<_status.size(); ++i)
        {
            switch (_status[i]) {
            case 'P':
                clater_count = 0;
                dfs(n, cur+1, absent_count, 0, res);
                break;
            case 'A':
                if(++absent_count > 1) return;
                dfs(n, cur+1, absent_count, 0, res);
                break;
            case 'L':
                if(++clater_count > 2) return;
                dfs(n, cur+1, absent_count, clater_count, res);
                break;
            }
        }
        return;
    }
};

#endif // MATHREL_H
