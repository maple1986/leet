#include <vector>
#include <priority_queue>

using namespace std;

vector<int> smallestRange(vector<vector<int>> &nums)
{
    if (nums.empty())
        return {};
    if (nums.size() == 1)
        return {nums[0][0], nums[0][0]};
    int n = nums.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> iter(nums.size(), 0);
    int maxN = INT_MIN;
    for (int i = 0; i < n; ++i)
    {
        if (nums[i].empty())
            return {};
        maxN = max(maxN, nums[i][0]);
        pq.push({nums[i][0], i});
    }
    //vector<int> res({pq.top().first, maxN});
    //int lastPop = pq.top().second;
    int res1 = pq.top().first, res2 = maxN;
    while (true)
    {
        auto cur = pq.top();
        pq.pop();
        lastPop = cur.second;
        iter[lastPos]++;
        if (iter[lastPos] >= nums[lastPos].size())
            break;
        pq.push({nums[iter[lastPos]], lastPos});
        maxN = max(maxN, nums[iter[lastPos]]);
        if (res2 - res1 > maxN - pq.top().first)
        {
            res1 = pq.top().first;
            res2 = maxN;
        }
    }
    return {res1, res2};
}

int consecutiveNumbersSum(int N)
{
    if (N < 2)
        return 1;
    int res = 0, size = 1;
    for (int m = 1;; m++)
    {
        int mx = N - m * (m - 1) / 2;
        if (mx <= 0)
            break;
        if (mx % m == 0)
            res++;
    }
    return res;
}

bool lottery(vector<vector<int>> &lot, vector<int> &lucky)
{
    int n = lot.size(), m = lucky.size();
    if (m < n)
        return false;
}

API : bool hasNext(stream &int_stream);
pair<int, bool> getNext(stream &int_stream);

vector<int> Sampling(stream &int_stream, int n)
{
    vector<int> res(n, 0);
    int badIndex = -1, goodIndex = n, totalBadCnt = 0;
    while (hasNext(int_stream) && goodIndex > 0)
    {
        auto nextInt = getNext(int_stream);
        if (nextInt.second)
        {
            goodIndex-- ； if (goodIndex == badIndex)
            {
                int dropIndex = rand() % (badIndex + 1);
                swap(res[badIndex], res[dropIndex]);
                badIndex--;
            }
            res[goodIndex] = nextInt.first;
        }
        else
        {
            totalBadCnt++;
            if (badIndex + 1 == goodIndex)
            {
                int dropIndex = rand() % (totalBadCnt);
                if (dropIndex <= badIndex)
                {
                    res[dropIndex] = nextInt.first;
                }
            }
            else
                res[++badIndex] = nextInt.first;
        }
    }
    return res;
}

class UnionFind
{
  public:
    UnionFind()
    {
    }

    pair<string, double> Find(string &str)
    {
        if (parents[x].first != x)
        {
            parents[x] = Find(parents[x]);
            value[x] = value[x] * value[parents[x]];
        }
        return parents[x];
    }

    double getValue(string &x)
    {
        if (!dict.count(x))
            return -1.0;
        return value[dict[x]];
    }

    bool Union(string &x, string &y, double v)
    {
        if (!dict.count(x))
        {
            cnt++;
            dict[x] = cnt - 1;
        }
        if (!dict.count(y))
        {
            cnt++;
            dict[y] = cnt - 1;
        }
        int parentX = Find(x);
        int parentY = Find(y);
        if (parentX != parentY)
        {
            parents[parentX] = parentY;
            value[parentX] *= v;
        }
    }

  private:
    unordered_map<string, pair<string, double>> parents;
};

class Solution
{
  public:
    class UnionFind
    {
      public:
        UnionFind()
        {
        }

        pair<string, double> Find(string &str)
        {
            if (!parents.count(str))
            {
                parents[str] = {str, 1.0};
            }
            else if (parents[str].first != str)
            {
                parents[str].first = parents[parents[str].first].first;
                parents[str].second *= parents[parents[str].first].second;
            }
            return parents[str];
        }

