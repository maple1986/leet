#include "dfs.h"
#include <queue>

DFS::DFS()
{

}

void DFS::test()
{
    DFS dfs;
    char* str = "[3,9,20,null,null,15,7]";
    BalanceTree bt;
    TreeNode* tree = bt.generateTree(str);
    vector<string> res = dfs.binaryTreePaths(tree);

    vector<string>::iterator it = res.begin();
    while(it != res.end())
    {
        printf("%s\n", it->c_str());
        ++it;
    }
}

bool DFS::isSameTree(TreeNode *p, TreeNode *q)
{
    if(!p && !q)
    {
        return true;
    }

    std::queue<TreeNode*> qp;
    std::queue<TreeNode*> qq;
    qp.push(p);
    qq.push(q);
    while(!qp.empty() && !qq.empty())
    {
        TreeNode* tp = qp.front();
        TreeNode* tq = qq.front();
        qp.pop();
        qq.pop();
        if(tp && tq)
        {
            if(tp->val != tq->val) return false;
            qp.push(tp->left);
            qp.push(tp->right);
            qq.push(tq->left);
            qq.push(tq->right);
        }
        else if(!tp && !tq)
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    if(!qp.empty() && !qq.empty())
    {
        return false;
    }

    return true;
    /*
    if(p || q)
    {
        return false;
    }
    */
}


