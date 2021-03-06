#ifndef BACKTRACK_H
#define BACKTRACK_H
#include <vector>
#include <string>
#include <string.h>
#include <hashtable.h>
#include <set>
#include <unordered_set>
#include <iostream>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "utils.h"

using namespace std;
class backtrack
{
public:
    backtrack();
    static void test();
    /*
    char mapping[9][5] =
    {
        "ABC",
        "DEF",
        "GHI",
        "JKL",
        "MNO",
        "PQRS",
        "TUV",
        "WXYZ",
    };
    */
    vector<string> mapping1 =
    {"ABC","DEF",
        "GHI",
        "JKL",
        "MNO",
        "PQRS",
        "TUV",
        "WXYZ"};


    vector<string> letterCombinations(string digits) {
        vector<string> ret;
        for(int i=0; i<digits.size(); ++i)
        {
            int index = digits[i]-'1';
            if(ret.empty())
            {
                for(int j=0; j< mapping1[index].size();++j)
                {
                    string tmp;
                    tmp += mapping1[index][j];
                    ret.push_back(tmp);
                }
            }
            else
            {
                vector<string> tmp;
                for(int j=0; j<ret.size(); ++j)
                {
                    for(int k=0; k<mapping1[index].size(); ++k)
                    {
                        string tmp1 = ret[j];
                        tmp1 += mapping1[index][k];
                        tmp.push_back(tmp1);
                    }
                }
                ret.swap(tmp);
            }
        }
        return ret;
    }

    vector<string> letterCasePermutation(string S)
    {
        vector<string> res;
        PermutationHelper(S, 0, res);
        return res;
    }

    void PermutationHelper(string& S, int i, vector<string>& res)
    {
        if(i == S.length())
        {
            res.push_back(S);
            return;
        }
        PermutationHelper(S, i+1, res);

        if(isalpha(S[i]))
        {
            if(isupper(S[i]))
            {
                S[i] += 32;
            }
            else
            {
                S[i] -= 32;
            }
            PermutationHelper(S, i+1, res);
            if(isupper(S[i]))
            {
                S[i] += 32;
            }
            else
            {
                S[i] -= 32;
            }
        }
    }

    vector<string> letterCasePermutation2(string S) {
        vector<string> res;
        if(S.empty())
        {
            res.push_back("");
            return res;
        }
        dfs(S, 0, res);
        return res;
    }
    void dfs(string& S, int s, vector<string>& res)
    {
        if(s == S.length())
        {
            res.push_back(S);
            return;
        }
        dfs(S, s+1, res);
        if(!isalpha(S[s])) return;
        S[s] ^= (1 << 5);
        dfs(S, s+1, res);
        S[s] ^= (1 << 5);
    }

    vector<int> hours = {8, 4, 2, 1};
    vector<int> minutes ={32, 16, 8, 4, 2, 1};
    vector<string> readBinaryWatch(int num)
    {
        vector<string> res;
        /*
        for(int hr_num=0; hr_num <= hours.size(); ++hr_num)
        {
            int min_num = num - hr_num;
            if(min_num > minutes.size() || min_num < 0)
            {
                continue;
            }
            dfs(res, hr_num, min_num);
        }
        */
        dfs(num, 0, 0, 0, res);
        return res;
    }

    void dfs(int num, int pos, int hr_num, int min_num, vector<string>& res)
    {
        if(pos == hours.size() + minutes.size() && num != 0)
        {
            return;
        }
        if(num > hours.size() + minutes.size() - pos)
        {
            return;
        }
        if(num == 0)
        {
            res.push_back(to_string(hr_num) + (min_num < 10 ?  ":0" : ":") + to_string(min_num));
            return;
        }
        dfs(num, pos+1, hr_num, min_num, res);

        if(pos < hours.size())
        {
            hr_num += hours[pos];
        }
        else
        {
            min_num += minutes[pos-hours.size()];
        }
        if(min_num > 59 || hr_num > 11)
        {
            return;
        }
        dfs(num-1, pos+1, hr_num, min_num, res);
        if(pos < hours.size())
        {
            hr_num -= hours[pos];
        }
        else
        {
            min_num -= minutes[pos-hours.size()];
        }
    }

