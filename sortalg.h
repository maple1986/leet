#ifndef SORTALG_H
#define SORTALG_H

#include <vector>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <memory.h>

using namespace std;
class SortAlg
{
public:
    SortAlg();
    static void test();
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
    {
        vector<int> res;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int>::iterator it1 = nums1.begin();
        vector<int>::iterator it2 = nums2.begin();
        while(it1 != nums1.end() && it2 != nums2.end())
        {
            if(*it1 < *it2)
            {
                it1++;
            }
            else if(*it1 > *it2)
            {
                it2++;
            }
            else
            {
                if(res.empty())
                {
                    res.push_back(*it1);
                }
                else
                {
                    if(res.back() != *it1)
                    {
                        res.push_back(*it1);
                    }
                }
                it1++, it2++;
            }
        }

        /*
        set<int> snum1(nums1.begin(), nums1.end());
        set<int> snum2(nums2.begin(), nums2.end());
        multiset<int> mset(snum1.begin(), snum1.end());
        mset.insert(snum2.begin(), snum2.end());

        multiset<int>::iterator it = mset.begin();
        while(it != mset.end())
        {
            if(mset.count(*it) > 1)
            {
                res.push_back(*it);
            }
            it++;
        }
        return res;
        */
    }

    vector<int> intersection_using_stl_facilities(vector<int>& nums1, vector<int>& nums2)
    {

        std::vector<int> result;
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());
        //std::set_intersection(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), std::back_inserter(result));
        result.erase(std::unique(result.begin(), result.end()), result.end());

        return result;
    }


    vector<int> intersection1(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> lookup(nums1.begin(), nums1.end());
        vector<int> res;
        /*
        for(int num : nums2){
            if(lookup.count(num)){
                res.push_back(num);
                lookup.erase(num);    //remove it from the lookup so we don't double add.
            }
        }
        */
        return res;
    }

    /*
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> res;
        if(!nums1.size() || !nums2.size())
            return vector<int>(0);
        if(nums1.size() >= nums2.size()){
            unordered_set<int> lookup(nums1.begin(), nums1.end());
            for(int num : nums2){
                if(lookup.count(num) && !res.count(num)){
                    res.insert(num);
                }
            }
        }
        else{
            return intersection(nums2, nums1);
        }
        return vector<int>(res.begin(), res.end());
    }
    */
    vector<int> intersection2(vector<int>& nums1, vector<int>& nums2)
    {
        vector<int> res;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int>::iterator it1 = nums1.begin();
        vector<int>::iterator it2 = nums2.begin();
        while(it1 != nums1.end() && it2 != nums2.end())
        {
            if(*it1 < *it2)
            {
                it1++;
            }
            else if(*it1 > *it2)
            {
                it2++;
            }
            else
            {
                res.push_back(*it1);
                it1++, it2++;
            }
        }
        return res;
    }
    //[0,1,3,5,6]
    /*
     * Input: citations = [0,1,3,5,6]
    Output: 3
    Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each of them had
             received 0, 1, 3, 5, 6 citations respectively.
             Since the researcher has 3 papers with at least 3 citations each and the remaining
             two with no more than 3 citations each, her h-index is 3.

We use two pinter to solve this problem: pointer l (low) and pointer h (high).

Say n = citations.length.
Because the range of H-index is [0,n], at the beginning we must point high pointer after the last element of the array: h = n. In this way we can generate all possible value without worrying about annoying corner case.

The rest is standard binary search, we find middle point m and compare citations[m] with n-m (n-m means number of papers has at least citations[m] citations.)

    citations[m] == n-m : we find the answer
    citations[m] < n-m : more papers has at least this number of citations we should raise the bar of citations so we go to the right part: l = m+1.
    citations[m] > n-m : we should lower the bar so we go to the left part: h = m.

In the end l == r and the H-index is n-l.

    */
    int hIndex(vector<int>& citations) {
        int res = 0;
        int n = citations.size();
        for(int i=0; i<n; ++i)
        {
            if(res >= n-i)
            {
                break;
            }
            if(citations[i] >= n-i)
            {
                res = n-i;
            }
        }
        return res;
    }

    bool isAnagram(string s, string t)
    {
        int dict[26] = {0};

        for(int i=0; i<s.size(); ++i)
        {
            ++dict[s[i]-'a'];
        }

        for(int i=0; i<t.size(); ++i)
        {
            --dict[t[i]-'a'];
        }

        for(int i=0; i<26; ++i)
        {
            if(dict[i] != 0)
            {
                return false;
            }
        }
        return true;
    }
    /*
     * Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
    */
    vector<int> findAnagrams(string s, string p)
    {
        vector<int> res(0);
        if(s.size() < p.size())
        {
            return res;
        }
        int dict[26] = {0};

        for(int i=0; i< p.size(); ++i)
        {
            ++dict[p[i]-'a'];
        }
        int dict_tmp[26] = {0};
        int cur = 0, start = 0;
        int end   = p.size()-1;

        while(end < s.size())
        {
            if(++dict_tmp[s[cur] - 'a'] <= dict[s[cur] - 'a'])
            {
                if(cur == end)
                {
                    res.push_back(start);
                    //while()

                    cur = start;
                    memset(dict_tmp, 0, 26*sizeof(int));
                }
                else
                {
                    cur++;
                }
            }
            else
            {
                end += ++cur - start;
                start = cur;
                memset(dict_tmp, 0, 26*sizeof(int));
            }
        }

        while(end < s.size())
        {
            if(++dict_tmp[s[cur] - 'a'] <= dict[s[cur] - 'a'])
            {
                if(cur == end)
                {
                    res.push_back(start);
                    start++;
                    end++;
                    cur = start;
                    memset(dict_tmp, 0, 26*sizeof(int));
                }
                else
                {
                    cur++;
                }
            }
            else
            {
                start++;
                end++;
                cur = start;
                memset(dict_tmp, 0, 26*sizeof(int));
            }
        }

        return res;
    }

    vector<int> findAnagrams2(string s, string p)
    {
        vector<int> res;
        if (s.length()<p.length()) return res;
        int N=p.size(), i=0;
        vector<int> tabS(26,0), tabP(26,0);
        for (;i<p.size();i++){
            tabS[s[i]-'a']++;
            tabP[p[i]-'a']++;
        }
        for (;i<s.size();i++){
            if (tabS==tabP)
                res.push_back(i-N);
            tabS[s[i]-'a']++;
            tabS[s[i-N]-'a']--;
        }

        if (tabS==tabP)
            res.push_back(i-N);
        return res;
    }
