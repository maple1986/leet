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
