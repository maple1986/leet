#ifndef GRAPH1_H
#define GRAPH1_H

#include <vector>
#include <unordered_map>
#include <stack>
#include <unordered_set>

using namespace std;

class Graph1
{
public:
    Graph1();
    static void test();

    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites)
    {
        if(numCourses < 1) return true;
        vector<vector<int>> graph(numCourses, vector<int>());
        for(auto& prerequisite : prerequisites)
        {
            graph[prerequisite.second].push_back(prerequisite.first);
        }

        for(int i=0; i<numCourses; ++i)
        {
            if(_visited.count(i)) continue;
            _visiting.clear();
            if(!visit(i, graph))
            {
                return false;
            }
            _visited.insert(_visiting.begin(), _visiting.end());
            //visiting_courses.push_back();
            //dfs();
        }
        return true;
    }

    bool visit(int course, vector<vector<int>>& graph)
    {
        if(graph[course].empty()) return true;
        for(int i=0; i<graph[course].size(); ++i)
        {
            if(_visiting.count(i)) return false;
            if(!visit(graph[course][i], graph)) return false;
        }
        return true;
    }
    unordered_set<int> _visited;
    unordered_set<int> _visiting;
};

#endif // GRAPH1_H
