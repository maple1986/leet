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

    void Union(const pair<int, int> &l, const pair<int, int> &r)
    {

        return;
    }
    pair<int, int> Find(const pair<int, int> &)
    {
    }

    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {
    }

    int numIslands(vector<vector<char>> &grid)
    {
    }
};

class UnionFind2
{
  public:
    UnionFind2(int n)
    {
        parents = vector<int>(n, 0);
        for (int i = 0; i < parents.size(); ++i)
        {
            parents[i] = i;
        }
        ranks = vector<int>(n, 1);
    }

    int Find(int x)
    {
        if (x != parents[x])
        {
            parents[x] = Find(parents[x]);
        }
        return parents[x];
    }

    bool Union(int x, int y)
    {
        int px = Find(x);
        int py = Find(y);
        if(px == py) return false;
        if (px != py)
        {
            if (ranks[px] > ranks[py])
            {
                parents[py] = px;
                ranks[px] += ranks[py];
            }
            else
            {
                parents[px] = py;
                ranks[py] += ranks[px];
            }
        }
        return true;
    }

  private:
    vector<int> parents;
    vector<int> ranks;
};

class UnionFindDirected
{
  public:
    UnionFindDirected(int n)
    {
        parents = vector<int>(n, 0);
        for (int i = 0; i < parents.size(); ++i)
        {
            parents[i] = i;
        }
        ranks = vector<int>(n, 1);
    }

    int Find(int x)
    {
        if (x != parents[x])
        {
            parents[x] = Find(parents[x]);
        }
        return parents[x];
    }

    bool Union(int parent, int child)
    {
        int pparent = Find(parent);
        int pchild  = Find(child);
        if(pparent == pchild) return false;
        parents[pchild] = pparent;
        return true;
        /*
        int px = Find(x);
        int py = Find(y);
        if(px == py) return false;
        if (px != py)
        {
            if (ranks[px] > ranks[py])
            {
                parents[py] = px;
                ranks[px] += ranks[py];
            }
            else
            {
                parents[px] = py;
                ranks[py] += ranks[px];
            }
        }
        return true;
        */
    }

  private:
    vector<int> parents;
    vector<int> ranks;
};


class UnionFindSln
{
  public:
    static void test()
    {
        vector<vector<char>> grid = {{'1'}, {'0'}, {'1'}, {'0'}, {'1'}, {'1'}};
        UnionFindSln uf;
        int i = uf.numIslands(grid);
    }

    int numIslands(vector<vector<char>> &grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;
        int m = grid.size();
        int n = grid[0].size();
        UnionFind2 uf(m * n);
        //vector<vector<int>> visited(m, vector<int>(n, 0));
        int res = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == '1')
                {
                    int id = i * n + j;
                    for (int k = 0; k < 4; ++k)
                    {
                        int tx = i + dx[k];
                        int ty = j + dy[k];
                        if (tx < 0 || ty < 0 || tx >= grid.size() || ty >= grid[0].size() || grid[tx][ty] != '1')
                            continue;
                        int id2 = tx * n + ty;
                        uf.Union(id, id2);
                    }
                }
            }
        }

        unordered_set<int> islands;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == '1')
                {
                    int id = i * n + j;
                    islands.insert(uf.Find(id));
                }
            }
        }
        return islands.size();
    }
    vector<int> dx = {-1, 0, 1, 0};
    vector<int> dy = {0, -1, 0, 1};

    vector<int> findRedundantConnection(vector<vector<int>> &edges)
    {
        UnionFind2 uf(edges.size());
        for(auto& edge: edges)
        {
            int p0 = uf.Find(edge[0]);
            int p1 = uf.Find(edge[1]);
            if(!uf.Union(p0, p1))
                return edge;
        }
        return {};
    }

    vector<int> findRedundantDirectedConnection(vector<vector<int>> &edges)
    {
        UnionFindDirected uf(edges.size());
        for(auto& edge: edges)
        {
            //int p0 = uf.Find(edge[0]);
            //int p1 = uf.Find(edge[1]);
            if(!uf.Union(edge[0], edge[1]))
                return edge;
        }
        return {};
    }
};
#endif // UNIONFIND_H
