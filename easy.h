#ifndef EASY_H
#define EASY_H

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

using namespace std;
class easy
{
public:
    easy();
    static void test()
    {

    }

    bool isOneBitCharacter(vector<int>& bits)
    {
        if(bits.empty()) return false;
        int size = bits.size();
        if(bits[size-1]) return false;
        bool res = false;
        for(int i=0; i<size;)
        {
            if(i == size-1)
            {
                res = true;
                break;
            }
            if(bits[i] == 1)
            {
                i += 2;
            }
            else
            {
                i += 1;
            }

        }
        return res;
    }

    int arrangeCoins(int n)
    {
        return 0;
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


    vector<vector<int>> removeOne(vector<vector<int>> &matrix, int x, int y)
    {
        // Write your code here
        bool drop = false;
        matrix[x][y] = 0;
        for(int i=1; i<matrix.size(); ++i)
        {
            if(!drop)
            {
                if(matrix[i][y] == 1)
                {
                    continue;
                }
                drop = true;
            }
            else
            {
                matrix[i][y] = 0;
            }
        }
        return matrix;
    }

};

#endif // EASY_H
