#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;
class UnionFind
{
public:
    UnionFind();
    static void test();

    void Union(const pair<int, int>& l, const pair<int, int>& r)
    {

        return;
    }
    pair<int, int> Find(const pair<int, int>&)
    {

    }

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {

    }

    int numIslands(vector<vector<char>>& grid) {

    }
};

class UnionFind1 {
public:
    static void test()
    {
        vector<vector<char>> grid = {{'1'},{'0'},{'1'},{'0'},{'1'},{'1'}};
        UnionFind1 uf;
        int i = uf.numIslands(grid);
    }
    class UnionFind
    {
    public:
        UnionFind(int n)
        {
            parents = vector<int>(n, 0);
            for(int i=0; i<parents.size(); ++i)
            {
                parents[i] = i;
            }
            //ranks = vector<int>(n, 0);
        }

        int Find(int x)
        {
            if( x != parents[x])
            {
                parents[x] = Find(parents[x]);
            }
            return parents[x];
        }

        void Union(int x, int y)
        {
            int px = Find(x);
            int py = Find(y);
            if(px != py)
                parents[py] = px;
        }

    private:
        vector<int> parents;
        //vector<int> ranks;
    };

    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        UnionFind uf(m*n);
        //vector<vector<int>> visited(m, vector<int>(n, 0));
        int res = 0;
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(grid[i][j] == '1')
                {
                    int id = i*m+j;
                    for(int i=0; i<dx.size(); ++i)
                    {
                        int tx = i + dx[i];
                        int ty = j + dy[i];
                        if(tx<0||ty<0||tx>=grid.size()||ty>=grid[0].size()|| grid[tx][ty] != '1') continue;
                        int id2 = tx*m + ty;
                        uf.Union(id, id2);
                    }
                }
            }
        }

        unordered_set<int> islands;
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(grid[i][j] == '1')
                {
                    int id = i*m+j;
                    islands.insert(uf.Find(id));
                }
            }
        }
        return islands.size();
    }
    vector<int> dx = {-1, 0, 1, 0};
    vector<int> dy = {0, -1, 0, 1};
};
#endif // UNIONFIND_H
