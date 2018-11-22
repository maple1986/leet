#ifndef BINARYSEARCHREL_H
#define BINARYSEARCHREL_H

#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
class binarySearchRel
{
public:
    binarySearchRel();
    static void test();

    int calcNth(vector<int>& arr, int num)
    {
        int l = 0;
        int r = arr.size();
        while(l < r)
        {
            int m = l + (r-l)/2;
            if(arr[m] < num)
            {
                l = m+1;
            }
            else if(arr[m] == num)
            {
                r = m;
            }
            else
            {
                return m;
            }
        }
        return l;
    }


    int kthSmallest(vector<vector<int>>& matrix, int k)
    {
        priority_queue<int> maxheap;
        int n = matrix.size();
        int m = matrix[0].size();
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<m; ++j)
            {
                if(maxheap.size() < k)
                {
                    maxheap.push(matrix[i][j]);
                }
                else
                {
                    if(maxheap.top() > matrix[i][j])
                    {
                        maxheap.pop();
                        maxheap.push(matrix[i][j]);
                    }
                }

            }
        }
        return maxheap.top();
    }

    int kthSmallest2(vector<vector<int>>& matrix, int k) {
        // 思路：对于这种矩阵，可以用n的复杂度查找某个数在不在里面
        //      还可以用n的复杂度算出有多少个元素<=指定的数

        //int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int L = matrix[0][0], R = matrix[n - 1][n - 1];
        while (L < R) {
            int mid = L + ((R - L) >> 1);
            int temp = search_lower_than_mid(matrix, mid, n);
            if (temp < k) L = mid + 1;
            else R = mid;
        }
        return L;
    }
    int search_lower_than_mid(const vector<vector<int>>& matrix, int x, const int n) {
        int i = n - 1, j = 0, cnt = 0;
        while (i >= 0 && j < n) {
            if (matrix[i][j] <= x) {
                j++;
                cnt += i + 1;
            }
            else i--;
        }
        return cnt;
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        return true;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty()) return vector<int> {-1, -1};
        int left  = 0;
        int right = nums.size()-1;
        //find lower bound
        while(left <= right)
        {
            int mid = left + (right-left)/2;
            if(nums[mid] >= target)
            {
                right = mid - 1;
            }
            else if(nums[mid] < target)
            {
                left = mid + 1;
            }
        }
        if(left > nums.size()-1 || nums[left] != target) return vector<int> {-1, -1};
        int start = left;
        right = nums.size()-1;
        while(left <= right)
        {
            int mid = left + (right-left)/2;
            if(nums[mid] > target)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        return vector<int> {start, left-1};
    }

    bool isBadVersion(int version)
    {
        return true;
    }

    int firstBadVersion(int n) {
        if(n == 0) return 0;
        int left  = 1;
        int right = n;
        //find lower bound
        while(left <= right)
        {
            int mid = left + (right-left)/2;
            if(isBadVersion(mid))
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        return isBadVersion(left)?left:0;
    }

    int searchInsert(vector<int>& nums, int target)
    {
        if(nums.empty()) return 0;
        int left = 0;
        int right = nums.size()-1;
        while(left <= right)
        {
            int mid = left + (right-left)/2;
            if(nums[mid] >= target)
            {
                right = mid-1;
            }
            else
            {
                left  = mid+1;
            }
        }
        return left;
    }

    char nextGreatestLetter(vector<char>& letters, char target)
    {

    }

    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> res;
        auto it = lower_bound(arr.begin(), arr.end(), x);
        if(it == arr.begin())
        {
            res.assign(arr.begin(), arr.begin()+k);
            return res;
        }
        else if(it == arr.end())
        {
            res.assign(arr.end()-k, arr.end());
            return res;
        }
        int mid = distance(arr.begin(), it);
        int left=mid, right=mid;
        while(k--)
        {
            if(left == 0)
            {
                ++right;
                continue;
            }
            if(right == arr.size()-1)
            {
                --left;
                continue;
            }
            if(x-arr[left] <= arr[right] - x)
            {
                --left;
            }
            else
            {
                ++right;
            }
        }
        res.assign(arr.begin()+left, arr.begin()+right);
        return res;
    }

    vector<int> findClosestElements1(vector<int>& arr, int k, int x) {
        vector<int> res;
        auto it = lower_bound(arr.begin(), arr.end(), x);
        if(it == arr.begin())
        {
            res.assign(arr.begin(), arr.begin()+k);
            return res;
        }
        else if(it == arr.end())
        {
            res.assign(arr.end()-k, arr.end());
            reverse(res.begin(), res.end());
            return res;
        }
        int mid = distance(arr.begin(), it);
        int left=mid-1, right=mid;
        for(; left>=0, right<arr.size(), k!=0; )
        {
            if(x-arr[left] <= arr[right] - x)
            {
                res.push_back(arr[left]);
                --left;
                --k;
            }
            else
            {
                res.push_back(arr[right]);
                ++right;
                --k;
            }
        }
        if( k == 0)
        {
            return res;
        }
        else
        {
            if(left < 0)
            {
                res.insert(res.end(), arr.begin()+right, arr.begin()+right+k);
            }
            else
            {
                vector<int> tmp(arr.begin()+left-k, arr.begin()+left);
                reverse(tmp.begin(), tmp.end());
                res.insert(res.end(), tmp.begin(), tmp.end());
            }
        }
        return res;
    }

};

#endif // BINARYSEARCHREL_H
