#include "bfs.h"
#include <queue>
BFS::BFS()
{

}

void BFS::test()
{
    vector<vector<int>> graph = {{1,2,3},{0},{0},{0}};
    BFS bfs;
    int i = bfs.shortestPathLength(graph);
    string orig = "hit";
    string end  = "cog";
    vector<string> list =  {"hot","dot","dog","lot","log","cog"};
    i = bfs.ladderLength2(orig, end, list);
    vector<vector<int>> grid = {{0,1,0,0,0},{1,0,0,2,1},{0,1,0,0,0}};
    i = bfs.shortestDistance(grid);
    i = 0;
}

vector<vector<string>> BFS::findLadders(string beginWord, string endWord, vector<string>& wordList) {
    vector<string> result;
    vector<vector<string> > results;
    vector<vector<string> > path;
    queue<string> q;
    /*
    while(!q.empty())
    {
        int size = q.size();
        for(int i=0; i<size; ++i)
        {
            string str = q.front();
            q.pop();

            auto it = wordList.begin();
            while(it != wordList.end())
            {
                if(1 == WordGap(str, *it))
                {
                    q.push();
                    wordList.erase(it++);
                }
                else
                {
                    ++it;
                }
            }
        }
        if(!results.empty())
        {
            break;
        }

    }
    */
    return results;
}

int BFS::WordGap(string& left, string& right)
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
