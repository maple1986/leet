#ifndef BITSREL_H
#define BITSREL_H

#include <vector>
#include <string>
#include <unordered_set>
#include <bitset>
#include <iostream>
using namespace std;
class BitsRel
{
public:
    BitsRel();
    static void test();
    vector<vector<int>> subsets(vector<int>& nums)
    {
        vector<vector<int>> ret;
        if(nums.size() == 0)
        {
            return ret;
        }
        for(int i=0; i<nums.size(); ++i)
        {
            //if(nums[i])
        }
    }

    void backtrack(vector<int>& nums, int begin, int end, vector<vector<int>>& out)
    {

    }

    vector<string> readBinaryWatch(int num)
    {

    }

    int getSum(int a, int b)
    {

    }
/*
    int is_a_solution(int a[],int k, data input)
    {
        return k==input;
    }

    void construct_candidates(int a[],int k, data input, int c[],int *ncandidates)
    {
        c[0] = 1;
        c[1] = 0;
        *ncandidates = 2;
    }

    void process_solution(int a[],int k,data input)
    {
        int i;
        printf("{");
        for(i=1;i<=k;i++)
            if(a[i])
                printf(" %d",i);
        printf(" }\n");
    }

    bool finished = FALSE; /* 是否获得全部解? * /
    backtrack(int a[], int k, data input)
    {
        int c[MAXCANDIDATES]; /*这次搜索的候选 * /
        int ncandidates; /* 候选数目 * /
        int i; /* counter * /
        if (is_a_solution(a,k,input))
        process_solution(a,k,input);
        else {
            k = k+1;
            construct_candidates(a,k,input,c,&ncandidates);
            for (i=0; i<ncandidates; i++) {
                a[k] = c[i];
                make_move(a,k,input);
                backtrack(a,k,input);
                unmake_move(a,k,input);
                if (finished) return; /* 如果符合终止条件就提前退出 * /
            }
        }
    }
    */

    int countPrimeSetBits(int L, int R)
    {
        int res = 0;
        unordered_set<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        for(int i=L; i<=R; ++i)
        {
            int countOnes = 0;
            int n = i;
            while(n)
            {
                if(n&1) countOnes++;
                n = n>>1;
            }
            if(primes.count(countOnes)) res++;
        }
        return res;
    }

    bool canIWin(int maxI, int total) {
        if(maxI>=total) return true;
        bitset<32> used;
        used.reset();
        return canIWinUtil(total, maxI, used);
    }

    bool canIWinUtil(int remain, int maxI, bitset<32>& used)
    {
        if(remain<=0) return false;
        for(int i=1; i<=maxI; ++i)
        {
            if(used.test(i)) continue;

            used.flip(i);
            cout << used.to_string().c_str() << endl;
            if(!canIWinUtil(remain-i, maxI, used)) return true;
            used.flip(i);
            //cout << used.to_string().c_str() << endl;
        }
        //cout << used.to_string().c_str() << endl;
        return false;
    }
};

#endif // BITSREL_H
