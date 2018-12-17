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
#include <sstream>
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
        if(0 == n) return nullptr;
        for(int i=0; i<post.size(); ++i)
        {
            _postIndex[post[i]] = i;
        }
        return constructFromPrePostHelper(pre, 0, pre.size()-1, post, 0, post.size()-1);
    }

    TreeNode* constructFromPrePostHelper(vector<int>& pre,int preStart,int preEnd,vector<int>& post, int postStart, int postEnd)
    {
        if(preStart > preEnd) return NULL;
        TreeNode* root = new TreeNode(pre[preStart]);
        if(preStart == preEnd) return root;
        int leftRootIndex = _postIndex[pre[preStart+1]];
        int leftTreeLen   = leftRootIndex - postStart + 1;
        root->left = constructFromPrePostHelper(pre, preStart+1, preStart+leftTreeLen, post, postStart, leftRootIndex);
        root->right= constructFromPrePostHelper(pre, preStart+leftTreeLen+1, preEnd, post, leftRootIndex+1, postEnd-1);;
        return root;
    }

    unordered_map<int, int> _postIndex;

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

    int longestUnivaluePath2(TreeNode* root)
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

    TreeNode* increasingBST(TreeNode* root)
    {
        TreeNode dummy(0);
        TreeNode* preNode = &dummy;
        inorder(root, preNode);
        return dummy.right;
    }

    void inorder(TreeNode* root, TreeNode*& preNode)
    {
        if(!root)
        {
            return;
        }
        inorder(root->left, preNode);
        root->left = NULL;
        preNode->right = root;
        preNode = root;
        inorder(root->right, preNode);
    }
    class Employee {
    public:
        // It's the unique ID of each node.
        // unique id of this employee
        int id;
        // the importance value of this employee
        int importance;
        // the id of direct subordinates
        vector<int> subordinates;
    };

    int getImportance(vector<Employee*> employees, int id)
    {
        unordered_map<int, Employee*> mappingTable;
        for(auto employee : employees)
        {
            mappingTable[employee->id] = employee;
        }
        return getScore(id, mappingTable);
    }

    int getScore(int id, unordered_map<int, Employee*>& mappingTable)
    {
        Employee* cur = mappingTable[id];
        if(!cur)
        {
            return 0;
        }
        int curScore = cur->importance;
        for(auto sub : cur->subordinates)
        {
            curScore += getScore(sub, mappingTable);
        }
        return curScore;
    }
