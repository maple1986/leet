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

    vector<int> twoSum2(vector<int>& nums, int target) {
        vector<int> res;
        multiset<int> hashset;
        for(int i=0; i<nums.size(); ++i)
        {
            hashset.insert(nums[i]);
            //hashset[nums[i]] = i;
        }
        return res;
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
};

#endif // NSUM_H
