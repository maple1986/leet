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

};

#endif // DFS_H
