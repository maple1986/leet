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

    int maxVacationDays2(vector<vector<int>> &flights, vector<vector<int>> &days) {
        // Write your code here
        N_ = flights.size();
        K_ = days[0].size();

        for(int i=0; i<N_; ++i)
        {
            _flights[i].emplace_back(i);
            for(int j=0; j<N_; ++j)
            {
                if(flights[i][j] == 1)
                {
                    _flights[i].emplace_back(j);
                }
            }
        }
        memo_ = vector<vector<int>>(N_, vector<int>(K_, -1));
        int res = 0;
        //int cur = 0;
        //dfs(0, 0, days, cur, res);
        //for(int dst : _flights[0])
        //{
        res = maxVacationDaysHelper(0, 0, days);
        return res;
        //}
        //return res;
    }

    int maxVacationDaysHelper(int start, int week, vector<vector<int>>& days)
    {
        if(week == K_)
        {
            return 0;
        }
        if(memo_[start][week] >= 0) return memo_[start][week];
        int maxD = 0;
        for(int dst : _flights[start])
        {
            maxD = max(maxD, maxVacationDaysHelper(dst, week+1, days)+days[dst][week]);
        }
        memo_[start][week] = maxD;
        Utils::printVV(memo_);
        return maxD;
    }

    int maxVacationDays3(vector<vector<int>> &flights, vector<vector<int>> &days) {
        // Write your code here
        int N = flights.size();
        int K = days[0].size();
        vector<vector<int>> dp(N, vector<int>(K, -1));
        for(int i=0; i<N; ++i)
            dp[i][K-1] = days[i][K-1];
        Utils::printVV(dp);
        for(int j=K-2; j>=0; --j)
            for(int i=0; i<N; ++i){
                for(int f=0; f<N; ++f)
                {
                    if(flights[i][f] || f == i)
                    {
                        dp[i][j] = max(dp[i][j], dp[f][j+1]+days[i][j]);
                        Utils::printVV(dp);
                    }
                }
            }
        Utils::printVV(dp);
        int res = 0;
        for(int i=0; i<N; ++i)
        {
            if(i == 0 || flights[0][i])
                res = max(res, dp[0][i]);
        }
        return res;
    }

    unordered_map<int, vector<int>> _flights;
    vector<vector<int>> memo_;
    int N_;
    int K_;

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
        vector<vector<int>> graph(n);
        for(auto& edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        unordered_set<int> visited;
        bool res = dfs1(graph, -1, 0, visited);
        /*
        for(int i=1; i<=n; ++i)
        {
            if(visited.count(i)) continue;

        }
        */
        return res && visited.size() == n;
    }

    bool dfs1(vector<vector<int>>& graph, int pre, int cur, unordered_set<int>& visited)
    {
        if(visited.count(cur)) return false;
        visited.insert(cur);
        for(int i :graph[cur])
        {
            if(i == pre) continue;
            if(!dfs1(graph, cur, i, visited)) return false;
        }
        return true;
    }

    vector<string> wordBreak2(string s, vector<string>& wordDict) {
        unordered_set<string> wordSearch(wordDict.begin(), wordDict.end());
        //wordSearch[""] = {""};
        return wordBreak(s, wordSearch);
    }

    vector<string> wordBreak(string s, unordered_set<string>& wordSearch) {
        if(_mem1.count(s)) return _mem1[s];
        vector<string> res;
        for(int i = 0; i<s.size(); ++i)
        {
            string left = s.substr(0, i);
            string right = s.substr(i);
            if(wordSearch.count(right))
            {
                vector<string> tmp = wordBreak(left, wordSearch);
                if(!tmp.empty())
                {
                    for(string & str: tmp)
                    {
                        str += " " + right;
                    }
                    res.insert(res.end(), tmp.begin(), tmp.end());
                }
            }
        }
        _mem1[s].swap(res);
        return _mem1[s];
    }

    unordered_map<string, vector<string>> _mem1;

    int change2(int amount, vector<int>& coins) {
        if(amount == 0) return 0;
        int res = 0;
        sort(coins.begin(), coins.end());
        vector<int> cur;
        vector<vector<int>> total;
        dfs1(coins, 0, 0, amount, res, cur, total);
        return res;
    }

    void dfs1(vector<int>& coins, int start, int sub, int amount, int& res, vector<int>& cur, vector<vector<int>>& total)
    {
        if(sub > amount) return;
        if(sub == amount)
        {
            res++;
            total.push_back(cur);
            return;
        }
        for(int i=start; i<coins.size(); ++i)
        {
            cur.push_back(coins[i]);
            dfs1(coins, i, sub+coins[i], amount, res, cur, total);
            cur.pop_back();
        }
        return;
    }

    int coinChange2(vector<int>& coins, int amount) {
        if(amount = 0) return 1;
        if(coins.empty()) return -1;
        sort(coins.rbegin(), coins.rend());
        int res = INT_MAX;
        dfs(coins, 0, 0, amount, 0, res);
        return res == INT_MAX?-1:res;
    }

    void dfs(vector<int>& coins, int start, int sub, int amount, int cur, int& res)
    {
        if(sub > amount) return;
        if(cur >= res) return;
        if(amount == sub)
        {
            res = min(res, cur);
            return;
        }
        for(int i=start; i<coins.size(); ++i)
        {
            dfs(coins, i, sub+coins[i], amount, cur+1, res);
        }
        return;
    }

    int coinChange3(vector<int>& coins, int amount) {
        if(amount == 0) return 0;
        if(coins.empty()) return -1;
        sort(coins.rbegin(), coins.rend());
        int res = INT_MAX;
        dfs2(coins, 0, amount, 0, res);
        return res == INT_MAX?-1:res;
    }

    void dfs2(vector<int>& coins, int start, int amount, int cur, int& res)
    {
        if(amount == 0)
        {
            res = min(res, cur);
            return;
        }
        if(start>=coins.size()) return;
        if(0 > amount) return;
        if(cur >= res) return;
        for(int i=start; i<coins.size(); ++i)
        {
            int k = amount/coins[i];
            for(int j=k; j>=0; --j)
            {
                dfs2(coins, i+1, amount-coins[i]*j, cur+j, res);
            }
        }
        return;
    }

    int change(int amount, vector<int>& coins) {
        if(amount == 0) return 1;
        sort(coins.begin(), coins.end());
        vector<vector<int>> mem(amount+1, vector<int>(coins.size(), -1));
        //mem[0][] = 1;
        return count(coins, 0, amount, mem);
        //return res;
    }

    int count(vector<int>& coins, int start, int amount, vector<vector<int>>& mem)
    {

        if(amount < 0) return 0;
        if(0 == amount)
        {
            return 1;
        }
        if(start >= coins.size())
        {
            return 0;
        }
        if(mem[amount][start] != -1) return mem[amount][start];
        int cnt = 0;
        for(int i=start; i<coins.size(); ++i)
        {
            if(coins[i] > amount) break;
            int k = amount/coins[i];

            while(k)
            {
                cnt += count(coins, i+1, amount-k*coins[i], mem);
                k--;
            }

        }
        mem[amount][start] = cnt;
        return mem[amount][start];
    }

    int numberOfPatterns1(int m, int n) {
        vector<vector<int>> dp(10, vector<int>(10, 0));
        int sum = 0;
        for(int i=1; i<=9; ++i)
        {
            dp[i][i] = 1;
            if(m == 1) sum += 9;
        }
        for(int i=2; i<=n; ++i)
        {


            for(int i=1; i<=9; ++i)
            {
                for(int j=i; j<=9; ++j)
                {
                    sum += dp[i][j];
                }
            }
        }


        return sum;
    }


    void wallsAndGates(vector<vector<int>>& rooms) {
        for (int i = 0; i < rooms.size(); ++i) {
            for (int j = 0; j < rooms[i].size(); ++j) {
                if (rooms[i][j] == 0) dfs(rooms, i, j, 0);
            }
        }
    }
    void dfs(vector<vector<int>>& rooms, int i, int j, int val) {
        if (i < 0 || i >= rooms.size() || j < 0 || j >= rooms[i].size() || rooms[i][j] < val) return;
        rooms[i][j] = val;
        dfs(rooms, i + 1, j, val + 1);
        dfs(rooms, i - 1, j, val + 1);
        dfs(rooms, i, j + 1, val + 1);
        dfs(rooms, i, j - 1, val + 1);
    }

    int minTotalDistance(vector<vector<int>>& grid)
    {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(); int n = grid[0].size();
        vector<int> rows, cols;
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(grid[i][j] == 1)
                {
                    rows.push_back(i);
                    cols.push_back(j);
                }
            }
        }
        if(cols.empty()) return 0;
        sort(cols.begin(), cols.end());
        int l=0, r=rows.size()-1;
        int sum = 0;
        while(l<r)
        {
            sum += rows[r--] - rows[l++];
            sum += cols[r--] - cols[l++];
        }
        return sum;
    }

    void solve(vector<vector<char> >& board) {
        if(board.empty() || board[0].empty()) return;
        int m = board.size(); int n = board[0].size();
        for(int i=0; i<board[0].size(); ++i)
        {
            if(board[0][i] == 'O')
            {
                dfs(board, 0, i);
            }
            if(board[m-1][i] == 'O')
            {
                dfs(board, m-1, i);
            }
        }
        for(int i=1; i<m-1; ++i)
        {
            if(board[i][0] == 'O')
            {
                dfs(board, i, 0);
            }
            if(board[i][n-1] == 'O')
            {
                dfs(board, i, n-1);
            }
        }
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(board[i][j] == 'O')
                    board[i][j] = 'X';
                if(board[i][j] == '$')
                    board[i][j] = 'O';
            }
        }
        return;
    }

    void dfs(vector<vector<char> >& board, int i, int j)
    {
        if(i<0 || j<0 || i>=board.size() || j>=board[0].size()) return;
        if(board[i][j] != 'O') return;
        board[i][j] = '$';
        dfs(board, i + 1, j);
        dfs(board, i - 1, j);
        dfs(board, i, j + 1);
        dfs(board, i, j - 1);
    }

    int shortestDistance(vector<vector<int>> &grid) {
        // write your code here
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(); int n = grid[0].size();
        vector<pair<int, int>> houses;
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(grid[i][j] == 1)
                {
                    houses.push_back({i, j});
                }
            }
        }
        int res = INT_MAX;
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(grid[i][j] == 0)
                {
                    int sum = 0;
                    for(auto& h: houses)
                    {
                        sum += calcDistance(h.first, h.second, i, j);
                    }
                    res = min(res, sum);
                }
            }
        }
        return res == INT_MAX?-1: res;
    }
    int calcDistance(int dx, int dy, int sx, int sy)
    {
        return abs(dy-sy)+abs(dx-sx);
    }

    int shortestDistance2(vector<vector<int>> &grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(); int n = grid[0].size();
        vector<int> rows(n, 0);
        vector<int> cols(m, 0);
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(grid[i][j] == 1)
                {
                    rows[i] = rows[i-1]+1;
                    cols[i] = cols[j-1]+1;
                }
                else
                {
                    rows[i] = rows[i-1];
                    cols[i] = cols[j-1];
                }
            }
        }
        int res = INT_MAX;
        for(int i=0; i<m; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(grid[i][j] == 0)
                {
                    int temp = calcDistance(rows, cols, i, j);
                    res = min(res, temp);
                }
            }
        }
        return res == INT_MAX?-1: res;
    }
    int calcDistance(vector<int>& rows, vector<int>& cols, int x, int y)
    {
        return 0;
    }

    int removeStones(vector<vector<int>>& stones) {
        if(stones.size() <= 1) return 0;
        int n = stones.size();
        vector<int> visited(n, 0);
        unordered_map<int, vector<int>> rows;
        unordered_map<int, vector<int>> cols;
        for(int i=0; i<stones.size(); ++i)
        {
            rows[stones[i][0]].push_back(i);
            cols[stones[i][1]].push_back(i);
        }
        int components = 0;
        for(int i=0; i<stones.size(); ++i)
        {
            if(visited[i]) continue;
            dfs(stones, i, rows, cols, visited);
            components++;
        }
        return n-components;
    }

    void dfs(vector<vector<int>>& stones, int i, unordered_map<int, vector<int>>& rows, unordered_map<int, vector<int>>& cols, vector<int>& visited)
    {
        if(visited[i]) return;
        visited[i] = 1;
        int x = stones[i][0];
        int y = stones[i][1];
        for(int j=0; j<rows[x].size(); ++j)
        {
            dfs(stones, rows[x][j], rows, cols, visited);
            //visited[rows[x][j]] = 1;
        }
        for(int j=0; j<cols[y].size(); ++j)
        {
            dfs(stones, cols[y][j], rows, cols, visited);
            //visited[cols[y][j]] = 1;
        }
        return;
    }
    
    int swimInWater(vector<vector<int>>& grid) {
        int N = grid.size();
        if(grid[0][0] == N*N-1 || grid[N-1][N-1] == N*N-1)
            return N*N-1;
        int l = 0, r = N*N;
        while(l < r)
        {
            int mid = l+(r-l)/2;

            vector<vector<int>> visited(N, vector<int>(N, 0));
            bool canSwin = dfs(0, 0, mid, grid, visited);
            if(canSwin)
            {
                r = mid;
            }
            else
            {
                l = mid+1;
            }
        }
        return l;
    }

    bool dfs(int x, int y, int h, vector<vector<int>>& grid, vector<vector<int>>& visited)
    {
        if(x<0 || y<0 || x>=grid.size() || y>= grid.size() || visited[x][y])
            return false;
        if(grid[x][y] < h) return false;
        if(x == grid.size()-1 && y == grid.size()-1) return true;
        visited[x][y] = 1;
        return dfs(x-1, y, h, grid, visited) || dfs(x+1, y, h, grid, visited) || dfs(x, y-1, h, grid, visited) || dfs(x, y+1, h, grid, visited);
    }

    vector<vector<int>> magicSquare(int n) {
        // Write your code here
    }

    bool compute24(vector<double> &nums) {
        // write your code here
        if(nums.size() != 4) return false;
        return dfs(nums);
    }

    bool dfs(vector<double> &nums)
    {
        if(nums.size() == 1)
        {
            if(nums[0]-24.0<1e-6) return true;
            else return false;
        }
        vector<double> temp(nums);
        for(int i=0; i<temp.size(); ++i)
        {
            temp = nums;
            int a = nums[i];
            temp.erase(temp.begin()+i);
            for(int j=i+1; j<temp.size(); ++j)
            {
                int b = nums[j];
                nums.erase(nums.begin()+j);
                double sum = nums[i]+nums[j];
                nums.push_back(sum);
                if(dfs(nums)) return true;
                nums.pop_back();

                double diff = nums[i]-nums[j];
                nums.push_back(diff);
                if(dfs(nums)) return true;
                nums.pop_back();

                diff = -diff;
                nums.push_back(diff);
                if(dfs(nums)) return true;
                nums.pop_back();

                if(nums[i] != 0)
                {
                    double quot = nums[j]/nums[i];
                    nums.push_back(quot);
                    if(dfs(nums)) return true;
                    nums.pop_back();
                }
                
                if(nums[j] != 0)
                {
                    double quot = nums[i]/nums[j];
                    nums.push_back(quot);
                    if(dfs(nums)) return true;
                    nums.pop_back();
                }
            }
        }
        nums.swap(temp);
        return false;
    }

    int numberOfPatterns(int m, int n) {
        vector<bool> visited(10, false);
        vector<vector<int>> jumps(10, vector<int>(10, 0));
        jumps[1][3] = jumps[3][1] = 2;
        jumps[4][6] = jumps[6][4] = 5;
        jumps[7][9] = jumps[9][7] = 8;
        jumps[1][7] = jumps[7][1] = 4;
        jumps[2][8] = jumps[8][2] = 5;
        jumps[3][9] = jumps[9][3] = 6;
        jumps[1][9] = jumps[9][1] = jumps[3][7] = jumps[7][3] = 5;
        int res = 0, cnt = 0;
        dfs(1, 1, m, n, visited, jumps, cnt);
        res = 4*cnt;
        cnt = 0;
        dfs(2, 1, m, n, visited, jumps, cnt);
        res += 4*cnt;
        cnt = 0;
        dfs(5, 1, m, n, visited, jumps, cnt);
        res += cnt;
        return res;
    }

    void dfs(int start, int step, int m, int n, vector<bool>& visited, vector<vector<int>>& jumps, int& res)
    {
        if(step >= m && step <= n)
        {
            res++;
        }
        if(step > n)
            return;
        visited[start] = true;
        for(int i=1; i<=9; ++i)
        {
            if(visited[i]) continue;
            if(jumps[start][i] != 0 && !visited[jumps[start][i]]) continue;
            dfs(i, step+1, m, n, visited, jumps, res);
        }
        visited[start] = false;
        return;
    }


         int dfs(vector<vector<int>>& skip, int visited, int cur, int m, int n) {
            if (n == 0) return 1;
            int res = (m <= 0);

            visited |= (1 << cur);

            for (int i = 1; i <= 9; ++i) {
                // If visited[i] is not visited and (two numbers are adjacent or skip number is already visited)
                if (!(visited & (1 << i)) && (skip[cur][i] == 0 || (visited & (1 << skip[cur][i])))) {
                    res += dfs(skip, visited, i, m-1, n-1);
                }
            }
            return res;
        }
        int numberOfPatterns2(int m, int n) {
            vector<vector<int>> skip(10,vector<int>(10,0));
            skip[1][3] = skip[3][1] = 2;
            skip[1][7] = skip[7][1] = 4;
            skip[3][9] = skip[9][3] = 6;
            skip[7][9] = skip[9][7] = 8;
            skip[1][9] = skip[9][1] = skip[2][8] = skip[8][2] = skip[3][7] = skip[7][3] = skip[4][6] = skip[6][4] = 5;

            int res = 0;
            res += dfs(skip, 0, 1, m-1, n-1)*4; // 1, 3, 7, 9 are symmetric
            res += dfs(skip, 0, 2, m-1, n-1)*4; // 2, 4, 6, 8 are symmetric
            res += dfs(skip, 0, 5, m-1, n-1); // 5

            return res;
        }
};

#endif // DFS_H
