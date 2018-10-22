#ifndef BFS_H
#define BFS_H

#include <vector>
#include <string>

using namespace std;

class BFS
{
public:
    BFS();
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList);
    int WordGap(string& left, string& right);
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix)
    {
        vector<vector<int>> res;
        int m = matrix.size();
        if(!m) return res;
        int n = matrix[0].size();
        if(!n) return res;

        for(int i=0; i<m; ++i)
        {
            vector<int> tmp;
            for(int j=0; j<n; ++j)
            {
                if(matrix[i][j] == 0)
                {
                    tmp.push_back(0);
                }
                else
                {
                    tmp.push_back(m+n);
                }
            }
            res.push_back(tmp);
        }

        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(res[i][j] != 0)
                {

                }
            }
        }
        return res;
    }
};

#endif // BFS_H
