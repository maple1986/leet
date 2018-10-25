#ifndef DFS_H
#define DFS_H

#include <vector>
#include <queue>
#include <string>
#include <set>
#include <unordered_map>
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
};

#endif // DFS_H