/*
How do we know string p is a permutation of string s?
Easy, each character in p is in s too.
So we can abstract all permutation strings of s to a map (Character -> Count).
i.e. abba -> {a:2, b:2}. Since there are only 26 lower case letters in this problem, we can just use an array to represent the map.
How do we know string s2 contains a permutation of s1?
 We just need to create a sliding window with length of s1, move from beginning to the end of s2.
 When a character moves in from right of the window,
we subtract 1 to that character count from the map.
When a character moves out from left of the window, we add 1 to that character count.
 So once we see all zeros in the map, meaning equal numbers of every characters between s1 and the substring in the sliding window, we know the answer is true.

*/

    bool checkInclusion(string s1, string s2)
    {
        if (s1.length() > s2.length()) return false;
        int N = s1.size();
        vector<int> tabS1(26, 0);
        vector<int> tabS2(26, 0);
        int i=0;
        for(; i<s1.size(); ++i)
        {
            tabS1[s1[i] - 'a']++;
            tabS2[s2[i] - 'a']++;
        }
        for (;i<s2.size();++i)
        {
            if(tabS1 == tabS2)
            {
                return true;
            }
            tabS2[s2[i] - 'a']++;
            tabS2[s2[i-N] - 'a']--;
        }
        if(tabS1 == tabS2)
        {
            return true;
        }
        return false;
    }
/*
 *  Input: S = "ADOBECODEBANC", T = "ABC"
    Output: "BANC"
 */

    string minWindow(string s, string t)
    {

    }

void Qsort(int a[], int low, int high)
{
    if(low >= high)
    {
        return;
    }
    int first = low;
    int last = high;
    int key = a[first];/*用字表的第一个记录作为枢轴*/

    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            --last;
        }

        a[first] = a[last];/*将比第一个小的移到低端*/

        while(first < last && a[first] <= key)
        {
            ++first;
        }

        a[last] = a[first];
/*将比第一个大的移到高端*/
    }
    a[first] = key;/*枢轴记录到位*/
    Qsort(a, low, first-1);
    Qsort(a, first+1, high);
}
bool searchMatrix2(vector<vector<int>>& matrix, int target)
{
    int n = matrix.size();
    if(n == 0)
    {
        return false;
    }
    int m = matrix.begin()->size();
    if(m == 0)
    {
        return false;
    }

}

bool searchMatrix(vector<vector<int>>& matrix, int target)
{
    int n = matrix.size();
    if(n == 0)
    {
        return false;
    }
    int m = matrix.begin()->size();
    if(m == 0)
    {
        return false;
    }
    if(target < matrix[0][0] || target > matrix[n-1][m-1])
    {
        return false;
    }
}

int search(vector<int>& nums, int target)
{
    int low  = 0;
    int high = nums.size()-1;
    while(low < high)
    {
        int mid = (low + high)/2;
        if(nums[mid] == target)
        {
            return mid;
        }
        else if(nums[mid] > target)
        {
            high = mid-1;
        }
        else
        {
            low = mid+1;
        }
    }
    if(nums[high] == target) return high;
    return -1;
}

int peakIndexInMountainArray(vector<int>& A) {
    int low = 0;
    int high = A.size()-1;
    while(low <= high)
    {
        int mid = low + (high-low)/2;
        if((A[mid] > A[mid+1]) && (A[mid] > A[mid-1]))
        {
            return mid;
        }
        else if(A[mid] <= A[mid+1])
        {
            low = mid + 1;
        }
        else
        {
            high = mid -1;
        }
    }
    return -1;
}

int peakIndexInMountainArray2(vector<int>& A)
{
    int l=0, r=A.size()-1;
    while(l+1<r) {
        int mid = l+(r-l)/2;
        if(A[mid]<A[mid+1]) l=mid;
        else r=mid;
    }
    return A[l]>A[r]?l:r;
}

int findRadius(vector<int>& houses, vector<int>& heaters)
{
    int radius = 0;
    for(int i=0; i<houses.size(); ++i)
    {
        int target = houses[i];
        for(int j=0; j<heaters.size(); ++j)
        {
            //if(abs(heaters[j]-target) > radius)
        }
    }
    return radius;
}
};

#endif // SORTALG_H