    vector<vector<int>> combine(int n, int k)
    {
        vector<vector<int>> res;
        unordered_set<int> visited;
        vector<int> tmp;
        combine_bt(n, k, 1, tmp, visited, res);
        return res;
    }

    void combine_bt(int n, int k, int start, vector<int>& tmp, unordered_set<int>& visited, vector<vector<int>>& res)
    {
        if(tmp.size() == k)
        {
            res.push_back(tmp);
            return;
        }
        for(int i=start; i<=n; ++i)
        {
            if(visited.count(i)) continue;
            tmp.push_back(i);
            visited.insert(i);
            combine_bt(n, k, i+1, tmp, visited, res);
            tmp.erase(tmp.end()-1);
            visited.erase(i);
        }
    }

    int singleNumber(vector<int>& nums)
    {
        multiset<int> mset;
        for(int i=0; i< nums.size(); ++i)
        {
            mset.insert(nums[i]);
        }
        auto it = mset.begin();
        while(it != mset.end())
        {
            if(mset.count(*it) == 1)
            {
                return *it;
            }
            ++it;
        }
        return -1;
    }

    string addBinary(string a, string b) {
        string result;
        bool carry = false;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        if(a.size() > b.size())
        {
            swap(a, b);
        }
        auto c1 = b.begin();
        for(auto& c:a)
        {
           int cur=0;
           if(carry) cur++;
           if(c-'0') cur++;
           if(*c1-'0') cur++;
           switch (cur) {
           case 0:
               carry = false;
               result += '0';
               break;
           case 1:
               carry = false;
               result += '1';
               break;
           case 2:
               carry = true;
               result += '0';
               break;
           case 3:
               carry = true;
               result += '1';
               break;
           default:
               break;
           }
           c1++;
        }
        if(!carry)
        {
            result.append(c1, b.end());
        }
        else
        {
            while(c1!=b.end())
            {
                if(*c1 == '1')
                {
                    result += '0';
                }
                else
                {
                    result += '1';
                    result.append(++c1, b.end());
                    carry = false;
                    break;
                }
                c1++;
            }
        }
        if(carry)
        {
            result += '1';
        }
        reverse(result.begin(), result.end());
        return result;
    }

    string addBinary1(string a, string b)
    {
        if(a.size() > b.size()) swap(a, b);
        int m = a.size();
        int n = b.size();
        for(int i=m-1; i>=0; --i)
        {
            b[n-m+i] += a[i]-'0';
        }
        int carry = 0;
        for(int i=n-1; i>=0; --i)
        {
            if(carry) b[i]++;
            if(b[i] > '1')
            {
                b[i] -= 2;
                carry =1;
            }
            else
            {
                carry = 0;
            }
        }
        if(carry)b.insert(b.begin(), '1');
        return b;
    }

    vector<vector<int>> permute(vector<int> nums)
    {
        vector<vector<int>> res;
        vector<int> tmp;
        backtracking(res, tmp, nums);
        return res;
    }

    void backtracking(vector<vector<int>>& list, vector<int>& tmp, vector<int>& nums)
    {
        if(tmp.size() == nums.size())
        {  //已将全部数选出，满足条件加入结果集，结束递归
            list.push_back(tmp);
        }
        else
        {
            for(int i = 0; i < nums.size(); i++){
                if(tmp.end() != find(tmp.begin(), tmp.end(), nums[i])) continue; // 已经选过的数不再选
                tmp.push_back(nums[i]);  //选择当前节点
                backtracking(list, tmp, nums);  //递归
                tmp.erase(tmp.end()-1);// (*last_element); //回溯到上一步，去掉当前节点
            }
        }
    }

