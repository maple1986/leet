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
        /*
        if(n == 1) return "1";
        string res("");
        int total = 1;
        set<int> candidates;
        for(int i=1; i<=n; ++i)
        {
            total *= i;
            candidates.insert(i);
        }
        while(total)
        {
            total = total/
        }
        */
        return "";
    }

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

    vector<int> constructArray(int n, int k)
    {

    }


};

#endif // BACKTRACK_H
