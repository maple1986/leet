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
        while(left <= right)
        {
            int mid = left + (right-left)/2;
            if(nums[mid] < target)
            {
                left = mid+1;
            }
            else if(nums[mid] >= target)
            {
                right = mid-1;
            }
        }
        if(nums[left] != target) return vector<int> {-1, -1};
        int start = left, end = left;
        while(start > 0 && nums[start] == nums[start-1]) start--;
        while(end < nums.size()-1 && nums[end] == nums[end+1]) end++;
        return vector<int> {start, end};

    }

};

#endif // BINARYSEARCHREL_H