/*
    vector<string> binaryTreePaths(TreeNode* root)
    {
        if(!root) return vector<string>("");
        if(!root->left && !root->right) return vector<string>(1, to_string(root->val));
        vector<string> left_res = binaryTreePaths(root->left);
        vector<string> right_res = binaryTreePaths(root->right);
        for(auto & str : left_res)
        {
            str = to_string(root->val) + "->" + str;
        }
        for(auto & str : right_res)
        {
            str = to_string(root->val) + "->" + str;
        }

    }
*/

    vector<string> binaryTreePaths1(TreeNode* root)
    {

    }

    int numIslands(vector<vector<char>>& grid)
    {
        int n = grid.size();
        if(0 == n) return 0;
        int m = grid[0].size();
        if(0 == m) return 0;
        int res = 0;
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<m; ++j)
            {
                if(grid[i][j] != '1')
                {
                    continue;
                }
                else
                {
                    dfs(grid, i, j, m, n);
                    res++;
                }
            }
        }
        return res;
    }

    vector<int> row =    {0, -1, 0, 1};
    vector<int> column = {-1, 0, 1, 0};

    void dfs(vector<vector<char>>& grid, int i, int j, int m, int n)
    {
        if(i < 0 || i >= n || j < 0 || j >= m || grid[i][j] != '1')
        {
            return;
        }
        grid[i][j] = '2';
        for(int k=0; k<4; ++k)
        {
            dfs(grid, i+row[k], j+column[k], m, n);
        }
        return;
    }

    int maxAreaOfIsland(vector<vector<int>>& grid)
    {
        int n = grid.size();
        if(0 == n) return 0;
        int m = grid[0].size();
        if(0 == m) return 0;
        int res = 0;
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<m; ++j)
            {
                if(grid[i][j] != 1)
                {
                    continue;
                }
                else
                {
                    int cur = 1;
                    dfs(grid, i, j, m, n, cur);
                    res = max(res, cur);
                }
            }
        }
        return res;
    }


    void dfs(vector<vector<int>>& grid, int i, int j, int m, int n, int cur)
    {
        if(i < 0 || i >= n || j < 0 || j >= m || grid[i][j] != 1)
        {
            return;
        }
        grid[i][j] = 2;
        for(int k=0; k<4; ++k)
        {
            dfs(grid, i+row[k], j+column[k], m, n, cur+1);
        }
        return;
    }

    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix)
    {
        int n = matrix.size();
        if(0 == n) return matrix;
        int m = matrix[0].size();
        if(0 == m) return matrix;
        vector<vector<int>> visited(n, vector<int>(m, 0));
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<m; ++j)
            {
                if(visited[i][j])
                {
                    continue;
                }
                visited[i][j] = 1;
                if(matrix[i][j] != 1)
                {
                    continue;
                }
                else
                {
                    int distance = dfs(matrix, i, j, m, n, visited);
                    matrix[i][j] = distance;
                }
            }
        }
        return matrix;
    }


    int dfs(vector<vector<int>>& matrix, int i, int j, int m, int n, vector<vector<int>>& visited)
    {
        if(i < 0 || i >= n || j < 0 || j >= m)
        {
            return 0;
        }
        if(matrix[i][j] == 0)
        {
            return 1;
        }
        int min_distance  = INT_MAX;
        for(int k=0; k<4; ++k)
        {
            min_distance = min(min_distance, dfs(matrix, i+row[k], j+column[k], m, n, visited));
        }
        return min_distance;
    }

    vector<vector<int>> updateMatrix2(vector<vector<int>>& matrix)
    {

    }

    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        return isMirror(root->left, root->right);
    }

    bool isMirror(TreeNode* root1, TreeNode* root2)
    {
        if(!root1 && !root2) return true;
        if(!root1 || !root2) return false;
        return root1->val == root2->val && isMirror(root1->left, root2->right) && isMirror(root1->right, root2->left);
    }

    vector<int> boundaryOfBinaryTree(TreeNode* root)
    {
    }

    vector<vector<int>> verticalOrder(TreeNode* root)
    {
        vector<vector<int>> res;
        if(!root) return res;
        map<int, vector<int>> m;
        queue<pair<TreeNode*, int>> q;
        q.push(make_pair(root, 0));
        while (!q.empty())
        {
            auto a = q.front();
            q.pop();
            TreeNode* curNode = a.first;
            m[a.second].push_back(curNode->val);
            if(curNode->left) q.push(make_pair(curNode, a.second-1));
            if(curNode->left) q.push(make_pair(curNode, a.second+1));
        }
        for(const auto& item : m)
        {
            res.push_back(item.second);
        }
        return res;
    }

    int longestConsecutive(TreeNode * root)
    {
        if(!root) return 0;
        int res = 1;
        dfs(root, root->val, 1, res);
        return res;
    }

    void dfs(TreeNode *root, int pValue, int cur, int &res)
    {
        if(!root) return;
        if(root->val == pValue+1) cur++;
        else cur = 1;
        res = max(cur, res);
        dfs(root->left, root->val, cur, res);
        dfs(root->right, root->val, cur, res);
    }

    int longestUnivaluePath(TreeNode* root)
    {
        if(!root) return 0;
        vector<pair<TreeNode*, int>> dp;
        int res = 0;
        dfs(root, dp, res);

        return res;
    }

    void dfs1(TreeNode *root, vector<pair<TreeNode*, int>> &dp, int &res)
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


    int ans = 0;

    int longestUnivaluePath1(TreeNode* root) {
        lup(root);
        return ans;
    }

    int lup(TreeNode* cur){
        if(!cur) return 0;
        int left, right, L = 0, R = 0;
        left = lup(cur->left);
        right = lup(cur->right);
        if(cur->left!=NULL&&cur->val==cur->left->val){
            L = left + 1;
        }
        if(cur->right!=NULL&&cur->val==cur->right->val){
            R = right + 1;
        }
        ans = max(ans,L+R);
        return max(L,R);
    }

    int longestUnivaluePath3(TreeNode* root) {
         if (!root) return 0;
         int res = 0;
         helper(root, res);
         return res;
     }
     int helper(TreeNode* node, int& res) {
         if (!node) return 0;
         int left = helper(node->left, res);
         int right = helper(node->right, res);
         left = (node->left && node->val == node->left->val) ? left + 1 : 0;
         right = (node->right && node->val == node->right->val) ? right + 1 : 0;
         res = max(res, left + right);
         return max(left, right);
     }

     bool isValidBST1(TreeNode* root) {
         if(!root) return true;
         return isValidBST_Rec(root->left, NULL, root) && isValidBST_Rec(root->right, root, NULL);
     }

     bool isValidBST_Rec(TreeNode* root, TreeNode* left_bound, TreeNode* right_bound)
     {
         if(!root) return true;
         if(left_bound && left_bound->val >= root->val)
         {
             return false;
         }
         if(right_bound && right_bound->val <= root->val)
         {
             return false;
         }
         //left_bound = root->left?root->left:NULL;
         //right_bound = root->right?root->right:NULL;
         return isValidBST_Rec(root->left, left_bound, root) && isValidBST_Rec(root->right, root, right_bound);
     }


     bool isValidBST(TreeNode* root)
     {
        if(!root) return true;
        vector<int> nums;
        inorder(root, nums);
        for(int i=0; i<nums.size()-1; ++i)
        {
            if(nums[i] >= nums[i+1])
            {
                return false;
            }
        }
        return true;
     }


     bool isValidBST2(TreeNode* root) {
         if(!root) return true;
         TreeNode* prev = NULL;
         return inorder2(root, prev);
     }

     bool inorder2(TreeNode* node, TreeNode*& prev)
     {
         if(!node) return true;
         if(!inorder2(node->left, prev)) return false;
         if (prev != NULL && prev->val >= node->val) return false;
         prev = node;
         return inorder2(node->right, prev);
     }

     int closestValue(TreeNode * root, double target) {
         int res = root->val;
         while(root)
         {
             if(abs(root->val-target) < abs(res - target))
             {
                 res = root->val;
             }
             root = root->val > target ? root->left : root->right;
         }
         return res;
     }

     vector<int> closestKValues1(TreeNode * root, double target, int k) {
         //vector<int> res;
         vector<int> nums;
         inorder(root, nums);
         priority_queue<pair<double, int>> pq;
         for(auto num : nums)
         {
             if(pq.size() < k)
             {
                pq.push(make_pair(abs(num-target), num));
             }
             else
             {
                 double delta = abs(num-target);
                 if(delta < pq.top().first)
                 {
                     pq.pop();
                     pq.push(make_pair(delta, num));
                 }
             }
         }
         nums.clear();
         while(!pq.empty())
         {
             nums.push_back(pq.top().second);
             pq.pop();
         }
         return nums;
     }

     vector<int> closestKValues2(TreeNode * root, double target, int k)
     {
         vector<int> nums;
         inorder(root, nums);
         auto it = lower_bound(nums.begin(), nums.end(), target);
         int i = distance(nums.begin(), it),  j = i;
         while(k--)
         {

         }
     }
    vector<int> closestKValues(TreeNode * root, double target, int k)
    {
        inorder(root, target, k);
        vector<int> res;
        res.reserve(k);
        while(!_pq.empty())
        {
            res.emplace_back(_pq.top().second);
            _pq.pop();
        }
        return res;
    }

    void inorder(TreeNode* root, double target, int k)
    {
        if(!root) return;
        inorder(root->left, target, k);
        if(_pq.size() < k)
        {
            _pq.push(make_pair(abs(target-root->val), root->val));
        }
        else
        {
            if(_pq.top().first > abs(target-root->val))
            {
                _pq.pop();
                _pq.push(make_pair(abs(target-root->val), root->val));
            }
        }
        inorder(root->right, target, k);
    }

    int diameterOfBinaryTree(TreeNode* root)
    {
        if(!root) return 0;
        diameterOfBinaryTree_rec(root);
        return _diameter-1;
    }

    int diameterOfBinaryTree_rec(TreeNode* root)
    {
        if(!root) return 0;
        int diameter = heightOfTree(root->left) + heightOfTree(root->right) + 1;
        int tmp = max(diameterOfBinaryTree(root->right), diameterOfBinaryTree(root->left));
        int res = max(diameter, tmp);
        _diameter = max(_diameter, res);
        return res;
    }

    int heightOfTree(TreeNode* node)
    {
        if(!node) return 0;
        if(_treehights.count(node))
        {
            return _treehights[node];
        }
        int height = max(heightOfTree(node->left), heightOfTree(node->right))+1;
        _treehights[node] = height;
        return height;
    }

    int _diameter = 0;
    priority_queue<pair<double, int>> _pq;
    unordered_map<TreeNode*, int> _treehights;

    int diameterOfBinaryTree2(TreeNode* root)
    {
        if(!root) return 0;
        int res = 0;
        maxDepth(root, res);
        return res;
    }

    int maxDepth(TreeNode* root, int& res)
    {
        if(!root) return 0;
        if(_treehights.count(root))
        {
            return _treehights[root];
        }
        int left  = maxDepth(root->left, res);
        int right = maxDepth(root->right, res);
        res = max(res, left+right);
        _treehights[root] = max(left, right)+1;
        return _treehights[root];
    }

    vector<int> findMode(TreeNode* root)
    {
        if(!root) return {};
        vector<int> nums, res;
        inorder(root, nums);
        res.push_back(nums[0]);
        int cur = 1, mode = 1;
        for(int i=1; i<nums.size(); ++i)
        {
            if(nums[i] == nums[i-1]) cur++;
            else cur = 1;
            if(cur == mode)
            {
                res.push_back(nums[i]);
            }
            else if( cur > mode)
            {
                mode = cur;
                res.clear();
                res.push_back(nums[i]);
            }
        }
        return res;
    }

    TreeNode* constructFromPrePost1(vector<int>& pre, vector<int>& post)
    {
        int n = pre.size();
        for(int i=0; i<post.size(); ++i)
        {
            _treenode[post[i]] = i;
        }
        return build(pre, post, 0, n-1, n);
    }

    TreeNode* build(vector<int> &pre, vector<int> &post, int preindex, int postindex, int len)
    {
        if(0 == len) return NULL;
        TreeNode* root = new TreeNode(pre[preindex]);
        if(1 == len) return root;
        int index = postindex;
        for(int i=postindex; i>=0; --i)
        {
            if(post[i] == pre[preindex+1])
            {
                index = i;
            }
        }
        int leftlen = postindex - index;
        int rightlen = len - leftlen;
        root->left = build(pre, post, preindex+1, index, leftlen);
        root->right = build(pre, post, preindex+1+leftlen, index+1, rightlen);
        return root;
    }

    TreeNode* build1(vector<int> &pre, vector<int> &post, int preStart, int preEnd, int postStart, int postEnd)
    {
        if(preStart > preEnd) return NULL;
        TreeNode* root = new TreeNode(pre[preStart]);
        if(preEnd == preStart) return root;
        int leftRoot = _treenode[post[preStart+1]];
        int leftlen = leftRoot - postStart + 1;
        //int rightlen = preEnd - preStart - leftlen;
        root->left = build1(pre, post, preStart+1, preStart+leftlen, postStart, leftRoot);
        root->right = build1(pre, post, preStart+leftlen+1, preEnd, leftRoot+1, postEnd);
        return root;
    }

    unordered_map<int, int> _treenode;

    TreeNode *constructFromPrePost3(vector<int> &pre, vector<int> &post)
    {
        if (pre.size() == 0) return nullptr;
        stack<TreeNode *> st;
        TreeNode *root = new TreeNode(pre[0]);
        st.push(root);
        int j = 0;
        TreeNode *node = nullptr;
        for(int i=1;i<=pre.size();++i){
            while (st.top()->val == post[j]) {
                node = st.top();
                st.pop();
                printf("pop %d\n",node->val);
                if(st.empty())
                    return root;
                if (st.top()->left == nullptr) {
                    st.top()->left = node;
                    printf("%d left child is %d\n", st.top()->val, node->val);
                } else {
                    st.top()->right = node;
                    printf("%d right child is %d\n", st.top()->val, node->val);
                }
                j++;
                printf("j: %d\n",j);
            }
            if (i < pre.size()){
                st.push(new TreeNode(pre[i]));
                printf("push %d\n",pre[i]);
            }
        }
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        serialize(root, res);
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }

    void serialize(TreeNode* root, string& str)
    {
        write(root, str);
        if(!root) return;
        serialize(root->left, str);
        serialize(root->right, str);
    }

    TreeNode* deserialize(istringstream& in)
    {
        TreeNode* root = read(in);
        if(!root) return root;
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }

    void write(TreeNode* root, string& str)
    {
        if(!root) str += "# ";
        else str += to_string(root->val) + " ";
        return;
    }

    TreeNode* read(istringstream& in)
    {
        string s;
        in >> s;
        if(s == "#") return NULL;
        else return new TreeNode(stoi(s));
    }

    int longestUnivaluePath(TreeNode* root)
    {
        if(!root) return 0;
        int res = 0;
        dfs(root, INT_MAX, 0, res);
        return res;
    }

    int dfs(TreeNode *root, int pre, int curr, int &res)
    {
        if(!root) return;
        if(pre == root->val) curr++;

        int left  = dfs(root->left, root->val, curr, res);
        int right = dfs(root->right, root->val, curr, res);
        res = max(res, left+right);
        return curr;
    }

};

#endif // BALANCETREE_H