    void fun(vector<int>& nums, vector<int>& tmp, unordered_set<int>& visited, vector<vector<int>>& res)
    {
        if(tmp.size() == nums.size())
        {
            res.push_back(tmp);

            return;
        }
        int last_element = INT_MIN;
        for(int i=0;i<nums.size();++i)
        {
            if(visited.count(i)) continue;
            if(last_element == nums[i]) continue; // 已经选过的数不再选
            visited.insert(i);
            tmp.push_back(nums[i]);  //选择当前节点
            fun(nums, tmp, visited, res);  //递归
            visited.erase(i);
            last_element = tmp.back();
            tmp.erase(tmp.end()-1);// (*last_element); //回溯到上一步，去掉当前节点
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        unordered_set<int> visited;
        fun(nums, tmp, visited, res);
        return res;
    }

    void recursion(vector<int> num, int i, int j, vector<vector<int> > &res) {
        if (i == j-1) {
            res.push_back(num);
            return;
        }
        for (int k = i; k < j; k++) {
            if (i != k && num[i] == num[k]) continue;
            swap(num[i], num[k]);
            recursion(num, i+1, j, res);
        }
    }
    vector<vector<int> > permuteUnique_Swap(vector<int> &num) {
        sort(num.begin(), num.end());
        vector<vector<int>>res;
        recursion(num, 0, num.size(), res);
        return res;
    }

    /*
ALGORITHM try(v1,...,vi)  // 这里的V1.....V2携带的参数说明 “可能解”
   // 入口处验证是否是全局解，如果是，直接返回。
   // 实际编程中也需要查看是否是无效解，如果是，也是直接返回
   IF (v1,...,vi) is a solution THEN RETURN (v1,...,vi)
   FOR each v DO  // 对于每一个可能的解，进行查看
      // 下面的含义是形成一个可能解 进行递归
      IF (v1,...,vi,v) is acceptable vector  THEN
        sol = try(v1,...,vi,v)
        IF sol != () THEN RETURN sol
        // 这个地方其实需要增加“回溯” 处理，实际编程中通常是函数参数的变化
      END
   END
   RETURN ()
      */

    vector<vector<int>> subsets(vector<int> nums)
    {
        vector<vector<int>> res;
        vector<int> tmp;
        subsetHelper(nums, 0, tmp, res);
        for(auto v : res)
        {
            printVec(v);
        }
        return res;
    }

    void subsetHelper(vector<int>& nums, int startIndex, vector<int>& tmp, vector<vector<int>>& res)
    {
        res.push_back(tmp);
        for(int i=startIndex; i<nums.size(); ++i)
        {
            if(tmp.end() != find(tmp.begin(), tmp.end(), nums[i])) continue;
            tmp.push_back(nums[i]);
            //printVec(tmp);
            subsetHelper(nums, i+1, tmp, res);
            tmp.pop_back();
            //printVec(tmp);
        }
    }

    vector<vector<int>> subsets2(vector<int> nums)
    {
        vector<vector<int>> res;
        vector<int> tmp;
        vector<bool> usage(nums.size(), false);
        sort(nums.begin(), nums.end());
        subsetHelper2(nums, 0, tmp, res, usage);
        return res;
    }

    void subsetHelper2(vector<int>& nums, int startIndex, vector<int> tmp, vector<vector<int>>& res, vector<bool>& usage)
    {
        res.push_back(tmp);
        for(int i=startIndex; i<nums.size(); ++i)
        {
            //if(tmp.end() != find(tmp.begin(), tmp.end(), nums[i])) continue;
            if(i>startIndex&&nums[i]==nums[i-1]) continue;
            tmp.push_back(nums[i]);
            subsetHelper2(nums, i+1, tmp, res, usage);
            tmp.pop_back();
        }
    }


    vector<vector<int>> subsets3(vector<int> nums)
    {
        vector<vector<int>> res;
        vector<int> tmp;
        int depth = 0;
        subsetHelper3(nums, 0, tmp, res, depth);
        /*
        for(auto v : res)
        {
            printVec(v);
        }
        */
        return res;
    }

    void subsetHelper3(vector<int>& nums, int startIndex, vector<int>& tmp, vector<vector<int>>& res, int& depth)
    {
        printf("recursion depth = [%d]:\n", depth);
        res.push_back(tmp);
        for(int i=startIndex; i<nums.size(); ++i)
        {
            if(tmp.end() != find(tmp.begin(), tmp.end(), nums[i])) continue;
            tmp.push_back(nums[i]);
            printVec(tmp);
            subsetHelper3(nums, i+1, tmp, res, ++depth);
            tmp.pop_back();
            printVec(tmp);
        }
    }

    vector<vector<int>> subsets4(vector<int>& nums)
    {
        vector<vector<int>> res;
        if(nums.empty()) return res;
        //vector<int> cur;
        backtracking(nums, 0, nums.size(), res);
        return res;
    }

    void backtracking(vector<int> nums, int start, int n, vector<vector<int>>& res)
    {
        if(n <= start)
        {
            res.push_back(nums);
            return;
        }
        backtracking(nums, start+1, n, res);
        vector<int> tmp(nums);
        auto pos = find(tmp.begin(), tmp.end(), start+1);
        tmp.erase(pos);
        backtracking(tmp, start+1, n, res);
        //nums.insert(nums.begin()+start, start+1);
    }

    vector<vector<int>> subsets5(vector<int>& nums)
    {
        vector<vector<int>> res;
        if(nums.empty()) return res;
        vector<int> cur;
        backtracking(0, nums, cur, res);
        return res;
    }

    void backtracking(int startIdx, vector<int>& nums, vector<int>& cur, vector<vector<int>>& res)
    {
        res.push_back(cur);
        for(int i=startIdx; i<nums.size(); ++i)
        {
            if(cur.end() != find(cur.begin(), cur.end(), nums[i]))
            {
                continue;
            }
            cur.push_back(nums[i]);
            backtracking(i+1, nums, cur, res);
            cur.pop_back();
        }
    }

    void printVec(vector<int>& vec){
        for (auto i : vec) {
            cout << i<< " ";
        }
        cout << "\n";
    }
    void print(vector<vector<int>>& res) {
        cout << "printing result : "<< endl;
        for(auto v : res) {
            cout << " [ ";
            for(auto i: v){
                cout << i << " " ;
            }
            cout << " ]";
            cout<<" \n";
        }
        cout<< "\n";
    }
    void popSubset(vector<int>& nums, int index, vector<vector<int>>& result, vector<int>& vec) {
        if(index == nums.size()) return;
        //cout << " popSubset for "<< index << endl;
        //cout << " result so far "<< endl; print(result);
        unordered_set<int> s;
        for(int i = index; i < nums.size(); i++){
          //cout << "start i "<< i << " for index "<< index<< endl;
            if(s.find(nums[i]) != s.end()) continue;
            vec.push_back(nums[i]);
            result.push_back(vec);
            popSubset(nums, i+1, result, vec);
            s.insert(nums[i]);
            vec.pop_back();
         //cout << " result after i "<< i << " for index "<< index<< endl; print(result);
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {

        vector<vector<int>> result;
        vector<int> vec;
        sort(nums.begin(), nums.end());
        result.push_back(vec);
        popSubset(nums, 0, result, vec);
        return result;

    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
    {
        vector<vector<int>> res;
        if(target <= 0) return res;
        vector<int> cur;
        dfs(candidates, cur, 0, target, res);
        return res;
    }

    void dfs(vector<int>& candidates, vector<int>& cur, int startIdx, int target, vector<vector<int>>& res)
    {
        if(target == 0)
        {
            res.push_back(cur);
            return;
        }

        for(int i=startIdx; i<candidates.size(); ++i)
        {
            if(candidates[i] > target) break;
            if(i>startIdx && candidates[i] == candidates[i-1]) continue;
            cur.push_back(candidates[i]);
            dfs(candidates, cur, startIdx+1, target-candidates[i], res);
            cur.pop_back();
        }
        return;
    }



    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        if(n > 45) return res;
        vector<int> cur;
        backtracking(k, n, 1, cur, res);
        return res;
    }


    void backtracking(int k, int n, int start, vector<int>& cur, vector<vector<int>>& res)
    {
        if(cur.size() == k-1)
        {
            int sum = accumulate(cur.begin(), cur.end(), 0);
            int toAdd = n - sum;
            if(toAdd >= start && toAdd <=9)
            {
                cur.push_back(toAdd);
                res.push_back(cur);
                cur.pop_back();
            }
            return;
        }

        for(int i=start; i<=9; ++i)
        {
            cur.push_back(i);
            backtracking(k, n, i+1, cur, res);
            cur.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        if(target <= 0) return res;
        sort(candidates.begin(), candidates.end());
        vector<int> cur;
        backtracking(candidates, target, candidates.size()-1, cur, res);
        return res;
    }

    void backtracking(vector<int>& candidates, int toAdd, int startpoint, vector<int>& cur, vector<vector<int>>& res)
    {
        if(toAdd == 0)
        {
            res.push_back(cur);
            return;
        }
        if(startpoint < 0)
        {
            return;
        }

        for(int i=startpoint; i>=0; --i)
        {
            if(candidates[i] > toAdd) continue;
            cur.push_back(candidates[i]);
            toAdd -= candidates[i];
            backtracking(candidates, toAdd, i, cur, res);
            cur.pop_back();
            toAdd += candidates[i];
        }
    }

    vector<int> grayCode(int n) {
        if(!n) return {0};
        vector<int> res;
        bitset<32> bits= {0};
        backtracking(bits, res, 0, n);
        reverse(res.begin(), res.end());
        return res;
    }

    void backtracking(bitset<32>& bits, vector<int>& res, int k, int n)
    {
        if(k == n)
        {
            res.push_back(bits.to_ulong());
            return;
        }
        bits.flip(k);
        backtracking(bits, res, k+1, n);
        bits.flip(k);
        backtracking(bits, res, k+1, n);
    }

    string getPermutation(int n, int k)
    {
        if(n == 1) return "1";
        string cur, res;
        vector<int> v(10, 0);
        int count = 0;
        getKth(n, k, cur, count, res, v);
        return res;
    }

    void getKth(int n, int k, string& cur, int& count, string& res, vector<int>& v)
    {
        if(cur.length() == n)
        {
            if(++count == k)
            {
                res = cur;
                return;
            }
        }
        for(int i=1; i<=n; ++i)
        {
            if(v[i]) continue;
            cur += to_string(i);
            v[i] = 1;
            getKth(n, k, cur, count, res, v);
            if(!res.empty()) return;
            v[i] = 0;
            cur.pop_back();
        }
    }
    /*
    vector<string> restoreIpAddresses(string s)
    {
        vector<string> res;
        if(s.length() > 12) return res;
        string cur;
        recursion(s, 0, 1, cur, res);
        return res;
    }

    void recursion(string& s, int start_point, int rec_depth, string& cur, vector<string>& res)
    {
        if(start_point >= s.length())
        {
            return;
        }
        //if(depth == 4 && s.)
    }
    */
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> res;
        if(n == 2 || n == 3) return res;

    }

    void helper(int n,int row, vector<string>& cur, vector<vector<string>>& res)
    {
        /*
        if(row == n){
            draw(pos);
            return;
        }
        for(int i=0;i<n;i++){
            if(isValid(row,i,pos)){
                pos[row][i] = 1;
                helper(n,row+1,pos);
                pos[row][i] = 0;
            }
        }
        */
    }


    int countArrangement(int N)
    {
        bitset<16> visited = {0};
        int res = 0;
        backtracking(N, 1, visited, res);
        return res;
    }

    void backtracking(int N, int cur, bitset<16>& visited, int& res)
    {
        if(cur == N+1)
        {
            ++res;
            return;
        }
        for(int i=1; i<=N; ++i)
        {
            if(visited[i]) continue;
            if(i%cur==0 || cur%i == 0)
            {
                visited.flip(i);
                backtracking(N, cur+1, visited, res);
                visited.flip(i);
            }
        }
        return;
    }

    int findTargetSumWays(vector<int>& nums, int S)
    {
        if(nums.empty()) return 0;
        int res = 0;
        dfs(nums, 0, 0, S, res);
        return res;
    }

    void dfs(vector<int>& nums, int cur, int sum, int S, int& res)
    {
        if(cur == nums.size())
        {
            if(sum == S) res++;
            return;
        }
        dfs(nums, cur+1, sum+nums[cur], S, res);
        dfs(nums, cur+1, sum-nums[cur], S, res);
        return;
    }

    vector<string> findStrobogrammatic(int n)
    {
        vector<string> res = {""};
        vector<string> res_odd = {"0", "1", "8"};
        if(n%2) res.swap(res_odd);
        for(int i= (n%2)+2; i <= n; i+=2)
        {
            vector<string> cur;
            for(auto& s : res)
            {
                if(i != n) cur.push_back("0" + s + "0");
                cur.push_back("1" + s + "1");
                cur.push_back("8" + s + "8");
                cur.push_back("6" + s + "9");
                cur.push_back("9" + s + "6");
            }
            res.swap(cur);
        }
        return res;
    }

    int countNumbersWithUniqueDigits(int n)
    {
        if(n == 0) return 1;
        bitset<10> mark;
        int res = 0;
        doCountNumbers(1, n, mark, res);
        return res;
    }

    void doCountNumbers(int cur, int n, bitset<10>& mark, int& res)
    {
        if(cur == n+1)
        {
            return;
        }
        for(int i=0; i<=9; ++i)
        {
            if(mark[i]) continue;
            if(cur==2 && mark[0]) continue;
            mark.flip(i);
            res++;
            doCountNumbers(cur+1, n, mark, res);
            mark.flip(i);
        }
        return;
    }

    int countArrangement1(int N)
    {
        if(N<3) return N;
        bitset<16> mark;
        int res = 0;
        doCountArrangement(1, N, mark, res);
        return res;
    }

    void doCountArrangement(int cur, int N, bitset<16>& mark, int& res)
    {
        if(cur == N+1)
        {
            return;
        }
        for(int i=1; i<=N; ++i)
        {
            if(mark[i]) continue;
            if(!(i%cur||cur%i)) continue;
            mark.flip(i);
            res++;
            doCountArrangement(cur+1, N, mark, res);
            mark.flip(i);
        }
    }

    vector<int> constructArray(int n, int k) {

    }

    vector<string> generateAbbreviations(string &word) {
        vector<string> res;
        if(word.empty()) return res;
        string cur;
        backtracking(word, 0, 0, cur, res);
        return res;
    }

    void backtracking(string& word, int curInx, int curAbbr, string& cur, vector<string>& res)
    {
        if(curInx == word.length())
        {
            res.push_back(cur);
            return;
        }
        cur += word[curInx];
        backtracking(word, curInx+1, 0, cur, res);
        cur.pop_back();
        string tmp(cur);
        while(isdigit(cur.back())) cur.pop_back();
        cur += to_string(++curAbbr);
        backtracking(word, curInx+1, curAbbr, cur, res);
        --curAbbr;
        cur = tmp;
    }

    vector<string> generateAbbreviations1(string word)
    {

    }

    vector<string> generateParenthesis(int n)
    {
        vector<string> res;
        if(n == 0) return res;
        string cur;
        dfs(n, n, 0, res, cur);
        return res;
    }

    void dfs(int left, int right, int sum, vector<string>& res, string& cur)
    {
        if(sum < 0)
        {
            return;
        }
        if(left == 0 && right ==0 && sum ==0)
        {
            res.push_back(cur);
            return;
        }
        if(left>0)
        {
            cur += "(";
            dfs(left-1, right, sum+1, res, cur);
            cur.pop_back();
        }
        if(right>0)
        {
            cur += ")";
            dfs(left, right-1, sum-1, res, cur);
            cur.pop_back();
        }
    }

    vector<vector<string>> partition(string s)
    {
        vector<vector<string>> res;
        vector<string> cur;
        dfs(s, 0, cur, res);
        return res;
    }

    void dfs(string& s, int start, vector<string>& cur, vector<vector<string>>& res)
    {
        if(start >= s.length())
        {
            res.push_back(cur);
            return;
        }
        for(int len=1; len<=s.length()-start; ++len)
        {
            string str = s.substr(start, len);
            if(!isPalindrome(str)) continue;
            cur.push_back(str);
            dfs(s, start+len, cur, res);
            cur.pop_back();
        }

    }

    bool isPalindrome(string& s)
    {
        int len = s.length();
        if(0 == len) return true;
        int l = 0, r = len-1;
        while(l < r)
        {
            if(s[l++] != s[r--]) return false;
        }
        return true;
    }

    string getPermutation1(int n, int k) {
        if(1 == n)return "1";
        vector<int> visited(n+1, 0);
        string res;
        dfs(k, n, visited, res);
        for(int i=1; i<=n; ++i)
        {
            if(!visited[i])
                res += to_string(i);
        }

        return res;
    }

    void dfs(int k, int n, vector<int>& visited, string& res)
    {
        if(1 == n)
        {
            return;
        }
        int fra = 1;
        for(int i=1; i<=n-1; ++i)
        {
            fra *=i;
        }
        int cur = int(ceil(double(k)/fra));
        cur = getKthValid(visited, cur);
        res += to_string(cur);
        visited[cur] = 1;
        if(k%fra == 0)
        {
            dfs(fra, n-1, visited, res);
        }
        else
        {
            dfs(k%fra, n-1, visited, res);
        }
    }

    int getKthValid(vector<int>& visited, int k)
    {
        for(int i=1; i<visited.size(); ++i)
        {
            if(!visited[i])
            {
                if(--k == 0)
                {
                    return i;
                }
            }
        }
        return 0;
    }

    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty() || board[0].empty() || word.empty()) return false;
        int m = board.size();
        int n = board[0].size();
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                //if(board[i][j] == word[0])
                //{
                    vector<vector<int>> visited(m, vector<int>(n, 0));
                    //visited[i][j] = 1;
                    if(dfs(i, j, m, n, visited, word, 0, board))
                    {
                        return true;
                    }
                //}
            }
        }
        return false;
    }

    vector<int> directions = {-1, 0, 1, 0, -1};

    bool dfs(int i, int j, int m, int n, vector<vector<int>>& visited, string& word, int cur, vector<vector<char>>& board)
    {
        if(cur == word.size())
        {
            return true;
        }
        if(i<0 || i>=m || j<0 || j>=n || visited[i][j]) return false;
        if(board[i][j] != word[cur]) return false;
        visited[i][j] = 1;
        for(int k=0; k<directions.size()-1; ++k)
        {
            int i0 = i+directions[k];
            int j0 = j+directions[k+1];
            if(dfs(i0, j0, m, n, visited, word, cur+1, board))
            {
                return true;
            }
        }
        visited[i][j] = 0;
        return false;
    }

    vector<string> restoreIpAddresses(string s) {
        if(s.length()>12 || s.length()<4) return {};
        vector<string> res;
        string cur;
        dfs(1, 0, s, cur, res);
        return res;
    }

    void dfs(int depth, int start, string& s, string& cur, vector<string>& res)
    {
        if(start >= s.length()) return;
        if(depth == 4)
        {
            string rest = s.substr(start);
            if(validIp(rest))
            {
                cur += "." + rest;
                printf("ip = %s\n", cur.c_str());
                res.push_back(cur);
            }
            return;
        }
        for(int i=start; i<min(start+3, (int)s.length()); ++i)
        {
            string num = s.substr(start, i-start+1);
            if(validIp(num))
            {
                int pos = cur.length();
                if(depth != 1)
                {
                    cur += ".";
                }
                cur += num;
                dfs(depth+1, i+1, s, cur, res);
                cur = cur.substr(0, pos);
            }
        }
        return;
    }

    bool validIp(string& s)
    {
        if(s.length() > 3 || s.length() < 1) return false;
        if(s[0] == 0 && s.length()>1) return false;
        int ip = stoi(s);
        if(ip>=0 && ip <= 255) return true;
        return false;
    }

    /*
    p:
        while(p)
        if(p == '.')
            s++
        if(p == '*')
            for()
              isMatch(s, p)
        else if(p == s)
            {
                continue;
            }
        return s.empty();
    */

    bool isMatch(string s, string p) {
        trim(p);
        return isMatch(s, 0, p, 0);
    }

    void trim(string& p)
    {
        for(int i=0; i<p.length();)
        {
            if(i>0 && p[i] == '*' && p[i-1] == '*')
            {
                p.erase(p.begin()+i, p.begin()+i+1);
            }
            else
            {
                ++i;
            }
        }
    }
    /*
"adceb"
"*a*b"
*/

    bool isMatch(string s, int si, string p, int pi)
    {
        if(si == s.size())
        {
            if(pi == p.size())
            {
                return true;
            }
            else
            {
                while(pi<p.size() && p[pi++] == '*')
                if(pi == p.size()) return true;
                return false;
            }
        }
        if(pi == p.size())
        {
            if(p[pi-1] == '*') return true;
            return false;
        }
        if(p[pi] != '*')
        {
            if(p[pi] == s[si] || p[pi] == '?')
            {
                return isMatch(s, si+1, p, pi+1);
            }
            return false;
        }
        else
        {
            for(int i=si; i<s.size(); ++i)
            {
                if(isMatch(s, i, p, pi+1))
                {
                    return true;
                }
            }
            return false;
        }
    }

    int optimalMatch(vector<vector<int>> &matrix) {
        // Write your code here
        if(matrix.empty() || matrix[0].empty())
            return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<pair<int, int>> persons;
        vector<pair<int, int>> bikes;
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(matrix[i][j] == 1)
                    persons.push_back({i, j});
                else if(matrix[i][j] == 2)
                    bikes.push_back({i, j});
            }
        }
        int k = persons.size();
        vector<vector<int>> dis(k, vector<int>(k, 0));
        for(int i=0; i<k; ++i)
        {
            for(int j=0; j<k; ++j)
            {
                dis[i][j] = abs(persons[i].first-bikes[j].first)+abs(persons[i].second-bikes[j].second);
            }
        }
        Utils::printVV(dis);
        int res = INT_MAX;
        int cur = 0;
        vector<int> visitedPerson(k, 0);
        vector<int> visitedBike(k, 0);
        backtracking(dis, 0, k, visitedPerson, visitedBike, cur, res);
        return res;
    }

    void backtracking(vector<vector<int>>& dis, int d, int k, vector<int>& vP, vector<int>& vB, int cur, int& res)
    {
        if(d == k)
        {
            res = min(res, cur);
        }
        for(int i=0; i<k; ++i)
        {
            if(vP[i]) continue;
            vP[i] = 1;
            for(int j=0; j<k; ++j)
            {
                if(vB[j]) continue;
                vB[j] = 1;
                //cur += dis[i][j];
                backtracking(dis, d+1, k, vP, vB, cur+dis[i][j], res);
                vB[j] = 0;
            }
            vP[i] = 0;
        }
    }
};

#endif // BACKTRACK_H
