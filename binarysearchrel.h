#ifndef BINARYSEARCHREL_H
#define BINARYSEARCHREL_H

#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <unordered_map>

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

    int kthSmallest3(vector<vector<int>> &matrix, int k)
    {
        // write your code here
        priority_queue<int> pq;
        for(int i = 0; i<matrix.size(); ++i)
        {
            for(int j=0; j<matrix[0].size(); ++j)
            {
                if(pq.size() >= k)
                {
                    if(matrix[i][j] < pq.top())
                    {
                        pq.push(matrix[i][j]);
                        pq.pop();
                    }
                }
                else
                {
                    pq.push(matrix[i][j]);
                }
            }
        }
        return pq.top();
    }


    int kthSmallest1(vector<vector<int>>& matrix, int k)
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
        auto start = it, end = it;
        while(end - start < k)
        {
            if(end == arr.end())
            {
                --start;
                continue;
            }
            if(start == arr.begin())
            {
                ++end;
                continue;
            }
            if(x - *(start-1) <= *end - x)
            {
                --start;
            }
            else
                ++end;
        }
        res.assign(start, end);
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

    vector<int> findClosestElements3(vector<int>& arr, int k, int x)
    {
        int left = 0, right = arr.size()-k;
        while(left < right)
        {
            int mid = left + (right-left)/2;
            printf("left[%d], right[%d], mid[%d]\n", left, right, mid);
            if(abs(arr[mid+k]-x) <= abs(arr[right+k]-x))
            {
                right = mid;
            }
            else
            {
                left = mid+1;
            }
        }
        vector<int> result(arr.begin() + left, arr.begin() + left + k);
        return result;
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return false;
        if(matrix[0].empty()) return false;
        if (target < matrix[0][0] || target > matrix.back().back()) return false;
        int m = matrix[0].size();
        int n = matrix.size();
        int low = 0, high = n-1;
        while(low <= high)
        {
            int mid = low + (high-low)/2;
            if(matrix[mid][0] > target)
            {
                high = mid-1;
            }
            else if(matrix[mid][0] < target)
            {
                low = mid+1;
            }
            else
            {
                return true;
            }
        }

        int left = 0, right = m-1;
        while(left <= right)
        {
            int mid = left + (right-left)/2;
            if(matrix[high][mid] > target)
            {
                right = mid-1;
            }
            else if(matrix[high][mid] < target)
            {
                left = mid+1;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    bool searchMatrix2(vector<vector<int>>& matrix, int target)
    {
        int m = matrix.size();
        if(m == 0) return false;
        int n = matrix[0].size();
        if(n == 0) return false;
        if(target < matrix[0][0] || target > matrix.back().back()) return false;
        int x = 0, y = n-1;
        while(y>=0 && x<m)
        {
            if(matrix[x][y] > target) y--;
            else if(matrix[x][y] < target) x++;
            else return true;
        }
        return false;
    }

    int getCap(vector<int> &a, int target)
    {
        if(a.empty() || target == 0) return 0;
        if(a.size() == 1) return target;
        sort(a.begin(), a.end());
        int n = a.size();
        vector<int> prefix_sum(n, 0);
        prefix_sum[0] = a[0];
        for(int i=1; i<n; ++i)
        {
            prefix_sum[i] = prefix_sum[i-1] + a[i];
        }
        int low = 0, high = n-1;
        while(low <= high)
        {
            int mid = low + (high-low)/2;
            if(a[mid]*(mid+1) + prefix_sum[n-1] - prefix_sum[mid] > target)
            {
                high = mid-1;
            }
            else if(a[mid]*(mid+1)+prefix_sum[n-1]-prefix_sum[mid] < target)
            {
                low = mid+1;
            }
            else return a[mid];
        }
        for(int i=a[high]; i<=a[low]; ++i)
        {
            if(i*(high+1)+prefix_sum[n-1]-prefix_sum[high] >= target)
            {
                return i;
            }
        }
        return a[low];
    }

    int getCap1(vector<int> &a, int target)
    {

    }

    vector<int> minimalDistance(vector<int> &a, vector<int> &b) {
        // Write your code here
        set<int> source(a.begin(), a.end());
        unordered_map<int, int> dict;
        vector<int> res;
        /*
        for(b)
        {
            find in dict;
            find;
            insert to dict;
            arrange the result;
        }
        */
        for(int num : b)
        {
            if(dict.count(num))
            {

                //continue;
            }
            else
            {
                auto it = source.lower_bound(num);
                if(it == source.begin())
                {
                    dict[num] = *it;
                }
                else if(it == source.end())
                {
                    dict[num] = *(--it);
                }
                else
                {
                    int cand1 = *it;
                    int cand2 = *(--it);
                    dict[num] = cand1-num >= num-cand2?cand2:cand1;
                }
            }
            res.push_back(dict[num]);
        }

        return res;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        int m = nums1.size();
        int n = nums2.size();
        if(m > n) return findMedianSortedArrays(nums2, nums1);
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
        int l = 0, r = m-1;
        int k = (total+1)/2, m1 = 0, m2 = k;
        while(l <= r)
        {
            m1 = l + (r-l)/2;
            m2 = k - m1;
            if(nums1[m1] < nums2[m2])
            {
                l = m1+1;
            }
            else if(nums1[m1] > nums2[m2])
            {
                r = m1-1;
            }
            else
            {
                break;
            }
        }
    }

    //Given nums = [5, 2, 6, 1]
    //Return the array [2, 1, 1, 0].
    vector<int> countSmaller(vector<int>& nums)
    {
        vector<int> sortedNums;
        vector<int> res;
        for(int i=nums.size()-1; i>=0; --i)
        {
            auto index = lower_bound(sortedNums.begin(), sortedNums.end(), nums[i]);
            res.push_back(distance(index, sortedNums.begin()));
            sortedNums.insert(index, nums[i]);
        }
        reverse(res.begin(), res.end());
        return res;
    }
    //808201
    bool isPerfectSquare(int num) {
        if(num == 1) return true;
        int l = 1, r = num/2+1;
        while(l<r)
        {
            long long mid = l+(r-l)/2, target = mid*mid;
            if(target<num)
            {
                l = mid+1;
            }
            else if(target>num)
            {
                r = mid;
            }
            else return true;
        }
        return false;
    }

    int kthSmallest(vector<vector<int>>& matrix, int k)
    {
        if(matrix.empty() || matrix[0].empty())
        {
            return 0;
        }
        int l = matrix[0][0], r = matrix.back().back();
        while(l<=r)
        {
            int mid = l+(r-l)/2;
            int pos = 0;
            for(int i=0; i<matrix.size(); ++i)
            {
                auto it = upper_bound(matrix[i].begin(), matrix[i].end(), mid);
                pos += distance(matrix[i].begin(), it);
            }
            if(pos < k)
            {
                l = mid+1;
            }
            else// if(pos > k)
            {
                r = mid-1;
            }
        }
        return l;
    }
    //1, 2, 4, 5, 6, 9
    //[0, 1, 1, 1, 1]
    int findLowerBound(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            static int round = 1;
            int mid = left + (right - left) / 2;
            printf("round%d, l=%d, r=%d, mid=%d, val=%d\n", round++, left, right, mid, nums[mid]);
            if (nums[mid] < target) left = mid + 1;
            else right = mid;
        }
        return right;
    }

    int triangleNumber(vector<int>& nums)
    {
        int n = nums.size();
        if(n < 3) return 0;
        sort(nums.begin(), nums.end());
        int count = 0;
        for(int i=0; i<n-2; ++i)
        {
            for(int j=i+1; j<n-1; ++j)
            {
                int sum = nums[i]+nums[j];
                int left = j+1, right = n;
                while (left<right) {
                    int mid = left+(right-left)/2;
                    if(nums[mid] >= sum)
                    {
                        right = mid;
                    }
                    else left = mid+1;
                }
                if(right-j-1>0)
                {
                    count += right-j-1;
                }
            }
        }
        return count;
    }

    vector<int> findClosestElements2(vector<int>& arr, int k, int x) {
        int n = arr.size();
        if(n==0 || n<k) return {};
        auto it = lower_bound(arr.begin(), arr.end(), x);
        vector<int> res;
        if(it == arr.begin())
        {
            res.assign(arr.begin(), arr.begin()+k);
            return res;
        }
        else if(it == arr.end())
            return vector<int>(arr.rbegin(), arr.rbegin()+k);
        else
        {
            int l = it-arr.begin()-1;
            int r = it-arr.begin();
            while(k--)
            {
                if(l < 0) res.push_back(arr[r++]);
                else if(r>=n) res.push_back(arr[l--]);
                else
                {
                    if(abs(arr[l]-x) <= abs(x-arr[r]))
                    {
                        res.push_back(arr[l--]);
                    }
                    else
                    {
                        res.push_back(arr[r++]);
                    }
                }
            }
        }
        return res;
    }

    int smallestDistancePair(vector<int>& nums, int k)
    {
        vector<int> distance(1000001, 0);
        int n = nums.size();
        for(int i=0; i<n; ++i)
        {
            for(int j=i+1; j<n; ++j)
            {
                distance[abs(nums[j]-nums[i])]++;
            }
        }
        n = distance.size();
        for(int i=0; i<n; ++i)
        {
            k -= distance[i];
            if(k <= 0)
                return i;
        }
        return -1;
    }

    int smallestDistancePair2(vector<int>& nums, int k)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int l = 0, r = nums[n-1]-nums[0]+1;
        while(l<r)
        {
            int mid = l+(r-l)/2;

        }
    }

    bool isPossible(vector<int>& nums) {
        int n = nums.size();
        if(n < 3) return false;
        //vector<int> ends(n, -1);
        //vector<int> count(n, 0);
        int maxNum = nums[0], minNum = nums[0];
        for(int num: nums)
        {
            maxNum = max(maxNum, nums[i]);
            //minNum = min(minNum, nums[i]);
        }
        vector<multiset<int>> bucket(maxNum+1);
        //unordered_map<int, int> ends;
        //ends[nums[0]] = 1;
        //bucket[nums[0]].insert(1);
        for(int i=0; i<n; ++i)
        {
            if(bucket[nums[i]].empty())
            {
                bucket[nums[i]].insert(1);
            }
            else
            {

            }
            /*
            for(int j=0; j<=len; ++j)
            {
                if(nums[i] == ends[j]+1)
                {
                    ends[j] = nums[i];
                    count[j]++;
                }
                else
                {
                    ends[++len] = nums[i];
                    count[len]  = 1;
                }
            }
            */
        }
        for(int j=0; j<=len; ++j)
        {
            if(count[j] < 3) return false;
        }
        return true;
    }
};

#endif // BINARYSEARCHREL_H
