#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

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

    int getrank(int x)
    {
        int px = Find(x);
        return ranks[px];
    }

  private:
    vector<int> parents;
    vector<int> ranks;
};

class UnionFind3
{
  public:
    UnionFind3(int n)
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

    int Find(const string& str)
    {
        if(!dict.count(str))
            dict[str] = maxId++;
        int id = dict[str];
        return Find(id);
    }

    bool Union(int x, int y)
    {
        int px = Find(x);
        int py = Find(y);
        if(px == py) return false;
        parents[py] = px;
        ranks[px] += ranks[py];    
        return true;
    }

    int getrank(int x)
    {
        int px = Find(x);
        return ranks[px];
    }

  private:
    vector<int> parents;
    vector<int> ranks;
    unordered_map<string, int> dict;
    int maxId;
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
        vector<vector<int>> edges = {{2,1},{3,1},{4,2},{1,4}};
        vector<int> j = uf.findRedundantDirectedConnection(edges);
        vector<int> row = {0, 2, 1, 3};
        i = uf.minSwapsCouples(row);
        vector<Point> op = {{1,1},{0,1},{3,3},{3,4}};
        uf.numIslands2(4, 5, op);
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
    //[[2,1],[3,1],[4,2],[1,4]]
    vector<int> findRedundantDirectedConnection(vector<vector<int>> &edges)
    {
        UnionFindDirected uf(edges.size()+1);
        for(auto& edge: edges)
        {
            //int p0 = uf.Find(edge[0]);
            //int p1 = uf.Find(edge[1]);
            if(!uf.Union(edge[0], edge[1]))
                return edge;
        }
        return {};
    }

    int removeStones(vector<vector<int>>& stones) {
        //unordered_map<int, pair<int, int>> rows;
        //unordered_map<int, pair<int, int>> cols;
        UnionFind2 uf(20000);
        for(auto& stone: stones)
        {
            int x = stone[0];
            int y = stone[1];
            uf.Union(stone[0], stone[1]+10000);
            /*
            int id = x*10000+y;
            if(!rows.count(x))
                rows[x] = {x, y};
            else
            {
                int id2 = rows[x].first*10000+rows[x].second;
                uf.Union(id, id2);
            }
            if(!cols.count(y))
                cols[y] = {x, y};
            {
                int id2 = cols[x].first*10000+cols[x].second;
                uf.Union(id, id2);
            }
            */
        }
        unordered_set<int> roots;
        for(auto& stone: stones)
        {
            /*
            int x = stone[0];
            int y = stone[1];
            int id = x*10000+y;
            */
            roots.insert(uf.Find(stone[0]));
        }
        return stones.size()-roots.size();
    }

    int minSwapsCouples(vector<int>& row) {
        int n = row.size();
        UnionFind2 uf(n);
        for(int i=0; i<n; i+=2)
        {
            int first = row[i];
            int second = row[i+1];
            uf.Union(first, second);
            if(first&1)
                uf.Union(first, first-1);
            else
                uf.Union(first, first+1);
            if(second&1)
                uf.Union(second, second-1);
            else
                uf.Union(second, second+1);
        }
        int res = 0;
        unordered_set<int> seen;
        for(int i=0; i<n; i++)
        {
            int px = uf.Find(row[i]);
            if(seen.count(px)) continue;
            seen.insert(px);
            int rank = uf.getrank(px);
            if(rank != 2)
            {
                res += rank/2-1;
            }
        }
        return res;
    }

    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {
        unordered_map<string, int> emailToId;
        unordered_map<int, string> emailToUser;
        int id = 0;
        for(auto & a: accounts)
        {
            for(int i=1; i<a.size(); ++i)
            {
                if(!emailToId.count(a[i]))
                {
                    emailToId[a[i]] = id++;
                }
                emailToUser[emailToId[a[i]]] = a[0];
            }
        }
        UnionFind2 uf(id);
        for(auto & a: accounts)
        {
            for(int i=2; i<a.size(); ++i)
            {
                uf.Union(emailToId[a[i]], emailToId[a[i-1]]);
            }
        }
        unordered_map<int, set<string>> res;
        for(auto & a: accounts)
        {
            for(int i=1; i<a.size(); ++i)
            {
                int curId = uf.Find(emailToId[a[i]]);
                //res[curId].push_back(a[i]);
                if(res.count(curId))
                    res[curId].insert(a[i]);
                else
                {
                    res[curId].insert(emailToUser[curId]);
                    res[curId].insert(a[i]);
                }
            }
        }
        vector<vector<string>> res2;
        for(auto& g: res)
        {
            //vector<string> res3(g.second);
            //res2.emplace_back(vector<string>(g.second));
        }
        return res2;
    }

