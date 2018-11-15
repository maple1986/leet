#ifndef BALANCETREE_H
#define BALANCETREE_H
/******************************************
 * Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

    a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example 1:

Given the following tree [3,9,20,null,null,15,7]:

    3
   / \
  9  20
    /  \
   15   7

Return true.

Example 2:

Given the following tree [1,2,2,3,3,null,null,4,4]:

       1
      / \
     2   2
    / \
   3   3
  / \
 4   4

Return false.

******************************************
Given a binary tree and a sum, determine if the tree has a root-to-leaf
path such that adding up all the values along the path equals the given sum.

Note: A leaf is a node with no children.

Example:

Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \      \
7    2      1

return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.


Divide this problem to three same problem, and solve it recursively.
For the present node root, we can visit it or not, which means the path start with root or not.
Further, it is find the path start with root, find the path start with root->left, and find the path start with root->right.
Then we have to write a func dfs to calculate the path number start with node root.
Finally we solve the above three problems recursively.

class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        int num=0;
        dfs(root, sum, num);
        if(root) {
            num += pathSum(root->left, sum)+pathSum(root->right, sum);
        }
        return num;
    }

    void dfs(TreeNode* root, int sum, int& num) {
        if(!root) return;
        if(root->val==sum) ++num;
        dfs(root->left, sum-root->val, num);
        dfs(root->right, sum-root->val, num);
    }
};




 * ****************************************/
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
};

struct StringTreeNode {
    string val;
    StringTreeNode *brother;
    StringTreeNode *child;
    StringTreeNode(string x) : val(x), brother(nullptr), child(nullptr) {}
};

class NAryNode {
public:
    int val;
    vector<NAryNode*> children;

    NAryNode() {}

    NAryNode(int _val, vector<NAryNode*> _children) {
        val = _val;
        children = _children;
    }
};

class BalanceTree
{
public:
    BalanceTree();

    static void test();

    TreeNode* generateTree(char* input);


    bool isBalanced(TreeNode* root);
    int treeHight(TreeNode* root, bool& result);

    int minDepth(TreeNode* root);
    bool SumPath(TreeNode* root, int sum);
    int  SumPathIII(TreeNode* root, int sum);
    bool isSymmetric(TreeNode* root);
    vector<vector<int>> levelOrderBottom(TreeNode* root);
    vector<vector<int>> levelOrderBottom1(TreeNode* root);
    int ladderLength(string beginWord, string endWord, vector<string>& wordList);
    int ladderLength1(string beginWord, string endWord, vector<string>& wordList);
    vector<vector<string> > findLadders(string beginWord, string endWord, vector<string>& wordList);
    vector<vector<string> > findLadders2(string beginWord, string endWord, vector<string>& wordList);
private:
    int WordGap(string &left, string &right);
    StringTreeNode* generateTree(string beginWord, vector<string>& wordList);
    int bfsForlength(queue<string> &qs, int& step, vector<string>& wordList, vector<int>& visited, int flag);

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

    int getMinimumDifference(TreeNode* root)
    {
        if(!root) return 0;
        vector<int> nums;
        inorder(root, nums);
        int min_diff = INT_MAX;
        for(int i=0; i<nums.size()-1; ++i)
        {
            min_diff = min(min_diff, abs(nums[i] - nums[i+1]));
        }
        return min_diff;
    }

    void inorder(TreeNode* root, vector<int>& nums)
    {
        if(!root) return;
        if(root->left) inorder(root->left, nums);
        nums.push_back(root->val);
        if(root->right) inorder(root->right, nums);
    }

