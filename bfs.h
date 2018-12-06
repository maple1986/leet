#ifndef BFS_H
#define BFS_H

#include <vector>
#include <string>
#include <balancetree.h>
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

    vector<vector<int>> levelOrder(NAryNode* root)
    {
        vector<vector<int>> res;
        if(!root) return res;
        queue<NAryNode*> q;
        q.push(root);
        while(!q.empty())
        {
            int size = q.size();
            vector<int> tmp;
            for(int i=0; i<size; ++i)
            {
                NAryNode* cur = q.front();
                q.pop();
                tmp.push_back(cur->val);
                for(auto i : cur->children)
                {
                    q.push(i);
                }
            }
        }
        return res;
    }

    int islandPerimeter(vector<vector<int>>& grid)
    {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size(), res = 0;
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(grid[i][j] == 0) continue;
                res += 4;
                if(i>0   && grid[i-1][j] == 1) res--;
                if(i<m-1 && grid[i+1][j] == 1) res--;
                if(j>0 && grid[i][j-1] == 1) res--;
                if(j<n-1 && grid[i][j+1] == 1) res--;
            }
        }
        return res;
    }

    int shortestPathLength(vector<vector<int>>& graph)
    {

        //queue<int> q;
        //q.push();
    }

    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        unordered_map<int, vector<pair<int, int>>> graph;
        for(const auto& flight : flights)
        {
            graph[flight[0]].emplace_back(flight[1], flight[2]);
        }

        int res = INT_MAX;
        queue<pair<int, int>> q;
        q.push({src, 0});
        int steps = 0;
        while(!q.empty())
        {
            int size = q.size();
            while(size--)
            {
                int cur  = q.front().first;
                int cost = q.front().second;
                if(cur == dst)
                {
                    res = min(res, cost);
                }

                for(const auto& p : graph[cur])
                {
                    if(cost + p.second > res) continue;
                    q.push({p.first, cost+p.second});
                }
            }
            if(steps++ > K) break;
        }
        return res == INT_MAX?-1:res;
    }

    int shortestBridge(vector<vector<int>>& A)
    {

    }
};

#endif // BFS_H