    int Find(vector<int>& parents, int x)
    {
        if(x != parents[x])
        {
            parents[x] = Find(parents, parents[x]);
        }
        return parents[x];
    }

    int getAns(vector<vector<int>> &mp) {
        // Write your code here.
        if(mp.empty() || mp[0].empty()) return 0;
        int m = mp.size(), n = mp[0].size();
        vector<int> parents(m+n, 0);
        for(int i=0; i<parents.size(); ++i)
            parents[i] = i;
        int res = 0;
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(mp[i][j] == 1)
                {
                    int pi = Find(parents, i);
                    int pj = Find(parents, j+m);
                    if(pi != pj) parents[pj] = pi;
                    res++;
                }
            }
        }
        unordered_set<int> roots;
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(mp[i][j] == 1)
                {
                    roots.insert(Find(parents, i));
                }
            }
        }
        return res-roots.size();
    }

    struct Point {
        int x;
        int y;
        Point() : x(0), y(0) {}
        Point(int a, int b) : x(a), y(b) {}
    };

    vector<int> numIslands2(int n, int m, vector<Point> &operators) {
        // write your code here
        //int m = r, n = c;
        int k = operators.size();
        if(m == 0 || n == 0) return vector<int>(k, 0);
        vector<vector<int>> grid(n, vector<int>(m, 0));
        UnionFind2 uf(n*m);
        int cnt = 0;
        vector<int> res;
        for(int i=0; i<operators.size(); ++i)
        {
            int x = operators[i].x;
            int y = operators[i].y;
            grid[x][y] = 1;
            cnt++;
            unordered_set<int> seen;
            for(int j=0; j<4; ++j)
            {
                int tx = x + dx[i];
                int ty = y + dy[i];
                if(tx < 0 || tx >= n || ty<0 || ty >=m || grid[tx][ty] != 1) continue;
                //seen.insert(uf.Find(tx*m+ty));
                int pa = uf.Find(x*m+y);
                int pb = uf.Find(tx*m+ty);
                if(pa != pb)
                {
                    uf.Union(pa, pb);
                    cnt--;
                }

            }
            //for(int label: seen)
            //    uf.Union(label, x*m+y);
            //cnt -= seen.size();
            res.push_back(cnt);
        }
        return res;
    }

    bool isSentenceSimilarity(vector<string> &words1, vector<string> &words2, vector<vector<string>> &pairs) {
        if(words1.size() != words2.size()) return false;
        if(words1.empty()) return true;
        int n = words1.size();
        unordered_map<string, set<int>> ids;
        int id = 0;
        for(auto& p: pairs)
        {
            ids[p[0]].insert(id);
            ids[p[1]].insert(id);
            id++;
        }
        for(int i=0; i<words1.size(); ++i)
        {
            if(words1[i] == words2[i]) continue;
            if(!ids.count(words1[i]) || !ids.count(words2[i]))
                return false;
            vector<int> c;
            set_intersection(ids[words1[i]].begin(), ids[words1[i]].end(), ids[words2[i]].begin(), ids[words1[i]].end(), back_inserter(c));
            if(c.empty())
                return false;
        }
        return true;
    }

    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        if(words1.size() != words2.size()) return false;
        if(words1.empty()) return true;
        int n = words1.size();
        int id = 0;
        UnionFind3 uf(pairs.size()*2+1);
        //int id = 0;
        for(auto& p: pairs)
        {
            int p0 = uf.Find(p.first);
            int p1 = uf.Find(p.second);
            uf.Union(p0, p1);
        }

        for(int i=0; i<n; ++i)
        {
            string& l = words1[i];
            string& r = words2[i];
            if(l == r) continue;
            if(uf.Find(l) != uf.Find(r))
                return false;
        }

        return true;
    }
};
#endif // UNIONFIND_H
