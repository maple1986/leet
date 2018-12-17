#include "balancetree.h"
#include <algorithm>
#include <iostream>
using namespace std;
BalanceTree::BalanceTree()
{

}

void BalanceTree::test()
{
    char* str = "[3,9,20,null,null,15,7]";
    BalanceTree bt;
    TreeNode* tree = bt.generateTree(str);
    bt.levelOrderBottom(tree);

    string start = "hit";
    string end   = "cog";
    vector<string> vs;
    vs.push_back("hot");
    vs.push_back("dot");
    vs.push_back("dog");
    vs.push_back("log");
    vs.push_back("cog");
    vs.push_back("lot");

    /*
    int length = bt.ladderLength1(start, end, vs);
    cout << "ladder length1 =" << length << endl;

    vector<vector<string> > vvs = bt.findLadders(start, end, vs);
    cout << vvs.size() << endl;
    vector<vector<string> >::iterator it1 = vvs.begin();
    while(it1 != vvs.end())
    {
        auto it2 = it1->begin();
        while(it2 != it1->end())
        {
            cout << (*it2).c_str() << " ";
            it2++;
        }
        it1++;
        cout << endl;
    }
    vector<int> num1({3,2,1,6,0,5});
    TreeNode* t = bt.constructMaximumBinaryTree(num1);
    char* str2 = "[3,1,4,null,2]";
    TreeNode* tree2 = bt.generateTree(str2);
    int i = bt.kthSmallest(tree2, 1);
    //printf("ptr = [%p]", t);
    char* str3 = "[3,5,1,6,2,0,8,null,null,7,4]";
    TreeNode* tree3 = bt.generateTree(str3);
    bt.distanceK(tree3, tree3->left, 2);


    char* str4 = "[1,3,2,5,3,null,9]";
    TreeNode* tree4 = bt.generateTree(str4);
    i = bt.widthOfBinaryTree(tree4);

    char* str5 = "[1,4,5,4,4,5]";
    TreeNode* tree5 = bt.generateTree(str5);
    i = bt.longestUnivaluePath(tree5);

    char* str6 = "[5,3,6,2,4,null,8,1,null,null,null,7,9]";
    TreeNode* tree6 = bt.generateTree(str6);
    bt.increasingBST(tree6);
    vector<vector<int>> relation = {{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}};
    //bt.findCircleNum(relation);
    vector<vector<int>> relation1 = {{0,0,0},{0,1,0},{1,1,1}};
    relation1 = bt.updateMatrix(relation1);
    */
    char* str7 = "[1,2,3,4,5]";
    TreeNode* tree7 = bt.generateTree(str7);
    int j = bt.diameterOfBinaryTree(tree7);
    vector<int> pre = {1, 2, 4, 5, 3, 6, 7};
    vector<int> post = {4, 5, 2, 6, 3, 7, 1};
    bt.constructFromPrePost3(pre, post);
    TreeNode* tree8 = bt.generateTree("[10,5,-3,3,2,null,11,3,-2,null,1]");
    bt.pathSum32(tree8, 8);
    TreeNode* tree9 = bt.generateTree("[1,4,5,4,4,null,5]");
    bt.longestUnivaluePath4(tree9);
    j = 0;
}

static int isdigit(const char c)
{
    if ((c >= '0' && c <= '9')|| c == '.' || c == '-' || c == 'n')
    {
        return 1;
    }
    return 0;
}

