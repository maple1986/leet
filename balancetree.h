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
            return doDelete(root);
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

    }

    TreeNode* constructFromPrePostHelper(vector<int>& pre, int& left, vector<int>& post)
    {
        if(left >= pre.size())
        {
            return NULL;
        }
        auto it = std::find(post.begin(), post.end(), pre[left]);
        int mid = distance(it, post.end());
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
};

#endif // BALANCETREE_H
