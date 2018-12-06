#ifndef DIVIDEANDCONQUER_H
#define DIVIDEANDCONQUER_H

#include <vector>
#include <stdio.h>
#include <set>
#include <string>

using namespace std;
class DivideAndConquer
{
public:
    DivideAndConquer();
    static void test();
    int maxSubSumRec(vector<int>& nums, int left, int right){

        if(left >= right){
            return nums[left];
        }

        int i,center;
        center = (left + right)/2;
        int lmax = maxSubSumRec(nums, left, center - 1);
        int rmax = maxSubSumRec(nums, center +1, right);
        int mmax = nums[center], t = mmax;

        for(i = center - 1; i >= left; --i){
            t += nums[i];
            mmax = max(mmax, t);
        }

        t = mmax;
        for(i = center + 1; i <=right; ++i){
            t += nums[i];
            mmax = max(mmax, t);
        }

        return max(mmax, max(lmax, rmax));
    }


    int maxSubArray(vector<int>& nums) {

        int length = int(nums.size()-1);
        return maxSubSumRec(nums, 0, length);
    }

    int mergesort(vector<int>& nums, int left, int right)
    {
        printf("merge sort %d to %d\n", left, right);
        if(left >= right)
        {
            return left;
        }
        int mid = (left + right)/2;
        mergesort(nums, left, mid);
        mergesort(nums, mid+1, right);
        merge(nums, left, mid, right);
        return 0;
    }

    void merge(vector<int>& nums, int left, int mid, int right)
    {
        if(right - left < 2)
        {
            if(nums[right] < nums[left])
            {
                int tmp     = nums[left];
                nums[left] = nums[right];
                nums[right]  = tmp;
            }
            return;
        }

        vector<int> vleft(nums.begin()+left, nums.begin()+mid+1);
        vector<int> vright(nums.begin()+mid+1, nums.begin()+right+1);
        int i = 0, j =0, k = left;

        while (i < vleft.size() && j <vright.size())
        {
            if(vleft[i] < vright[j])
            {
                nums[k++] = vleft[i++];
            }
            else
            {
                nums[k++] = vright[j++];
            }
        }
        if(i < vleft.size())
        {
            while(k <= right)
            {
                nums[k++] = vleft[i++];
            }
        }
        else if(j <vright.size())
        {
            while(k <= right)
            {
                nums[k++] = vright[j++];
            }
        }
    }

    int majorityElement(vector<int>& nums)
    {
//        multiset<int> groupednums(nums.begin(), nums.end());
//        auto it = groupednums.begin();
//        while(it != groupednums.end())
//        {
//            if(groupednums.count(*it) > nums.size()/2) return *it;
//            ++it;
//        }
//        return 0;
        mergesort(nums, 0, nums.size()-1);
        return nums[nums.size()/2];
        return 0;
    }

    int majorityElement2(vector<int>& nums) {
        int target = nums.size() / 2;
        int count = 1;
        int res = nums[0];
        for(int i = 1;i < nums.size();i++){
            if(nums[i] != res){
                if(--count < 0){
                    res = nums[i];
                    count = 1;
                }
            }
            else{
                count++;
            }
        }
        return res;
    }

    int maxCoins(vector<int>& nums)
    {
        return 0;
    }

    int numSquares(int n)
    {

    }

    string longestCommonPrefix(vector<string>& strs)
    {
        int n = strs.size();
        if(n == 0) return "";
        if(n == 1) return strs.front();
        return longestCommonPrefixHelper(strs, 0, strs.size()-1);
    }

    string longestCommonPrefixHelper(vector<string>& strs, int begin, int end)
    {
        if(begin > end) return "";
        if(end == begin) return strs[begin];
        int mid = begin + (end-begin)/2;
        string left =  longestCommonPrefixHelper(strs, begin, mid);
        string right = longestCommonPrefixHelper(strs, mid+1, end);
        string common_pre = merge(left, right);
        return common_pre;
    }

    string merge(string& pre1, string& pre2)
    {
        if(pre1.empty() || pre2.empty()) return "";
        int index = 0;
        while(index < min(pre1.length(), pre2.length()))
        {
            if(pre1[index] != pre2[index])
            {
                break;
            }
            index++;
        }
        return pre1.substr(0, index);
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        int m = nums1.size();
        int n = nums2.size();
        //bool odd = (m+n)%2;
        int total = m+n;
        if(0 == m)
        {
            if(total%2)
            {
                return nums2[total/2];
            }
            else {
                int median1 = nums2[total/2];
                int median2 = nums2[total/2-1];
                return static_cast<double>(median1)/static_cast<double>(median2);
            }
        }
        if(0 == n)
        {
            if(total%2)
            {
                return nums1[total/2];
            }
            else {
                int median1 = nums1[total/2];
                int median2 = nums1[total/2-1];
                return static_cast<double>(median1)/static_cast<double>(median2);
            }
        }

        return 0.f;
    }
};

#endif // DIVIDEANDCONQUER_H