TreeNode *BalanceTree::generateTree(char *input)
{
    char* p = input;
    while(*p != '[') p++;
    p++;
    std::queue<TreeNode*> v;
    TreeNode* cur = nullptr;
    TreeNode* ret = nullptr;
    int status = 0;
    int anchor = 0;
    while(*p && (*p != ']'))
    {
        if(isdigit(*p))
        {
            if(*p == 'n')
            {
                p += 4;
                if(status == 0)
                {
                    status++;
                }
                else
                {
                    if(!v.empty())
                    {
                        cur = v.front();
                        v.pop();
                        status = 0;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                int val = atoi(p);
                while(isdigit(*p))
                {
                    p++;
                }
                TreeNode* newNode = new TreeNode(val);
                if(!anchor)
                {
                    ret = newNode;
                    anchor = 1;
                }
                v.push(newNode);
                if(!cur)
                {
                    cur = v.front();
                    v.pop();
                    status = 0;
                }
                else
                {
                    if(status == 0)
                    {
                        cur->left = newNode;
                        status = 1;
                    }
                    else
                    {
                        cur->right = newNode;
                        if(!v.empty())
                        {
                            cur = v.front();
                            v.pop();
                            status = 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        }
        if(*p == ']')
        {
            break;
        }
        p++;
    }

    return ret;
}



bool BalanceTree::isBalanced(TreeNode *root)
{
    if(!root)
    {
        return true;
    }
    bool result = true;
    treeHight(root, result);
    return result;
}

int BalanceTree::treeHight(TreeNode *root, bool &result)
{
    if(!root)
    {
        return 0;
    }
    int a = treeHight(root->left, result);
    int b = treeHight(root->right, result);
    if(abs(a-b) <= 1) result = false;
    return 1 + std::max(a, b);
}
struct TreeNodeWithDepth
{
    TreeNodeWithDepth(TreeNode* p, int depth){_p =p; _depth=depth;}
    TreeNode* _p;
    int       _depth;
};
int BalanceTree::minDepth(TreeNode *root)
{
    if(!root)
    {
        return 0;
    }

    std::queue<TreeNodeWithDepth> q;
    q.push(TreeNodeWithDepth(root, 1));
    while(!q.empty())
    {
        TreeNodeWithDepth& temp = q.front();
        q.pop();
        if(!(temp._p->left && temp._p->right))
            return temp._depth;
        if(temp._p->left) q.push(TreeNodeWithDepth(temp._p->left, temp._depth+1));
        if(temp._p->right) q.push(TreeNodeWithDepth(temp._p->right, temp._depth+1));
    }
    return 0;
}
/*
 * Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \      \
7    2      1
 */
bool BalanceTree::SumPath(TreeNode *root, int sum)
{
    std::stack<TreeNodeWithDepth> s;
    s.push(TreeNodeWithDepth(root, root->val));
    printf("push node, val=[%d], sum=[%d]\n", root->val, root->val);
    while (!s.empty())
    {
//        for(int i = 0; i < s.size(); ++i)
//        {
//            printf("node val=[%d], sum=[%d]\n", s[i]._p->val, s[i]._depth);
//        }
        TreeNodeWithDepth temp = s.top();
        //printf("node val=[%d], sum=[%d]\n", temp._p->val, temp._depth);
        s.pop();
        if(!(temp._p->left || temp._p->right) && (temp._depth == sum))
        {
            return true;
        }
        if(temp._p->left)
        {
            printf("push node, val=[%d], sum=[%d]\n", temp._p->left->val, temp._depth+temp._p->left->val);
            s.push(TreeNodeWithDepth(temp._p->left, temp._depth+temp._p->left->val));
        }
        if(temp._p->right)
        {
            printf("push node, val=[%d], sum=[%d]\n", temp._p->right->val, temp._depth+temp._p->right->val);
            s.push(TreeNodeWithDepth(temp._p->right, temp._depth+temp._p->right->val));
        }
    }
    return false;
}

int BalanceTree::SumPathIII(TreeNode *root, int sum)
{
    /*
    if(!root)
    {
        return 0;
    }
    std::stack<TreeNodeWithDepth> s;
    s.push(TreeNodeWithDepth(root, root->val));
    int ret = 0;
    printf("push node, val=[%d], sum=[%d]\n", root->val, root->val);
    while (!s.empty())
    {
        TreeNodeWithDepth temp = s.top();
        s.pop();
        if(temp._depth == sum)
        {
            ret++;
        }
        if(temp._p->left)
        {
            printf("push node, val=[%d], sum=[%d]\n", temp._p->left->val, temp._depth+temp._p->left->val);
            s.push(TreeNodeWithDepth(temp._p->left, temp._depth+temp._p->left->val));
        }
        if(temp._p->right)
        {
            printf("push node, val=[%d], sum=[%d]\n", temp._p->right->val, temp._depth+temp._p->right->val);
            s.push(TreeNodeWithDepth(temp._p->right, temp._depth+temp._p->right->val));
        }
    }
    */
    if(!root) return 0;
    std::stack<TreeNodeWithDepth> s;

    return 0;
}

void pre(TreeNode* T , vector<vector<int> >& vec ,int level)
{
    if(T==nullptr) return;
    if(level > vec.size())
    {
        vector<int>  vec1(0);
        vec1.push_back(T->val);
        vec.push_back(vec1);
    }
    else vec[level-1].push_back(T->val);
    pre(T->left , vec , level+1);
    pre(T->right , vec , level+1);
}

vector<vector<int> > BalanceTree::levelOrderBottom1(TreeNode* root) {
    vector<vector<int> > vec(0);
    pre(root, vec,1);
    reverse(vec.begin(),vec.end());
    return vec;
}

int BalanceTree::ladderLength(string beginWord, string endWord, vector<string> &wordList)
{
    int step = 1;
    queue<string> cur;
    queue<string> next;
    cur.push(beginWord);

    while (!cur.empty())
    {
        step++;
        while(!cur.empty())
        {
            string str = cur.front();
            cur.pop();
            vector<string>::iterator it = wordList.begin();
            while(it != wordList.end())
            {
                if(1 == WordGap(str, *it))
                {
                    if(0 == (*it).compare(endWord))
                    {
                        return step;
                    }
                    next.push(*it);
                    it = wordList.erase(it++);
                }
                else
                {
                    it++;
                }
            }
        }
        cur = next;
    }
    return 0;
}

int BalanceTree::ladderLength1(string beginWord, string endWord, vector<string> &wordList)
{
    queue<string> qf;
    queue<string> qb;
    int endwordPos = -1;
    for(int i=0; i<wordList.size(); ++i)
    {
        if(wordList[i] == endWord)
        {
            endwordPos = i;
        }
    }
    if(endwordPos < 0)
    {
        return 0;
    }
    qf.push(beginWord);
    qb.push(endWord);

    int flen = 0;
    int blen = 0;
    vector<int> visited;
    visited.assign(wordList.size(), 0);
    visited[endwordPos] = 2;
    while (!qf.empty() || !qb.empty())
    {
        int fret = bfsForlength(qf, flen, wordList, visited, 1);
        if(0 == fret)
        {
            return flen + blen+1;
        }

        int bret = bfsForlength(qb, blen, wordList, visited, 2);
        if(0 == bret)
        {
            return flen + blen+1;
        }
    }
    return 0;
}

struct node
{
    node(string s1): val(s1), parent(nullptr), child(nullptr), brother(nullptr)
    {}
    string val;
    node* parent;
    node* child;
    node* brother;
};

vector<vector<string> > BalanceTree::findLadders(string beginWord, string endWord, vector<string> &wordList)
{
    //bfs
    vector<string> result;
    vector<vector<string> > results;

    queue<node*> cur;
    node* root = new node(beginWord);
    cur.push(root);

    while(!cur.empty())
    {
        node* pnode = cur.front();
        cur.pop();
        vector<string>::iterator it = wordList.begin();
        while(it != wordList.end())
        {
            if(1 == WordGap(pnode->val, *it))
            {
                if(0 == (*it).compare(endWord))
                {
                    result.clear();
                    result.push_back(endWord);
                    result.push_back(pnode->val);
                    node* parent = pnode->parent;
                    while(parent)
                    {
                        result.push_back(parent->val);
                        parent = parent->parent;
                    }
                    reverse(result.begin(), result.end());
                    results.push_back(result);
                    it++;
                }
                else
                {
                    node* new_node = new node(*it);
                    new_node->parent = pnode;
                    if(pnode->child)
                    {
                        new_node->brother = pnode->child;
                        pnode->child = new_node;
                    }

                    cur.push(new_node);
                    it = wordList.erase(it++);
                }

            }
            else
            {
                ++it;
            }
        }
    }

    return results;
}

vector<vector<string> > BalanceTree::findLadders2(string beginWord, string endWord, vector<string> &wordList)
{
    //dbfs
    vector<vector<string> > results;
    if(wordList.end() == find(wordList.begin(), wordList.end(), endWord))
    {
        return results;
    }



    return results;
}

int BalanceTree::WordGap(string& left, string& right)
{
    if(left.length() != right.length())
    {
        return -1;
    }
    int gap = 0;
    for(int i=0; i < left.length(); ++i)
    {
        if(left[i] != right[i])
        {
            gap++;
        }
    }
    return gap;
}

StringTreeNode *BalanceTree::generateTree(string beginWord, vector<string> &wordList)
{
    vector<vector<string> > wordListList;
    int wordSize = beginWord.size();
    wordListList.reserve(beginWord.size());

    while(wordSize)
    {
        wordListList.push_back(vector<string>());
        wordSize--;
    }

    vector<string>::iterator it = wordList.begin();
    for(; it != wordList.end(); ++it)
    {
        int gap = 0;
        for(int i = 0; i < beginWord.size(); ++i)
        {
            if(beginWord[i] != (*it)[i])
            {
                gap++;
            }
        }
        wordListList[gap].push_back(*it);
    }

    StringTreeNode* root = new StringTreeNode(beginWord);


    return nullptr;
}

int BalanceTree::bfsForlength(queue<string> &qs, int& step, vector<string>& wordList, vector<int>& visited, int flag)
{
    if(!qs.empty())
    {
        step++;
        int size = qs.size();
        for(int i=0; i < size; ++i)
        {
            string str = qs.front();
            qs.pop();
            for(int i=0; i<wordList.size(); ++i)
            {
                if(visited[i] == flag)
                {
                    continue;
                }
                if(1 == WordGap(str, wordList[i]))
                {
                    if(visited[i] == 0)
                    {
                        visited[i] = flag;
                        qs.push(wordList[i]);
                    }
                    else
                    {
                        //matched ans
                        return 0;
                    }
                }
            }
        }
    }
    return -1;
}

vector<vector<int> > BalanceTree::levelOrderBottom(TreeNode *root)
{
    vector<vector<int> > vv;
    if(!root)
    {
        return vv;
    }
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty())
    {
        TreeNode* p = s.top();
        printf("%d ", p->val);
        s.pop();
        if(p->right)
        {
            s.push(p->right);
        }

        if(p->left)
        {
            s.push(p->left);
        }

    }
    return vv;
}
