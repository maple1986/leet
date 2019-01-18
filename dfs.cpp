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

    dfs.invertTree226(tree);

    vector<string>::iterator it = res.begin();
    while(it != res.end())
    {
        printf("%s\n", it->c_str());
        ++it;
    }

    vector<vector<char>> image = {{'0','0','1','0'},{'0','1','1','0'},{'0','1','0','0'}};
    dfs.minArea(image, 0, 2);

    vector<pair<string, string>> equations = {{"a","b"},{"b","c"}};
    vector<double> values = {2.0,3.0};
    vector<pair<string, string>> queries = {{"a","c"},{"b","c"},{"a","e"},{"a","a"},{"x","x"}};

    dfs.calcEquation(equations, values, queries);

    vector<vector<int>> relation = {{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}};
    vector<vector<int>> relation1 = {{1,1,0},{1,1,0},{0,0,1}};
    int i = dfs.findCircleNum1(relation);
    i = dfs.numSquares(12);
    vector<vector<int>> matrix = {{9,9,4},{6,6,8},{2,2,1}};
    i = dfs.longestIncreasingPath(matrix);
    vector<int> coins = {3,5,7,8,9,10,11};
    vector<int> coins1 = {1,2,5};
    i = dfs.coinChange(coins1, 11);
    i = dfs.change(11, coins1);
    vector<vector<int>> stones = {{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}};
    i = dfs.removeStones(stones);
    i = 0;
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


