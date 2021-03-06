#ifndef MATHREL_H
#define MATHREL_H

#include <math.h>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <set>

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
        int res=0;

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
                dfs(n, cur+1, absent_count, 0, res);
                break;
            case 'A':
                if(++absent_count > 1)
                {
                    --absent_count;
                    continue;
                }
                dfs(n, cur+1, absent_count, 0, res);
                --absent_count;
                break;
            case 'L':
                if(++clater_count > 2)
                {
                    --clater_count;
                    continue;
                }
                dfs(n, cur+1, absent_count, clater_count, res);
                --clater_count;
                break;
            }
        }
        return;
    }


    int maximumSwap(int num) {
        // Write your code here
        string res = to_string(num);
        string back = res;
        for(int b = back.size()-2; b >= 0; --b)
        {
            back[b] = max(back[b+1], back[b]);
        }
        for(int f=0; f<res.size(); ++f)
        {
            if(res[f] < back[f])
            {
                int b = back.size();
                while(back[--b] != back[f]);
                swap(res[f], res[b]);
                break;
            }
        }
        return stoi(res);
    }

    bool isRectangleCover(vector<vector<int>>& rectangles) {
        if(rectangles.empty()) return false;
        int xmin = INT_MAX, ymin= INT_MAX, xmax = 0, ymax = 0;
        for(const auto& e : rectangles)
        {
            xmin = min(xmin, e[0]);
            ymin = min(ymin, e[1]);
            xmax = max(xmax, e[2]);
            ymax = max(ymax, e[3]);
        }
        bool findMin = false, findMax = false;
        for(const auto& e : rectangles)
        {
            if(e[0] == xmin && e[1] == ymin) findMin = true;
            if(e[2] == xmax && e[3] == ymax) findMax = true;
        }
        if(!(findMin&&findMax)) return false;
        int size = (ymax-ymin)*(xmax-xmin);
        if(!size) return false;
        for(const auto& e : rectangles)
        {
            size -= (e[3]-e[1])*(e[2]-e[0]);
        }
        return size == 0;
    }


    bool isReflected(vector<vector<int>> &points) {
        // Write your code here
        if(points.empty()) return true;
        unordered_map<int, unordered_set<int>> yIndices;
        int xMin = INT_MAX;
        int xMax = INT_MIN;
        for(const auto& pt:points)
        {
            yIndices[pt[1]].insert(pt[0]);
            xMin = min(pt[0], xMin);
            xMax = max(pt[0], xMax);
        }
        int x0 = xMin + xMax;
        auto it = yIndices.begin();
        for(; it != yIndices.end(); ++it)
        {
            auto& xs = it->second;
            auto xindex = xs.begin();
            for(; xindex != xs.end(); ++xindex)
            {
                int x = *xindex;
                if(!xs.count(x0-x))
                {
                    return false;
                }
            }
        }
        return true;
    }

    int countNumbersWithUniqueDigits(int n)
    {
        if(n==0) return 1;
        if(n==1) return 10;
        if(n>10) n = 10;
        //int res = 10;
        vector<int> dp(n+1, 0);
        dp[1] = 10, dp[2] = 81;
        for(int i=3; i<=n; ++i)
        {
            dp[i] = dp[i-1]*(10-i+1);
        }
        return accumulate(dp.begin(), dp.end(), 0);
    }

    int countNumbersWithUniqueDigits2(int n) {
        if(n == 0) return 1;
        //if(n == 1) return 10;
        int used = 0;
        int res = 0;
        doCountNumbers(1, n, used, res);
        return res+1;
    }

    void doCountNumbers(int cur, int n, int used, int& res)
    {
        if(cur == n+1)
        {
            return;
        }
        for(int i=0; i<=9; ++i)
        {
            if(used&1<<i) continue;
            if(cur==1 && i==0) continue;
            used |= 1<<i;
            res++;
            doCountNumbers(cur+1, n, used, res);
            used &= ~(1<<i);
        }
        return;
    }

    long long countNumbers(long long n) 
    {
        if(n <= 10) return 0;
        if(n <= 99) return 9;
        string s = to_string(n);
        int len = s.length();
        if(len>10) len=10;
        vector<int> dp(len+1, 0);
        dp[1] = 10, dp[2] = 81;
        for(int i=3; i<=n; ++i)
        {
            dp[i] = dp[i-1]*(10-i+1);
        }
        int unique = accumulate(dp.begin(), dp.end(), 0);
        if(len>10) return 1e10-unique;
        else
        {
            int all = pow(10, len-1);
        }
        return 0;
    }
};

#endif // MATHREL_H
