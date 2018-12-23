#ifndef GRAPH1_H
#define GRAPH1_H

#include <vector>
#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <queue>

using namespace std;


struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

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

    bool isSentenceSimilarity(vector<string> &words1, vector<string> &words2, vector<vector<string>> &pairs) {
        if(words1.size() != words2.size())
        {
            return false;
        }
        int n = words1.size();
        if(n == 0) return true;
        unordered_map<string, unordered_set<string>> graph;
        //build graph
        for(auto& eachpair : pairs)
        {
            graph[eachpair[0]].insert(eachpair[1]);
            graph[eachpair[1]].insert(eachpair[0]);
        }
        for(int i=0; i<n; ++i)
        {
            if(words1[i] == words2[i])
            {
                continue;
            }
            if(!graph.count(words1[i]))
            {
                return false;
            }
            if(!graph[words1[i]].count(words2[i]))
            {
                return false;
            }
        }
        return true;
    }

    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return NULL;
        queue<UndirectedGraphNode*> q;
        UndirectedGraphNode* copy = new UndirectedGraphNode(node->label);
        mp[node] = copy;
        q.push(node);
        while(!q.empty())
        {
            UndirectedGraphNode* curr = q.front();
            q.pop();
            for(UndirectedGraphNode* next : curr->neighbors)
            {
                if(!mp.count(next))
                {
                    UndirectedGraphNode* neigh = new UndirectedGraphNode(next->label);
                    mp[next] = neigh;
                    q.push(next);
                }

                mp[curr]->neighbors.push_back(mp[next]);
            }
        }
        return copy;
    }

    unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> mp;

    UndirectedGraphNode *cloneGraph1(UndirectedGraphNode *node) {
        if(!node) return NULL;
        if(!mp.count(node))
        {
            mp[node] = new UndirectedGraphNode(node->label);
            for(UndirectedGraphNode* neigh : node->neighbors)
            {
                mp[node]->neighbors.push_back(cloneGraph(neigh));
            }
        }
        return mp[node];
    }

    bool validTree(int n, vector<vector<int>> &edges) {
        // write your code here
        if(n == 0) return false;
        //if(edges.size() < n-1) return false;
        vector<int> visited(n, 0);
        unordered_map<int, vector<int>> graph;
        for(const auto& edge:edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        queue<int> q;
        q.push(0);
        visited[0] = 1;
        while(!q.empty())
        {
            int cur = q.front();
            q.pop();
            for(const int e: graph[cur])
            {
                if(visited[e]) return false;
                visited[e] = 1;
                q.push(e);
            }
        }
        for(int v:visited)
        {
            if(v == 0)
            {
                return false;
            }
        }
        return true;
    }

};

#endif // GRAPH1_H
