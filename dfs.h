#ifndef DFS_H
#define DFS_H

#include <vector>
#include <queue>
#include <string>
#include <set>
#include <unordered_map>
#include <math.h>
#include "balancetree.h"
using namespace std;

class DFS
{
public:
    DFS();
    static void test();
    bool isSameTree(TreeNode* p, TreeNode* q);
    bool isSameTree1(TreeNode* p, TreeNode* q)
    {
        if(!p && !q) return true;
        if(p->val != q->val || (p && !q) || (q && !p))
            return false;
        bool res = isSameTree1(p->left, q->left);
        if(!res)
            return false;
        res = isSameTree1(p->right, q->right);
        if(!res)
            return false;
    }
    /*
    vector<string> binaryTreePaths(TreeNode* root)
    {
        queue<TreeNode*> q;
        vector<string> ret;
        if(!root)
        {
            return ret;
        }
        q.push(root);
        while (!q.empty())
        {
           TreeNode* tmp = q.front();
           q.pop();
           if(tmp->left) q.push(tmp->left);
           if(tmp->right) q.push(tmp->right);
        }

    }
    */
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        if (root == nullptr) return res;
        dfs(root, to_string((long long)root->val), res);
        return res;
    }

    void dfs(TreeNode* root, string path, vector<string>& res) {
        if (root->left == nullptr && root->right == nullptr) {
            res.push_back(path);
        }

        if (root->left != nullptr)
            dfs(root->left, path + "->" + to_string((long long)root->left->val), res);

        if (root->right != nullptr)
            dfs(root->right, path + "->" + to_string((long long)root->right->val), res);
    }

    bool canVisitAllRooms(vector<vector<int>>& rooms)
    {
        set<int> traveled;
        //stack<int> s;
        //for(int i=0; i<rooms.size(); ++i)
        //{
        dfs(rooms, 0, traveled);


        return traveled.size() == rooms.size();
    }

    void dfs(vector<vector<int>>& rooms, int cur, set<int>& traveled)
    {
        if(traveled.count(cur)) return;
        traveled.insert(cur);
        for(int i=0; i<rooms[cur].size(); ++i)
        {
            dfs(rooms, rooms[cur][i], traveled);
        }

    }

    bool findTarget(TreeNode* root, int k)
    {
        if(!root) return false;
        vector<int> nums;
        dfs(root, nums);
        int left = 0, right = nums.size()-1;
        while(left < right)
        {
            int sum = nums[left] + nums[right];
            if(sum > k) right--;
            else if(sum < k) left++;
            else return true;
        }
        return false;
    }

    void dfs(TreeNode* cur, vector<int>& nums)
    {
        if(!cur)return;
        if(cur->left) dfs(cur->left, nums);
        nums.push_back(cur->val);
        if(cur->right) dfs(cur->right, nums);
        return;
    }

    bool findTarget2(TreeNode* root, int k) {
        if (!root) return false;
        unordered_map<int, int> m;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* t = q.front();
            q.pop();
            if (m.count(k - t->val) > 0) return true;
            m[t->val]++;
            if (t->right) q.push(t->right);
            if (t->left) q.push(t->left);
        }
        return false;
    }

    bool findTarget3(TreeNode* root, int k)
    {
        if (!root) return false;
        unordered_map<int, int> m;
        queue<TreeNode*> q;
        q.push(root);
    }

    int maxDepth(NAryNode* root)
    {
        int max_depth = 0;
        int cur = 0;
        dfs(root, cur, max_depth);
        return max_depth;
    }

    void dfs(NAryNode* root, int cur, int& max_depth)
    {
        if(!root) return;
        cur++;
        max_depth = max(cur, max_depth);
        for(int i=0; i<root->children.size(); ++i)
        {
            dfs(root->children[i], cur, max_depth);
        }
    }

    TreeNode* invertTree226(TreeNode* root)
    {
        if(!root) return NULL;
        TreeNode* tmp = root->left;
        if(root->right)
            root->left = invertTree226(root->right);
        else
            root->left = NULL;
        if(tmp)
            root->right = invertTree226(tmp);
        else
            root->right = NULL;
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
    {
        if(preorder.empty()) return NULL;
        TreeNode* root = buildTreeHelper(preorder, inorder, 0, preorder.size()-1, 0, inorder.size()-1);
        return root;
    }

    TreeNode* buildTreeHelper(vector<int>& preorder, vector<int>& inorder, int pre_begin, int pre_end, int in_begin, int in_end)
    {
        if(pre_begin > pre_end || in_begin > in_end)
        {
            return NULL;
        }
        TreeNode* root = new TreeNode(preorder[pre_begin]);
        if(pre_begin == pre_end)
        {
            return root;
        }
        int mid = find(inorder, in_begin, in_end, preorder[pre_begin]);
        int lefttree_size = mid - in_begin;

        root->left = buildTreeHelper(preorder, inorder, pre_begin+1, pre_begin+lefttree_size, in_begin, mid-1);
        root->right = buildTreeHelper(preorder, inorder, pre_begin+1+lefttree_size, pre_end, mid+1, in_end);
        return root;
    }

    int find(vector<int>& v, int start, int end, int target)
    {
        for(; start <= end; ++start)
        {
            if(v[start] == target) break;
        }
        return start;
    }

    TreeNode* buildTree1(vector<int>& inorder, vector<int>& postorder) {
        if(postorder.empty()) return NULL;
        TreeNode* root = buildTreeHelper(postorder, 0, postorder.size(), inorder, 0, inorder.size());
        return root;
    }

    TreeNode* buildTreeHelper(vector<int>& postorder, int postbegin, int postend, vector<int>& inorder, int inorderbegin, int inorederend)
    {
        if(postbegin >= postend || inorderbegin >= inorederend)
        {
            return NULL;
        }
        TreeNode* root = new TreeNode(postorder[postend-1]);
        if(postbegin == postend-1)
        {
            return root;
        }

        auto it = std::find(inorder.begin()+inorderbegin, inorder.begin()+inorederend, postorder[postend-1]);
        if(it == inorder.begin()+inorederend)
        {
            return NULL;
        }
        int leftTreeSize = distance(inorder.begin()+inorderbegin, it);

        root->left =  buildTreeHelper(postorder, postbegin, postbegin+leftTreeSize, inorder, inorderbegin, inorderbegin+leftTreeSize);
        root->right = buildTreeHelper(postorder, postbegin+leftTreeSize, postend-1, inorder, inorderbegin+leftTreeSize+1, inorederend);
        return root;
    }

    int islandPerimeter(vector<vector<int>>& grid)
    {

    }

    unordered_set<string> _visited;
    vector<double> calcEquation(vector<pair<string, string>> equations,\
                                vector<double>& values, vector<pair<string, string>> queries)
    {
        unordered_map<string, vector<pair<string, double>>> graph;
        for(int i=0; i < equations.size(); ++i)
        {
            graph[equations[i].first].push_back(make_pair(equations[i].second, values[i]));
            graph[equations[i].second].push_back(make_pair(equations[i].first, 1.f/values[i]));
        }
        vector<double> res;

        for(const auto& query : queries)
        {
            if(!(graph.count(query.first) && graph.count(query.second)))
            {
                res.push_back(-1.f);
                continue;
            }
            _visited.clear();
            double cur = 1.f;
            if(dfs(query.first, query.second, graph, cur))
                res.push_back(cur);
            else res.push_back(-1.f);
        }
        return res;
    }

    bool dfs(string start, string end,\
             unordered_map<string, vector<pair<string, double>>>&graph, double& cur)
    {
        if(start == end)
        {
            return true;
        }
        _visited.insert(start);
        for(auto& v : graph[start])
        {
            if(_visited.count(v.first)) continue;
            cur *= v.second;
            _visited.insert(v.first);
            if(dfs(v.first, end, graph, cur)) return true;
            _visited.erase(v.first);
            cur /= v.second;
        }
        return false;
    }

    int coinChange(vector<int>& coins, int amount)
    {
        sort(coins.rbegin(), coins.rend());
        int best = INT_MAX;
        dfs(coins, 0, 0, amount, best);
        return best;
    }

    void dfs(vector<int>& coins, int start, int cur, int rest_amount, int& best)
    {
        /*
        if(cur >= best)
        {
            return;
        }
        if(start == coins.size())
        {
            if(rest_amount)
            {
                return;
            }
            else
            {
                best = min(best, cur);
                return;
            }
        }
        if(rest_amount%coins[start] == 0)
        {
            cur += rest_amount/coins[start];
            best = min(best, cur);
            return;
        }

        for(int i = rest_amount/coins[start]; )
        */
    }

    int minArea(vector<vector<char>> &image, int x, int y) {
        int x0 = x, x1 = x, y0 = y, y1 = y;
        dfs(image, x, y, x0, x1, y0, y1);
        return (x1-x0+1)*(y1-y0+1);
    }

    void dfs(vector<vector<char>> &image, int x, int y, int& x0, int& x1, int& y0, int& y1)
    {
        if(x < 0 || x >= image.size() || y < 0 || y >= image[0].size())
        {
            return;
        }
        if(image[x][y] != '1')
        {
            return;
        }
        image[x][y] = '2';
        x0 = min(x0, x);
        y0 = min(y0, y);
        x1 = max(x1, x);
        y1 = max(y1, y);

        dfs(image, x-1, y, x0, x1, y0, y1);
        dfs(image, x+1, y, x0, x1, y0, y1);
        dfs(image, x, y-1, x0, x1, y0, y1);
        dfs(image, x, y+1, x0, x1, y0, y1);
    }

    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        if(1 == n) return n;
        int res = 0;
        unordered_set<int> seen;
        for(int i=0; i<n; ++i)
        {
            if(seen.count(i))
            {
                continue;
            }
            seen.insert(i);
            dfs(M, i, n, seen);
            res++;
        }
        return res;
    }

    void dfs(vector<vector<int>>& M, int i, int n, unordered_set<int>& seen)
    {
        if(i < 0 || i >= n)
        {
            return;
        }
        for(int j=0; j<n; ++j)
        {
            if(M[i][j] == 1)
            {
                seen.insert(j);
                dfs(M, j, n, seen);
            }
        }
        return;
    }

    int findCircleNum1(vector<vector<int>>& M)
    {
        int n = M.size();
        if( 1 == n ) return 1;
        int res = 0;
        for(int i=0; i<n; ++i)
        {
            if(_seen.count(i)) continue;
            dfs(M, i, n);
            res++;
        }
        return res;
    }

    void dfs(vector<vector<int> > &M, int i, int n)
    {
        for(int j=0; j<n; ++j)
        {
            if(j == i) continue;
            if(_seen.count(j)) continue;
            if(M[i][j] == 1)
            {
                _seen.insert(j);
                dfs(M, j, n);
            }
        }
        return;
    }

    unordered_set<int> _seen;

    vector<string> binaryTreePaths3(TreeNode* root)
    {
        vector<string> res;
        if(!root) return res;
        string prefix = to_string(root->val);
        dfs(prefix, root->left, res);
        dfs(prefix, root->right, res);
        return res;
    }

    void dfs(string& prefix, TreeNode* node, vector<string>& res)
    {
        if(!node) return;
        if(!node->left && !node->right)
        {
            res.push_back(prefix+"->"+to_string(node->val));
            return;
        }
        int pos = prefix.length();
        prefix = prefix + "->"+to_string(node->val);
        dfs(prefix, node->left, res);
        dfs(prefix, node->right, res);
        prefix = prefix.substr(0, pos-1);
    }

    void binaryTreePaths(TreeNode* root, string s, vector<string>& res) {

        if (!root)
            return;

        if (!s.empty())
            s += "->";

        s += to_string(root->val);

        if (!root->left && !root->right) {
            res.push_back(s);
            return;
        }

        binaryTreePaths(root->left, s, res);
        binaryTreePaths(root->right, s, res);
    }

    vector<string> binaryTreePaths2(TreeNode* root) {
        vector<string> res;
        binaryTreePaths(root, "", res);
        return res;
    }

    int numSquares(int n) {
        int maxN = sqrt(n);
        int res  = n;
        int cur  = 0;
        dfs(maxN, n, cur, res);
        return res;
    }

    void dfs(int maxN, int target, int& cur, int& res)
    {
        if(target == 0)
        {
            res = min(cur, res);
            return;
        }
        for(int i= maxN; i>=1; --i)
        {
            if(target - maxN*maxN < 0) continue;
            target = target - maxN*maxN;
            ++cur;
            dfs(maxN, target, cur, res);
            --cur;
            target += maxN*maxN;
        }
    }

    int numSquares_bfs(int n)
    {

    }

    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K)
    {
        for(const auto& flight : flights)
        {
            _flightGraph[flight[0]].emplace_back(flight[1], flight[2]);
        }
        _findCheapestPriceVisited.assign(n, 0);
        int res = INT_MAX;
        _findCheapestPriceVisited[src] = 1;
        dfs(src, dst, 0, K+1, res);
        return res==INT_MAX?-1:res;
    }

    void dfs(int cur, int dst, int cost, int remainSteps, int& minCost)
    {
        if(cur == dst)
        {
            minCost = min(minCost, cost);
            return;
        }
        if(remainSteps == 0) return;

        for(const auto& e: _flightGraph[cur])
        {
            int next = e.first;
            int nextCost = e.second;
            if(cost + nextCost > minCost) continue;
            if(_findCheapestPriceVisited[next]) continue;
            _findCheapestPriceVisited[next] = 1;
            dfs(next, dst, cost+nextCost, remainSteps-1, minCost);
            _findCheapestPriceVisited[next] = 0;
        }
    }
    unordered_map<int, vector<pair<int, int>>> _flightGraph;
    vector<int> _findCheapestPriceVisited;

    int maxVacationDays(vector<vector<int>> &flights, vector<vector<int>> &days) {
        // Write your code here
        for(int i=0; i<flights.size(); ++i)
        {
            for(int j=0; j<flights[i].size(); ++j)
            {
                if(flights[i][j] == 1)
                {
                    _flights[i].emplace_back(j);
                }
            }
        }
        int res = 0;
        int cur = 0;
        dfs(0, 0, days, cur, res);
        for(int dst : _flights[0])
        {
            cur += days[dst][0];
            dfs(dst, 1, days, cur, res);
            cur -= days[dst][0];
        }
        return res;
    }

    void dfs(int start, int week, vector<vector<int>>& days, int cur, int& res)
    {
        if(week == days[0].size())
        {
            res = max(res, cur);
            return;
        }
        cur += days[start][week];
        dfs(start, week+1, days, cur, res);
        cur -= days[start][week];
        for(int dst : _flights[start])
        {
            cur += days[dst][week];
            dfs(dst, week+1, days, cur, res);
            cur -= days[dst][week];
        }
        return;
    }

    unordered_map<int, vector<int>> _flights;
    vector<vector<int>> _mem;

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        _mem.assign(matrix.size(), vector<int>(matrix[0].size(), 0));
        int res = 1;
        for(int i=0; i<matrix.size(); ++i)
        {
            for(int j=0; j<matrix[0].size(); ++j)
            {
                int cur = dfs1(matrix, i, j);
                res = max(res, cur);
            }
        }
        return res;
    }

    int dfs1(vector<vector<int>>& matrix, int x, int y)
    {
        if(x<0||x>=matrix.size()||y<0||y>=matrix[0].size())
        {
            return 0;
        }
        if(_mem[x][y] > 0) return _mem[x][y];
        /*
        if(matrix[x][y] <= matrix[x+1][y] && matrix[x][y] <= matrix[x-1][y] && matrix[x][y] <= matrix[x][y-1] && matrix[x][y] <= matrix[x][y+1])
        {
            return 1;
        }
        */
        int ans = 1;
        if(x+1<matrix.size() && matrix[x][y] > matrix[x+1][y])
            ans = max(ans, dfs1(matrix, x+1, y)+1);
        if(x-1 >=0 &&matrix[x][y] > matrix[x-1][y])
            ans = max(ans, dfs1(matrix, x-1, y)+1);
        if(y-1 >=0 &&matrix[x][y] > matrix[x][y-1])
            ans = max(ans, dfs1(matrix, x, y-1)+1);
        if(y+1 <matrix[0].size() &&matrix[x][y] > matrix[x][y+1])
            ans = max(ans, dfs1(matrix, x, y+1)+1);
        _mem[x][y] = ans;
        return ans;
    }

    //vector<vector<int>> _mem;

    vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        if (maze.empty() || maze[0].empty()) return true;
        int m = maze.size(), n = maze[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return helper(maze, dp, start[0], start[1], destination[0], destination[1]);
    }
    bool helper(vector<vector<int>>& maze, vector<vector<int>>& dp, int i, int j, int di, int dj) {
        if (i == di && j == dj) return true;
        if (dp[i][j] != -1) return dp[i][j];
        bool res = false;
        int m = maze.size(), n = maze[0].size();
        maze[i][j] = -1;
        for (auto dir : dirs) {
            int x = i, y = j;
            while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] != 1) {
                x += dir[0]; y += dir[1];
            }
            x -= dir[0]; y -= dir[1];
            if (maze[x][y] != -1) {
                res |= helper(maze, dp, x, y, di, dj);
            }
        }
        dp[i][j] = res;
        return res;
    }

    bool validTree(int n, vector<vector<int>> &edges) {
        if(edges.empty() && n == 1) return true;
        if(edges.empty()) return false;
        unordered_map<int, vector<int>> _graph;
        for(auto& edge : edges)
        {
            _graph[edge[0]].push_back(edge[1]);
            _graph[edge[1]].push_back(edge[0]);
        }
        for(int i=1; i<=n; ++i)
        {
            if(!_graph.count(i)) return false;
        }
        vector<int> visited(n, 0);
        dfs(_graph, 1, visited);
    }

    void dfs(unordered_map<int, vector<int>>& graph, int cur, vector<int>& visited)
    {

    }
};

#endif // DFS_H
