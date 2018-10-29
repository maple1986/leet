#ifndef DIVIDEANDCONQUER_H
#define DIVIDEANDCONQUER_H

#include <vector>
#include <stdio.h>
#include <set>

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

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {

    }

};

#endif // DIVIDEANDCONQUER_H