        bool Union(string &x, string &y, double v)
        {
            auto parentX = Find(x);
            auto parentY = Find(y);
            if (parentX.first != parentY.first)
            {
                parents[parentX.first].first = parentY.first;
                parents[parentX.first].second *= v;
            }
            return true;
        }
        unordered_map<string, pair<string, double>> parents;
    };

    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double> &values, vector<pair<string, string>> queries)
    {
        if (queries.empty())
            return {};
        UnionFind uf;
        for (int i = 0; i < equations.size(); ++i)
        {
            string a = equations[i].first, b = equations[i].second;
            uf.Union(a, b, values[i]);
        }

        vector<double> res(queries.size(), -1.0);
        for (int i = 0; i < queries.size(); ++i)
        {
            if (!uf.parents.count(queries[i].first) || !uf.parents.count(queries[i].second))
                continue;
            auto parentA = uf.Find(queries[i].first);
            auto parentB = uf.Find(queries[i].second);
            if (parentA.first == parentB.first)
            {
                res[i] = parentA.second / parentB.second;
            }
        }
        for (auto kv : uf.parents)
        {
            cout << kv.first.c_str() << " " << kv.second.first.c_str() << " " << kv.second.second << endl;
        }
        return res;
    }

    class UnionFind
    {
      public:
        UnionFind(int n)
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
            if (px == py)
                return false;
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

    int regionsBySlashes(vector<string> &grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;
        int n = grid.size();
        UnionFind uf(n * n * 4);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                int key = (i*n+j)*4;
                if (grid[i][j] == '/')
                {
                    uf.Union(key, key+3);
                    uf.Union(key+1, key+2);
                }
                else if (grid[i][j] == '\\')
                {
                    uf.Union(key, key+1);
                    uf.Union(key+2, key+3);
                }
                else
                {
                    uf.Union(key, key + 1);
                    uf.Union(key, key + 2);
                    uf.Union(key, key + 3);
                }
                if (i != 0)
                    uf.Union(key, key-n*4+2);
                if (i !=n-1)
                    uf.Union(key + 2, key + n* 4);
                if (j != 0)
                    uf.Union(key + 3, key - 4 + 1);
                if (j != n-1)
                    uf.Union(key + 1, key + 4 + 3);
            }
        //unordered_set<int> res;
        int res = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < 4; ++k)
                {
                    int key = (i*n+j)*4+k;
                    if (uf.Find(key) == key)
                        res++;
                }
        printV(uf.parents);
        return res;
    }


vector<double> calcEquation(const vector<pair<string, string>>& equations, vector<double>& values, const vector<pair<string, string>>& queries) {
  // parents["A"] = {"B", 2.0} -> A = 2.0 * B
  // parents["B"] = {"C", 3.0} -> B = 3.0 * C
  unordered_map<string, pair<string, double>> parents;
 
  for (int i = 0; i < equations.size(); ++i) {
    const string& A = equations[i].first;
    const string& B = equations[i].second;
    const double k = values[i];
    // Neighter is in the forrest
    if (!parents.count(A) && !parents.count(B)) {
      parents[A] = {B, k};
      parents[B] = {B, 1.0};
    } else if (!parents.count(A)) {
      parents[A] = {B, k};
    } else if (!parents.count(B)) {
      parents[B] = {A, 1.0 / k};
    } else {
      auto& rA = find(A, parents);
      auto& rB = find(B, parents);      
      parents[rA.first] = {rB.first, k / rA.second * rB.second};
    }    
  }
 
  vector<double> ans;
  for (const auto& pair : queries) {
    const string& X = pair.first;
    const string& Y = pair.second;
    if (!parents.count(X) || !parents.count(Y)) {
      ans.push_back(-1.0);
      continue;
    }
    auto& rX = find(X, parents); // {rX, X / rX}
    auto& rY = find(Y, parents); // {rY, Y / rY}
    if (rX.first != rY.first)
      ans.push_back(-1.0);
    else // X / Y = (X / rX / (Y / rY))
      ans.push_back(rX.second / rY.second);
  }
  return ans;
}
private:
  pair<string, double>& find(const string& C, unordered_map<string, pair<string, double>>& parents) {
    if (C != parents[C].first) {
      const auto& p = find(parents[C].first, parents);
      parents[C].first = p.first;
      parents[C].second *= p.second;
    }
    return parents[C];
  }


    vector<vector<int>> multiply(vector<vector<int>> &A, vector<vector<int>> &B) {
        // write your code here

    }

    vector<vector<int>> multiply(vector<vector<int>> &A, vector<vector<int>> &B) {
        // write your code here
        if(A.empty()||A[0].empty()||B.empty()||B[0].empty()) return {};
        vector<vector<int>> res(A.size(), vector<int>(B[0].size(), 0));
        for(int i=0; i<A.size(); ++i)
        {
            for(int j=0; j<A[i].size(); ++j)
            {
                if(A[i][j]==0) continue;
                else
                {
                    for(int k=0; k<B[j].size(); ++k)
                        res[i][k] += A[i][j]*B[j][k];
                }
            }
        }
        return res;
    }


    vector<vector<string>> findDuplicate(vector<string>& paths) {
        
    }
};
