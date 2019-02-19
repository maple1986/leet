#ifndef ARRAY1_H
#define ARRAY1_H

#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <algorithm>

using namespace std;

class array1
{
public:
    array1();
    static void test();
    /*
     * nums = [0, 1, 3, 50, 75], lower = 0 and upper = 99
    Output:
    ["2", "4->49", "51->74", "76->99"]
    */
    vector<string> findMissingRanges1(vector<int> &nums, int lower, int upper)
    {
        if(nums.size() == static_cast<long>(upper)-lower+1)
        {
            return {};
        }

    }

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

    void nextPermutation(vector<int>& nums)
    {
        if(nums.size() <= 1) return;
        int maxNum = 0;
        int swapLeft = nums.size()-1;
        vector<int> lastNum(10, -1);
        for(int i=nums.size()-1; i>=0; --i, --swapLeft)
        {
            maxNum = max(maxNum, nums[i]);
            if(lastNum[nums[i]] == -1)
            {
                lastNum[nums[i]] = i;
            }
            if(maxNum > nums[i])
            {
                int swapRight = findSwapRight(nums[i], lastNum);
                swap(nums[swapLeft], nums[swapRight]);
                return;
            }
        }
        sort(nums.begin(), nums.end());
        return;
    }

    void nextPermutation1(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) return;
        int i = n-1;
        int maxRight = -1;
        for(; i>=0; --i)
        {
            maxRight = max(maxRight, nums[i]);
            if(maxRight > nums[i])
            {
                break;
            }
        }
        if(i < 0)
        {
            reverse(nums.begin(), nums.end());
            return;
        }
        int j=n-1;
        for(; j>i; --j)
        {
            if(nums[j]>nums[i])
            {
                break;
            }
        }
        swap(nums[i], nums[j]);
        reverse(nums.begin()+i+1, nums.end());
        return;
    }

    int findSwapRight(int num, vector<int>& lastNum)
    {
        if(num == 9)
        {
            return -1;
        }
        for(int i=num+1; i<lastNum.size(); ++i)
        {
            if(lastNum[i] != -1)
            {
                return lastNum[i];
            }
        }
        return -1;
    }

    /*
[4,1,2]
[1,3,4,2]
    */
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums)
    {
        unordered_map<int, int> indexes;
        for(int i=0; i<nums.size(); ++i)
        {
            indexes[nums[i]] = i;
        }
        vector<int> res(findNums.size(), -1);
        for(int i=0; i<findNums.size(); ++i)
        {
            int pos = indexes[findNums[i]];
            for(int j=pos+1; j<nums.size(); ++j)
            {
                if(nums[j] > findNums[i])
                {
                    res[i] = nums[j];
                    break;
                }
            }
        }
        return res;
    }

    vector<int> nextGreaterElement_st(vector<int>& findNums, vector<int>& nums)
    {
        if(findNums.empty()) return {};
        vector<int> res(findNums.size(), -1);
        unordered_map<int, int> indexes;
        stack<int> st;
        for(int num : nums)
        {
            while(!st.empty() && st.top() < num)
            {
                indexes[st.top()] = num;
                st.pop();
            }
            st.push(num);
        }
        for(int i=0; i<findNums.size(); ++i)
        {
            if(indexes.count(findNums[i]))
            {
               res[i] = indexes[findNums[i]];
            }
        }
        return res;
    }

    vector<int> nextGreaterElement2(vector<int>& nums)
    {
        if(nums.empty()) return {};
        vector<int> res(nums.size(), -1);
        //unordered_map<int, int> indexes;
        stack<pair<int,int>> st;
        for(int i=0; i<2*nums.size(); ++i)
        {
            int index = i%nums.size();
            while(!st.empty() && st.top().first < nums[index])
            {
                res[st.top().second] = nums[index];
                st.pop();
            }
            st.push(make_pair(nums[index], index));
        }

        return res;
    }

    int nextGreaterElement(int n)
    {
        string str = to_string(n);
        if(str.size() <= 1) return -1;
        vector<int> back(10, -1);
        for(int i=str.size()-1; i>=0; --i)
        {
            //maxNum = max(maxNum, nums[i]);
            if(back[str[i]-'0'] == -1)
            {
                back[str[i]-'0'] = i;
            }
            if(i != str.size()-1 && str[i] == str[i+1])
                continue;
            int right = findGreater(back, str[i]-'0');

            if(right != -1)
            {
                swap(str[i], str[right]);
                sort(str.begin()+i+1, str.end());
                long long res = stoll(str);
                return res > INT_MAX? -1 : res;
            }
        }
        return -1;
    }

    int findGreater(vector<int>& back, int num)
    {
        if(num == 9)
        {
            return -1;
        }
        for(int i=num+1; i<back.size(); ++i)
        {
            if(back[i] != -1)
            {
                return back[i];
            }
        }
        return -1;
    }

    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k)
    {
        int n = nums.size();
        if(n < 3*k) return {};
        if(n == 3*k) return {0, k, 2*k};
        vector<int> prefixSum(n+1, 0);
        for(int i=0; i<n; ++i)
        {
            prefixSum[i+1] = prefixSum[i] + nums[i];
        }
        vector<int> kSum(n-k, 0);
        for(int i=0; i<n-k+1; ++i)
        {
            int j=i+k;
            kSum[i] = prefixSum[j]-prefixSum[i];
        }
        vector<int> left(n-2*k, 0);
        left[0] = kSum[0];
        for(int i=1; i<n-2*k; ++i)
        {
            left[i] = max(left[i-1], kSum[i]);
        }

        vector<int> right(n, 0);
        right[2*k] = kSum[2*k];
        for(int i=1; i<n-2*k; ++i)
        {
            right[i+2*k] = max(right[i+2*k-1], kSum[2*k+1]);
        }
    }
    //[2,3,3,2,4]
    bool checkPossibility(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) return true;
        int counter = 0;
        for(int i=0; i<n-1; ++i)
        {
            if(nums[i] > nums[i+1])
            {
                if(counter++ >= 1) return false;
                if(i == 0 || nums[i-1] <= nums[i+1])
                    nums[i] = nums[i+1];
                else if(nums[i-1] > nums[i+1])
                    nums[i+1] = nums[i];
            }
        }
        return true;
    }

    vector<int> getModifiedArray(int length, vector<vector<int>> &updates) {
        // Write your code here
        if(updates.empty()) return vector<int>(length, 0);
        vector<int> delta(length+1, 0);
        for(const auto& up: updates)
        {
            delta[up[0]] += up[2];
            delta[up[1]+1] -= up[2];
        }
        int inc = 0;
        vector<int> res(length, 0);
        for(int i=0; i<length; ++i)
        {
            inc += delta[i];
            res[i] = inc;
        }
        return res;
    }

    void wiggleSort2(vector<int> &nums) {
        // write your code here
        if(nums.empty()) return;
        sort(nums.begin(), nums.end());
        vector<int> res;
        int i = 0, j = (nums.size()+1)/2, k = j;
        while(j<nums.size())
        {
            res.push_back(nums[i++]);
            res.push_back(nums[j++]);
        }
        if(i < k) res.push_back(nums[i++]);
        nums.swap(res);
        return;
    }

    vector<int> dailyTemperatures(vector<int>& T) {
        if(T.size()<1) return {0};
        int n = T.size();
        vector<int> res(n, 0);
        stack<int> MonoDecrease;
        MonoDecrease.push(n-1);
        for(int i=T.size()-2; i>=0; --i)
        {
            while(!MonoDecrease.empty() && T[i] > T[MonoDecrease.top()])
            {
                MonoDecrease.pop();
            }
            if(MonoDecrease.empty())
                res[i] = 0;
            else
                res[i] = MonoDecrease.top()-i;
            MonoDecrease.push(i);
        }
        return res;
    }

    //{0,1,2,4,5,7}
    vector<string> summaryRanges(vector<int>& nums)
    {
        if(nums.empty()) return {};
        vector<string> res;
        for(int i=0; i<nums.size();)
        {
            int start = i, end = i;
            while(end<nums.size()-1&&nums[end+1] == nums[end]+1)
            {
                end++;
            }

            if(start == end)
                res.push_back(to_string(nums[start]));
            else
                res.push_back(to_string(nums[start])+"->"+to_string(nums[end]));
            i = end+1;
        }
        return res;
    }

    vector<string> summaryRanges(vector<int>& nums)
    {
        if(nums.empty()) return {};
        int i = 0, n = nums.size();
        vector<string> res;
        while(i<n)
        {
            int j = 1;
            while(i+j<n&&nums[i+j]==nums[i+j-1]+1) j++;
            if(j==1)
                res.push_back(to_string(nums[i]));
            else
                res.push_back(to_string(nums[i])+"->"+to_string(nums[i+j]));
            i+=j;
        }
        return res;
    }
    //[0, 1, 3, 50, 75], return [“2”, “4->49”, “51->74”, “76->99”]
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<int> res;
        if(nums.empty())
        {
            if(lower==upper)
                res.push_back(to_string(lower));
            else
                res.push_back(to_string(lower)+"->"+to_string(upper));
        }
        int l = lower, n = nums.size();


        for(int i=0; i<n; ++i)
        {
            if(nums[i] != l+1)
            {
                if(l+2 == nums[i])
                    res.push_back(to_string(l));
                else
                    res.push_back(to_string(nums[i])+"->"+to_string(nums[i+j]));
            }
            else
            {
                start = nums[i];
            }
            i++;
        }
    }
};

#endif // ARRAY1_H