    TreeNode* deleteNode(TreeNode* root, int key)
    {
        if(root->val == key)
        {
            return NULL;//doDelete(root);
        }
        else if(root->val > key)
        {
            root->left = deleteNode(root->left, key);
        }
        else// if(root->val < key)
        {
            root->right = deleteNode(root->right, key);
        }
    }
/*
    TreeNode* doDelete(TreeNode* root)
    {
        if(isLeaf(root))
        {
            return NULL;
        }
        else if(leftOnly(root))
        {
            return root->left;
        }
        else if(RightOnly(root))
        {
            return root->right;
        }
        else //Both childrens
        {
            TreeNode* toDel = root;
            root = root->right;
            TreeNode* pre = root->right;
            while(root->left)
            {
                pre  = root;
                root = root->left;
            }
            pre->left = NULL;
            return;
        }
*/
    vector<double> averageOfLevels(TreeNode* root)
    {
        vector<double> res;
        if(!root) return res;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            int size = q.size();
            double avg=0;

            for(int i=0; i<size; ++i)
            {
                TreeNode* tmp = q.front();
                q.pop();
                avg+=(tmp->val-avg)/size;
                if(tmp->left) q.push(tmp->left);
                if(tmp->right) q.push(tmp->right);
            }
            res.push_back(avg);
        }
        return res;
    }


    TreeNode* pruneTree1(TreeNode* root)
    {
        if(!root) return NULL;
        if(containingall0s(root->left) && containingall0s(root->right) && root->val == 0)
        {
            return NULL;
        }
        pruneTree1(root->left);
        pruneTree1(root->right);
        return root;
    }

    bool containingall0s(TreeNode* root)
    {

    }
    TreeNode* pruneTree2(TreeNode* root){
        return go(root) ? root : nullptr;
    }
    int go(TreeNode* node){
        if (node==nullptr) return 0;
        int l=go(node->left),r=go(node->right);
        if (l==0) node->left=nullptr;
        if (r==0) node->right=nullptr;
        return l+r+node->val;
    }

    TreeNode* pruneTree3(TreeNode* root) {
        if (!root) return NULL;
        root->left = pruneTree3(root->left);
        root->right = pruneTree3(root->right);
        if (!root->left && !root->right && root->val == 0) return NULL;
        return root;
    }

    TreeNode* constructMaximumBinaryTree(vector<int>& nums)
    {
        if(nums.empty()) return NULL;
        return constructMaximumHelper(nums, 0, nums.size()-1);
    }
    TreeNode* constructMaximumHelper(vector<int>& nums, int begin, int end)
    {
        if(begin > end)
        {
            return NULL;
        }
        else if(begin == end)
        {
            return new TreeNode(nums[begin]);
        }
        int index = max_elementIndex(nums, begin, end);
        TreeNode* root = new TreeNode(nums[index]);
        root->left = constructMaximumHelper(nums, begin, index-1);
        root->right = constructMaximumHelper(nums, index+1, end);
        return root;
    }

    int max_elementIndex(vector<int>& nums, int begin, int end)
    {
        int index = begin;
        int maxnum= nums[begin];
        for(; begin <= end; ++begin)
        {
            if(nums[begin] > maxnum)
            {
                index = begin;
                maxnum= nums[begin];
            }
        }
        return index;
    }


    TreeNode* constructMaximumBinaryTree1(vector<int>& nums)
    {
        if(nums.empty()) return NULL;
        return constructMaximumHelper1(nums, 0, nums.size()-1);
    }
    TreeNode* constructMaximumHelper1(vector<int>& nums, int begin, int end)
    {
        if(begin > end)
        {
            return NULL;
        }
        else if(begin == end)
        {
            return new TreeNode(nums[begin]);
        }
        auto it = max_element(nums.begin()+begin, nums.begin()+end+1);
        TreeNode* root = new TreeNode(*it);
        root->left = constructMaximumHelper1(nums, begin, distance(nums.begin(), it)-1);
        root->right = constructMaximumHelper1(nums, distance(nums.begin(), it)+1, end);
        return root;
    }
    TreeNode* constructMaximumBinaryTree2(vector<int>& nums)
    {
        vector<TreeNode *> stks;
        for (auto& num : nums) {
            TreeNode * node = new TreeNode(num);
            while (!stks.empty() && stks.back()->val < num) {
                node->left = stks.back();
                stks.pop_back();
            }
            if (!stks.empty()) {
                stks.back()->right = node;
            }
            stks.push_back(node);
        }
        return stks[0];
    }

    TreeNode* insertIntoBST(TreeNode* root, int val)
    {
        if(!root) return new TreeNode(val);
        if(root->val == val) return root;
        if(root->val > val)
        {
            root->left = insertIntoBST(root->left, val);
            return root;
        }
        if(root->val < val)
        {
            root->right = insertIntoBST(root->right, val);
            return root;
        }
    }

    TreeNode* insertIntoBST2(TreeNode* root, int val) {
        TreeNode* prev = root;
        TreeNode* tmp = root;
        while (root!=NULL){
            if (root->val < val){
              prev = root;
              root = root->right;
            }else{
                prev = root;
                root = root->left;
            }
        }
        TreeNode *root1 = new TreeNode(val);
        root1->val = val;
        root1->right = NULL;
        root1->left = NULL;
        if (prev->val < val) prev->right = root1;
        else prev->left = root1;
        return tmp;
    }

    vector<int> largestValues(TreeNode* root)
    {
        if(!root) return {};
        vector<int> res;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            int size = q.size();
            int maxInRow = q.front()->val;
            for(int i=0; i<size; ++i)
            {
                TreeNode* cur = q.front();
                maxInRow = max(maxInRow, cur->val);
                q.pop();
                //Insert Children
                if(cur->left)
                    q.push(cur->left);
                if(cur->right)
                    q.push(cur->right);
            }
            res.push_back(maxInRow);
        }
        return res;
    }


    int leftmostValues(TreeNode* root)
    {
        int res = 0;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            int size = q.size();
            res = q.front()->val;
            for(int i=0; i<size; ++i)
            {
                TreeNode* cur = q.front();
                q.pop();
                //Insert Children
                if(cur->left)
                    q.push(cur->left);
                if(cur->right)
                    q.push(cur->right);
            }
        }
        return res;
    }

    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post)
    {
        int n = pre.size();
        if(0 == n) return NULL;
        vector<TreeNode*> treenodes;
        treenodes.push_back(new TreeNode(pre[0]));
        for(int i=1, j=pre.size()-2; i<pre.size(); ++i)
        {
            TreeNode* tmp = new TreeNode[pre[i]];
            while(pre[i] == post[j])
            {
                i++;
                j--;
            }

        }
        return NULL;
    }


    TreeNode* constructFromPrePost2(vector<int>& pre, vector<int>& post)
    {

    }

    TreeNode* constructFromPrePostHelper(vector<int>& pre, int& left, vector<int>& post)
    {
        if(left >= pre.size())
        {
            return NULL;
        }


        TreeNode* root = new TreeNode(pre[left]);
        /*
        if(pre[left] == post[right])
        {
            root = new TreeNode(pre[left]);
            left++;
            right--;
            constructFromPrePostHelper(pre, left, post, right);
        }
        */
        //else
        //{

        //}
        return NULL;
    }

    vector<vector<int>> pathSumII(TreeNode* root, int sum)
    {
        vector<vector<int>> res;
        if(!root) return res;
        stack<TreeNode*> stk;
        stk.push(root);
        vector<int> path;
        while(!stk.empty())
        {
            TreeNode* pCur = stk.top();
            stk.pop();
            path.push_back(pCur->val);
            sum -= pCur->val;
            if(!pCur->left && !pCur->right)
            {
                if(0 == sum)
                {
                    res.push_back(path);
                }
                sum += pCur->val;
                path.pop_back();
            }
            if(pCur->left) stk.push(pCur->left);
            if(pCur->right) stk.push(pCur->right);
        }
        return res;
    }

    vector<vector<int>> pathSumIIrec(TreeNode* root, int sum)
    {
        vector<vector<int>> res;
        vector<int> path;
        dfs(root, sum, path, res);
        return res;
    }

    void dfs(TreeNode* root, int sum, vector<int>& path, vector<vector<int>>& res)
    {
        if(!root) return;
        path.push_back(root->val);
        if(!root->left && !root->right && root->val == sum)
        {
            res.push_back(path);
            path.pop_back();
            return;
        }
        dfs(root->left, sum-root->val, path, res);
        dfs(root->right, sum-root->val, path, res);
        path.pop_back();
    }
    /*
    int pathSumIII(TreeNode* root, int sum) {
        if(!root) return 0;
        int num=0;
        pathSumIII_dfs(root, sum, num);
        num += pathSumIII_dfs(root->left, sum)+pathSumIII_dfs(root->right, sum);
        return num;
    }

    void pathSumIII_dfs(TreeNode* root, int sum, int& num) {
        if(!root) return;
        if(root->val==sum) ++num;
        dfs(root->left, sum-root->val, num);
        dfs(root->right, sum-root->val, num);
    }
    */

    int kthSmallest(TreeNode* root, int k)
    {
        int lchild_count = NumofChildren(root->left);
        if(lchild_count >= k)
        {
            return kthSmallest(root->left, k);
        }
        else if(lchild_count+1 < k)
        {
            return kthSmallest(root->right, k-lchild_count-1);
        }
        return root->val;
    }

    int NumofChildren(TreeNode* root)
    {
        if(!root) return 0;
        return NumofChildren(root->left)+NumofChildren(root->right)+1;
    }

    TreeNode* addOneRow(TreeNode* root, int v, int d)
    {
        if(!root) return NULL;
        //root is leaf
        if(d == 1)
        {
            TreeNode* newRoot = new TreeNode(v);
            newRoot->left = root;
            return newRoot;
        }
        int depth = 1;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            int size = q.size();
            if(depth == d-1)
            {
                for(int i=0; i<size; ++i)
                {
                    TreeNode* cur = q.front();
                    q.pop();
                    TreeNode* left_node = new TreeNode(v);
                    TreeNode* right_node = new TreeNode(v);
                    TreeNode* tmp = cur->left;
                    cur->left = left_node;
                    left_node->left = tmp;

                    tmp = cur->right;
                    cur->right = right_node;
                    right_node->right = tmp;
                }
                break;
            }
            else
            {
                for(int i=0; i<size; ++i)
                {
                    TreeNode* cur = q.front();
                    q.pop();
                    if(cur->left) q.push(cur->left);
                    if(cur->right) q.push(cur->right);
                }
            }
            depth++;
        }
        return root;
    }

    vector<int> rightSideView(TreeNode* root)
    {
        if(!root) return {};
        queue<TreeNode*> q;
        q.push(root);
        vector<int> res;
        while(!q.empty())
        {
            int size = q.size();
            for(int i=0; i<size; ++i)
            {
                TreeNode* cur = q.front();
                q.pop();
                if(i == size-1)
                {
                    res.push_back(cur->val);
                }
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
        }
        return res;
    }


    vector<int> rightSideView2(TreeNode* root) {
        /*if (NULL == root)
            return vector<int>();
        TreeNode* curr = root;
        vector<int> result;
        result.push_back(root->val);
        TreeNode* temp = root->left;
        while(curr)
        {
            if (curr->right)
            {
                curr = curr->right;
                result.push_back(curr->val);
                if (curr->left)
                    temp = curr->left;
                else
                {
                    if (temp->right)
                        temp = temp->right;
                    else if (temp->left)
                        temp = temp->left;
                    else
                        temp = NULL;
                }
            }
            else
            {
                if (temp)
                    result.push_back(temp->val);
                curr = temp;
            }
        }

        return result;*/
        vector<int> result;
        int level = 1;
        findrightmost(root, level, result);
        return result;
    }

    void findrightmost(TreeNode* root, int level, vector<int>& result)
    {
        if (NULL == root)
            return;
        if (result.size() < level)
            result.push_back(root->val);
        findrightmost(root->right, level+1, result);
        findrightmost(root->left, level+1, result);
    }

    vector<int> distanceK(TreeNode* root, TreeNode* target, int K)
    {
        vector<int> res;
        if(K == 0)
        {
            res.push_back(target->val);
            return res;
        }
        map<TreeNode*, vector<TreeNode*>> graph;
        gernerateGraph(root, graph);
        unordered_set<TreeNode*> visited;

        queue<TreeNode*> q;
        int depth = 0;
        q.push(target);
        visited.insert(target);
        while(!q.empty())
        {
            int size = q.size();
            for(int i=0; i<size; ++i)
            {
                TreeNode* cur = q.front();
                q.pop();
                for(auto con : graph[cur])
                {
                    if(visited.count(con))
                    {
                        continue;
                    }
                    else
                    {
                        visited.insert(con);
                        q.push(con);
                    }
                }
            }
            depth++;
            if(depth == K)
            {
                size = q.size();
                for(int i=0; i < size; ++i)
                {
                    TreeNode* cur = q.front();
                    q.pop();
                    res.push_back(cur->val);
                }
                break;
            }
        }
        return res;
    }

    void gernerateGraph(TreeNode* root, map<TreeNode*, vector<TreeNode*>>& graph)
    {
        if(!root) return;
        if(root->left)
        {
            graph[root].push_back(root->left);
            graph[root->left].push_back(root);
        }
        if(root->right)
        {
            graph[root].push_back(root->right);
            graph[root->right].push_back(root);
        }
        gernerateGraph(root->left, graph);
        gernerateGraph(root->right, graph);
    }

    void flatten(TreeNode* root)
    {
        /*
        if(!root) return NULL;
        if(!root->left)
        {
            flatten(root->right);
        }
        else if(!root->right)
        {
            root->right = root->left;
            root->left = NULL;
            flatten(root->right);
        }
        else // left and right
        {

        }
        */
    }

    TreeNode* flatten_helper(TreeNode* root)
    {
        if(!root) return NULL;

    }

    int SumOfNode(TreeNode* root)
    {
        if(!root) return 0;
        int cur = 0;
        int total = 0;
        dfs_SumOfNode(root, cur, total);
        return total;
    }

    void dfs_SumOfNode(TreeNode* root, int cur, int& total)
    {
        if(!root) return;
        if(!root->left && !root->right)
        {
            total = total + cur + root->val;
        }
        cur += root->val;


    }

    vector<int> postorderTraversal(TreeNode* root)
    {

    }

    vector<int> findFrequentTreeSum(TreeNode* root) {
        map<TreeNode*, int> m;
        map<int, vector<TreeNode*>> sums;
        TreeSum(root, m, sums);
        vector<int> res;
        int mostFrequent = 0;
        for(auto it : sums)
        {
            int size = it.second.size();
            if(size > mostFrequent)
            {
                mostFrequent = size;
                res.clear();
                res.push_back(it.first);
            }
            else if( size == mostFrequent)
            {
                res.push_back(it.first);
            }
        }
        return res;
    }


    int TreeSum(TreeNode* root, map<TreeNode*, int>& m, map<int, vector<TreeNode*>>& sums)
    {
        if(!root) return 0;
        if(m.count(root)) return m[root];
        int sum = root->val + TreeSum(root->left, m, sums) + TreeSum(root->right, m, sums);
        sums[sum].push_back(root);
        return sum;
    }

/*
    vector<int> findFrequentTreeSum2(TreeNode* root) {
        vector<int> res;
        unordered_map<int, int> m;
        int cnt = 0;
        postorder(root, m, cnt, res);
        return res;
    }
    int postorder(TreeNode* node, unordered_map<int, int>& m, int& cnt, vector<int>& res) {
        if (!node) return 0;
        int left = postorder(node->left, m, cnt, res);
        int right = postorder(node->right, m, cnt, res);
        int sum = left + right + node->val;
        ++m[sum];
        if (m[sum] >= cnt) {
            if (m[sum] > cnt) res.clear();
            res.push_back(sum);
            cnt = m[sum];
        }
        return sum;
    }
*/
    int sumNumbers(TreeNode* root)
    {
        if(!root) return 0;
        int presum = 0, total = 0;
        dfs_sumNumbers(root, presum, total);
        return total;
    }

    void dfs_sumNumbers(TreeNode* root, int presum, int& total)
    {
        if(!root) return;
        presum = presum*10 + root->val;
        if(!root->left && !root->right)
        {
            total += presum;
            return;
        }
        //presum = presum*10 + root->val;
        if(root->left)
        {
            dfs_sumNumbers(root->left, presum, total);
        }
        if(root->right)
        {
            dfs_sumNumbers(root->right, presum, total);
        }
        return;
    }

    int sumNumbers_useString(TreeNode* root)
    {
        if(!root) return 0;
        int res = 0;
        dfs_sumNumbers2(root, "", res);
        return res;
    }

    void dfs_sumNumbers2(TreeNode* root, string s, int& res)
    {
        if(!root) return;
        s += to_string(root->val);
        if(!root->left && !root->right)
        {
            res += stoi(s);
            return;
        }
        if(root->left) dfs_sumNumbers2(root->left, s, res);
        if(root->right) dfs_sumNumbers2(root->right, s, res);
    }

    int widthOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        queue<pair<TreeNode*, int>> q;
        q.push(make_pair(root, 1));
        int max_wid = 1;
        while(!q.empty())
        {
            int size = q.size();
            int cur_wid  = 0;
            int start_index = 0;
            int end_index = 0;
            for(int i=0; i<size; ++i)
            {
                pair<TreeNode*, int> tmp = q.front();
                q.pop();
                if(i == 0)
                {
                    start_index = tmp.second;
                    cur_wid = 1;
                }
                if(i == size-1)
                {
                    end_index = tmp.second;
                    cur_wid = end_index - start_index + 1;
                    max_wid = max(max_wid, cur_wid);
                }

                if(tmp.first->left)
                    q.push(make_pair(tmp.first->left, tmp.second*2));
                if(tmp.first->right)
                    q.push(make_pair(tmp.first->right, tmp.second*2+1));
            }
        }
        return max_wid;
    }

    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges)
    {
        if(N == 1) return {0};
        vector<int> res;
        unordered_map<int, vector<int>> graph;
        generateGraph(edges, graph);
        vector<vector<int>> mem(N, vector<int>(N, -1));
        unordered_set<int> visited;
        //dfs(graph, visited, i, mem);
        //accumulate
        return res;
    }

    void generateGraph(vector<vector<int>>& edges, unordered_map<int, vector<int>>& graph)
    {
        for(int i=0; i<edges.size(); ++i)
        {
            graph[i].assign(edges[i].begin(), edges[i].end());
            for(int j : edges[i])
            {
                graph[j].push_back(i);
            }
        }
    }


    void recoverTreeO1(TreeNode* root)
    {
        if(!root) return;
        TreeNode* preNode = NULL;
        TreeNode* first   = NULL;
        TreeNode* second  = NULL;
        inoder(root, preNode, first, second);

        int tmp = first->val;
        second->val = first->val;
        first->val  = tmp;
    }

    void inoder(TreeNode* root, TreeNode*& preNode, TreeNode*& first, TreeNode*& second)
    {
        if(!root) return;
        inoder(root->left, preNode, first, second);
        //do something
        if(preNode && preNode->val > root->val)
        {
            if(!first)
            {
                first = preNode;
            }
            if(first)
            {
                second = root;
            }
        }
        preNode = root;
        inoder(root->right, preNode, first, second);
    }



    void recoverTree(TreeNode* root)
    {
        if(!root) return;
        vector<pair<int, TreeNode*>> vInoder;
        inorder(root, vInoder);
        int disorder_count = 0;
        int pos1 = 0, pos2 = 0;
        for(int i=0; i <vInoder.size()-1; ++i)
        {
            if(vInoder[i].first > vInoder[i+1].first)
            {
                if(disorder_count)
                {
                    pos2 = i;
                }
                else
                {
                    pos1 = i;
                }
                disorder_count++;
            }
        }
        if(disorder_count == 1)
        {
            pos2 = pos1+1;
        }
        else
        {
            pos2++;
        }
        vInoder[pos1].second->val = vInoder[pos2].first;
        vInoder[pos2].second->val = vInoder[pos1].first;
        return;
    }

    void inorder(TreeNode* root, vector<pair<int, TreeNode*>>& v)
    {
        if(!root)
            return;
        inorder(root->left, v);

        v.push_back(make_pair(root->val, root));
        inorder(root->right, v);
    }

    void recoverTree2(TreeNode* root) {
        if (NULL == root)
            return;

        TreeNode* inorder = NULL;
        TreeNode* first = NULL;
        TreeNode* second = NULL;
        findWrong(root, inorder, first, second);

        int fval = first->val;
        first->val = second->val;
        second->val = fval;

    }

    void findWrong(TreeNode* root, TreeNode*& inorder, TreeNode*& first, TreeNode*& second)
    {
        if (NULL == root)
            return;
        findWrong(root->left, inorder, first, second);
        //do something here
        if (first == NULL && inorder != NULL && root->val < inorder->val)
            first = inorder;
        if (first != NULL && inorder != NULL && root->val < inorder->val)
        {
            second = root;
        }
        inorder=root;

        findWrong(root->right, inorder, first, second);

    }

    int longestUnivaluePath(TreeNode* root)
    {
        if(!root) return 0;
        vector<pair<TreeNode*, int>> dp;
        int res = 0;
        dfs(root, dp, res);

        return res;
    }

    void dfs(TreeNode *root, vector<pair<TreeNode*, int>> &dp, int &res)
    {
        int tmp = 0;
        if(!dp.empty() && root->val == dp.back().first->val)
        {
            tmp = dp.back().second+1;
        }
        dp.push_back(make_pair(root, tmp));

        if(!root->left && !root->right)
        {
            for(auto i : dp)
            {
                res = max(res, i.second);
            }
            dp.pop_back();
            return;
        }
        if(root->left) dfs(root->left, dp, res);
        if(root->right) dfs(root->right, dp, res);
        dp.pop_back();
        return;
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges)
    {
        unordered_map<int, vector<int>> graph;
        generateGraph(edges, graph);
    }

};

#endif // BALANCETREE_H
