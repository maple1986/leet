#include "graph1.h"

Graph1::Graph1()
{

}

void Graph1::test()
{
    Graph1 g;
    vector<vector<int>> edges = {{0,1},{0,2},{0,3},{1,4}};
    bool b = g.validTree(5, edges);

    vector<int> start = {1,2,3,3,4,5,6};
    vector<int> end = {2,3,4,5,6,6,7};
    b = g.isCyclicGraph(start, end);
    b = true;
}
