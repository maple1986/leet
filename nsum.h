#ifndef NSUM_H
#define NSUM_H

#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>

using namespace std;
class NSum
{
public:
    NSum();
    static void test();

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

    vector<int> twoSum22(vector<int>& nums, int target)
    {
        unordered_map<int, int> hash;
        for(int i=0; i<nums.size(); ++i)
        {
            if(hash.count(target-nums[i]))
            {
                return {hash[target-nums[i]]+1, i+1};
            }
            hash[nums[i]] = i;
        }
        return {};
    }

    vector<int> twoSum23(vector<int>& nums, int target)
    {
        if(nums.empty()) return {};
        int l = 0, r = nums.size()-1;
        while(l < r)
        {
            if(nums[l] + nums[r] > target)
            {
                r--;
            }
            else if(nums[l] + nums[r] < target)
            {
                l++;
            }
            else
            {
                return {l+1, r+1};
            }
        }
        return {};
    }

    vector<vector<int>> threeSum1(vector<int>& nums)
    {
        vector<vector<int>> triple;
        if(nums.size() < 3) return {};
        sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size(); ++i)
        {
            int target = -nums[i];

            int l = i+1, r = nums.size()-1;
            while(l < r)
            {
                if(nums[l] + nums[r] > target)
                {
                    r--;
                }
                else if(nums[l] + nums[r] < target)
                {
                    l++;
                }
                else
                {
                    triple.push_back({i, l, r});
                }
            }
        }
        return triple;
    }

    vector<vector<int>> threeSum(vector<int>& nums)
    {
        vector<vector<int>> triple;
        if(nums.size() < 3) return triple;
        sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size(); ++i)
        {
            if(i>=1 && nums[i] == nums[i-1])
            {
                continue;
            }
            int left = i+1, right = nums.size()-1;
            while(left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                if(sum == 0)
                {
                    vector<int> tmp = {nums[i], nums[left], nums[right]};
                    triple.push_back(tmp);
                    while(nums[left++] == nums[left]);
                    while(nums[right--] == nums[right]);
                }
                else if( sum > 0)
                {
                    right--;
                }
                else
                {
                    left++;
                }
            }
        }
        return triple;
    }

    int threeSumMulti1(vector<int>& A, int target)
    {
        if(A.size() < 3) return 0;
        vector<long> counts(101, 0);
        for(int num : A)
        {
            counts[num]++;
        }
        long res = 0;
        for(int i=0; i<counts.size(); ++i)
        {
            if(i*3 == target)
            {
                res += counts[i]*(counts[i]-1)*(counts[i]-2)/6;
            }
            else if(target-i*2>=0 && counts[target-i*2])
            {
                res += counts[i]*(counts[i]-1)*counts[target-i*2]/2;
            }
            int l = i+1, r = counts.size()-1;
            while(l < r)
            {
                if(l + r + i  > target)
                {
                    r--;
                }
                else if(l + r + i < target)
                {
                    l++;
                }
                else
                {
                    res += counts[l]*counts[i]*counts[r];
                    r--;
                    l++;
                }
            }
        }
        return res%int(1e9 + 7);
    }

    int threeSumMulti2(vector<int>& A, int target)
    {
        if(A.size() < 3) return 0;
        map<int, long> counts;
        for(int num : A)
        {
            counts[num]++;
        }
        long res = 0;
        auto it = counts.begin();
        for(; it != counts.end(); ++it)
        {
            if(it->first*3 == target)
            {
                res += it->second*(it->second-1)*(it->second-2)/6;
            }
            else if(target-it->first*2>=0 && counts.count(target-it->first*2))
            {
                res += it->second*(it->second-1)*counts[target-it->first*2]/2;
            }
            //int l = i+1, r = counts.size()-1;
            auto it2 = it; it2++;
            auto it3 = counts.end();it3--;
            while(it2->first < it3->first)
            {
                if(it->first + it2->first + it3->first  > target)
                {
                    it3--;
                }
                else if(it->first + it2->first + it3->first  < target)
                {
                    it2++;
                }
                else
                {
                    res += it->second * it2->second * it3->second;
                    it3--;
                    it2++;
                }
            }
        }
        return res%int(1e9 + 7);
    }


    int threeSumMulti(vector<int>& A, int target) {
        if(A.size() < 3) return 0;
        const int mod = 1e9 + 7;
        sort(A.begin(), A.end());
        unordered_map<int, int> counts;
        for(int num : A)
        {
            counts[num]++;
        }
        int res = 0;
        for(int i=0; i<A.size(); ++i)
        {
            if(i>0&&A[i] == A[i-1]) continue;
            int l = i+1, r=A.size()-1;
            while(l<r)
            {
                if(A[i] + A[l] + A[r] > target)
                {
                    r--;
                }
                else if(A[i] + A[l] + A[r] < target)
                {
                    l++;
                }
                else
                {
                    res = (res+calc(A[i], A[l], A[r], mod, counts))%mod;
                    while(l<A.size() && A[l+1] == A[l])l++;
                    while(r>=0 && A[r-1] == A[r])r--;
                    l++;
                    r--;
                }
            }
        }
        return res;
    }

    long calc(int i, int j, int r, int mod, unordered_map<int, int>& counts)
    {
        if(i == j && j == r)
        {
            int n = counts[i];
            int res = static_cast<long>(n)*(n-1)*(n-2)/6%mod;
            return res;
        }
        else if(i != j && j != r)
        {
            int res = static_cast<long>(counts[i])*counts[j]*counts[r]%mod;
            return res;
        }
        else
        {
            if(i == j)
            {
                long n = counts[i];
                n = n*(n-1)/2;
                return n*counts[r]%mod;
            }
            else if(i == r)
            {
                long n = counts[i];
                n = n*(n-1)/2;
                return n*counts[j]%mod;
            }
            else
            {
                long n = counts[j];
                n = n*(n-1)/2;
                return n*counts[i]%mod;
            }
        }
    }

    int threeSumSmaller(vector<int> &nums, int target) {
        if(nums.size() < 3) return 0;
        sort(nums.begin(), nums.end());
        int res = 0;
        for(int i=0; i<nums.size(); ++i)
        {
            int l = i+1, r = nums.size()-1;
            while(l<r)
            {
                int sum = nums[i] + nums[l] + nums[r];
                if(sum < target)
                {
                    res += r-l;
                    l++;
                }
                else
                {
                    r--;
                }
            }
        }
        return res;
    }

    typedef unordered_map<int, int>::iterator UMI;
    int threeSum2(vector<int>& nums, int target)
    {
        if(nums.size() < 3) return 0;
        const int mod = 1e9 + 7;
        int res = 0;
        unordered_map<int, int> counts;
        for(int num : nums)
        {
            counts[num]++;
        }
        auto it1 = counts.begin();
        for(; it1 != counts.end(); ++it1)
        {
            auto it2 = it1;
            if(it1->second < 2)
            {
                it2++;
            }
            for(; it2 != counts.end(); ++it2)
            {
                int rest = target - it1->first - it2->first;
                auto it3 = counts.find(rest);
                if(it3 == counts.end())
                {
                    continue;
                }
                if(!valid(it1, it2, it3))
                {
                    continue;
                }
                res = (res+calc(it1, it2, it3))%mod;
            }
        }
        return res;
    }

    bool valid(UMI it1, UMI it2, UMI it3)
    {
        if(it1 != it2 && it1 != it3 && it2 != it3)
        {
            return true;
        }
        if(it1 == it2 && it1 == it3)
        {
            return it1->second >=3;
        }
        else
        {
            if(it1 == it2)
            {
                return it1->second>=2;
            }
            else
            {
                return it3->second>=2;
            }
        }
    }

    long calc(UMI it1, UMI it2, UMI it3)
    {
        if(it1 != it2 && it1 != it3 && it2 != it3)
        {
            return static_cast<long>(it1->second) * it2->second * it3->second;
        }
        if(it1 == it2 && it1 == it3)
        {
            long n = it1->second;

            return static_cast<long>(n)*(n-1)*(n-2)/6;
        }
        else
        {
            if(it1 == it2)
            {
                long n = it1->second;
                n = n*(n-1)/2;
                long m = it3->second;
                return m*n;
            }
            else if(it1 == it3)
            {
                long n = it1->second;
                n = n*(n-1)/2;
                long m = it2->second;
                return m*n;
            }
            else
            {
                long n = it2->second;
                n = n*(n-1)/2;
                long m = it1->second;
                return m*n;
            }
        }
    }

    vector<vector<int>> fourSum(vector<int>& nums, int target)
    {
        vector<vector<int>> quadruplets;
        if(nums.size() < 4) return quadruplets;
        sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size(); ++i)
        {
            if(i>0 && nums[i] == nums[i-1])
            {
                continue;
            }
            for(int j=i+1; j<nums.size(); ++j)
            {
                if(j>i+1 && nums[j] == nums[j-1])
                {
                    continue;
                }
                int left = j+1, right = nums.size()-1;
                while(left < right)
                {
                    int sum = nums[i] + nums[j] + nums[left] + nums[right];
                    if(sum == target)
                    {
                        vector<int> tmp = {nums[i], nums[j], nums[left], nums[right]};
                        quadruplets.push_back(tmp);
                        while(nums[left++] == nums[left]);
                        while(nums[right--] == nums[right]);
                    }
                    else if( sum > target)
                    {
                        right--;
                    }
                    else
                    {
                        left++;
                    }
                }
            }
        }
        return quadruplets;
    }

    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D)
    {
        unordered_multiset<int> sA(A.begin(), A.end());
        unordered_multiset<int> sB(B.begin(), B.end());
        unordered_multiset<int> sC(C.begin(), C.end());
        unordered_multiset<int> sD(D.begin(), D.end());
        int res;
        auto ita = sA.begin();
        while(ita!= sA.end())
        {
            int cA = sA.count(*ita);
            auto itb = sB.begin();
            while(itb != sB.end())
            {
                int cB = sB.count(*itb);
                auto itc = sC.begin();
                while(itc != sC.end())
                {
                    int cC = sC.count(*itc);
                    int target = -*ita - *itb -*itc;
                    auto itd = sD.find(target);
                    if(itd != sD.end())
                    {
                        res += cA * cB * cC * sD.count(*itd);
                    }
                }
            }
        }
        return res;
    }

    int fourSumCount2(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D)
    {
        unordered_map<int, int> abSum;
        for(auto i=A.begin(); i != A.end(); ++i)
        {
            for(auto j=B.begin(); j != B.end(); ++j)
            {
                abSum[(*i)+(*j)]++;
            }
        }

        int count = 0;
        for(auto c : C) {
            for(auto d : D) {
                auto it = abSum.find(c - d);
                if(it != abSum.end()) {
                    count += it->second;
                }
            }
        }
        return count;
    }

    int threeSumSmaller2(vector<int> &nums, int target)
    {
        // Write your code here
        if(nums.size() < 3) return 0;
        multimap<int, int> dict;
        int res = 0;
        for(int i=0; i<nums.size(); ++i)
        {
            //dict[nums[i]].push_back(i);
        }
        for(int i=0; i<nums.size()-2; ++i)
        {
            for(int j=i+1; j<nums.size()-1; ++j)
            {
                int newTarget = target - nums[i] - nums[j];
                if(dict.lower_bound(newTarget) != dict.begin())
                {

                }
            }
        }
        return res;
    }

    int threeSumClosest(vector<int>& nums, int target) {
        if(nums.size() < 3) return {};
        int res = nums[0] + nums[1] + nums[2];
        sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size(); ++i)
        {
            while(i>0&&i<nums.size()&&nums[i-1] == nums[i]) i++;
            int l = i+1, r = nums.size()-1;
            while(l<r)
            {
                int sum = nums[i] + nums[l] + nums[r];
                if(sum > target)
                {
                    res = (sum-target) > abs(res-target)?res:sum;
                    while(r>0&&nums[r--] == nums[r]);
                }
                else if(sum < target)
                {
                    res = (target-sum) > abs(res-target)?res:sum;
                    while(l<nums.size()-1&&nums[l++] == nums[l]);
                }
                else
                {
                    return sum;
                }
            }
        }
        return res;
    }

};

#endif // NSUM_H
