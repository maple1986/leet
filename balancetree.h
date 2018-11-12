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

};

#endif // BALANCETREE_H
