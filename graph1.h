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
    UndirectedGraphNode(int x) : label(x) {}
};

struct DirectedGraphNode {
    int label;
    vector<DirectedGraphNode *> neighbors;
    DirectedGraphNode(int x) : label(x) {}
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


    UndirectedGraphNode *cloneGraph2(UndirectedGraphNode *node) {
        //if(!node) return NULL;
        unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> mptable;
        return dfs(node, mptable);
    }

    UndirectedGraphNode *dfs(UndirectedGraphNode *node, unordered_map<UndirectedGraphNode*, UndirectedGraphNode*>& mptable)
    {
        if(!node) return NULL;
        if(mptable[node]) return mptable[node];
        UndirectedGraphNode* copy = new UndirectedGraphNode(node->label);
        mptable[node] = copy;
        for(auto& nb: node->neighbors)
        {
            copy->neighbors.push_back(dfs(nb, mptable));
        }
        return copy;
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

    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        unordered_map<int, vector<int>> graph;
        for(int i=0; i<edges.size(); ++i)
        {
            graph[edges[i].first].push_back(edges[i].second);
            graph[edges[i].second].push_back(edges[i].first);
        }
        queue<int> q;
        for(auto& v: graph)
        {
            if(v.second.size() == 1)
                q.push(v.first);
        }
        while(!q.empty())
        {
            int v = q.front();q.pop();

        }

    }
    //topologic
    bool isCyclicGraph1(vector<int> &start, vector<int> &end) {
        unordered_map<int, vector<int>> graph;
        unordered_map<int, int> indgree;
        for(int i=0; i<start.size(); ++i)
        {
            graph[start[i]].push_back(end[i]);
            indgree[end[i]]++;
        }
        queue<int> q;
        for(auto& v: graph)
        {
            if(!indgree.count(v.first))
            {
                q.push(v.first);
            }
        }
        while(!q.empty())
        {
            int v = q.front(); q.pop();
            for(int e: graph[v])
            {
                indgree[e]--;
                if(indgree[e]==0) q.push(e);
            }
        }
        for(auto& v: indgree)
        {
            if(indgree[v.first] != 0)
                return true;
        }
        return false;
    }

    bool isCyclicGraph(vector<int> &start, vector<int> &end) {
        unordered_map<int, vector<int>> graph;
        for(int i=0; i<start.size(); ++i)
        {
            graph[start[i]].push_back(end[i]);
        }
        for(int s: start)
        {
            unordered_set<int> vistied;
            if(dfs(s, vistied, graph))
            {
                return true;
            }
        }
        return false;
    }

    bool dfs(int start, unordered_set<int>& visited, unordered_map<int, vector<int>>& graph)
    {
        if(visited.count(start))
        {
            return true;
        }
        visited.insert(start);
        if(!graph.count(start))
            return false;
        for(int i: graph[start])
        {
            if(dfs(i, visited, graph))
                return true;
        }
        return false;
    }

    int sixDegrees(vector<UndirectedGraphNode*> graph, UndirectedGraphNode* s, UndirectedGraphNode* t) {
        if(s == t) return 0;

        unordered_set<UndirectedGraphNode*> visited;
        queue<UndirectedGraphNode*> todo;
        todo.push(s);
        visited.insert(s);
        int step = 0;
        while(!todo.empty())
        {
            int size = todo.size();
            while(size--)
            {
                UndirectedGraphNode* top = todo.front();
                todo.pop();
                if(top == t) return step;
                for(UndirectedGraphNode* next: graph[top->label-1]->neighbors)
                {
                    if(visited.count(next)) continue;
                    todo.push(next);
                    visited.insert(next);    
                }
                step++;
            }
        }
        return -1;
    }

    int sixDegrees2(vector<UndirectedGraphNode*> graph, UndirectedGraphNode* s, UndirectedGraphNode* t) {
        if(s == t) return 0;

        unordered_set<UndirectedGraphNode*> visited;
        queue<pair<UndirectedGraphNode*,int>> todo;
        todo.push({s, 0});
        visited.insert(s);
        //int step = 0;
        while(!todo.empty())
        {
            int size = todo.size();
            while(size--)
            {
                auto top = todo.front();
                todo.pop();
                if(top.first == t) return top.second;
                for(UndirectedGraphNode* next: top.first->neighbors)
                {
                    if(visited.count(next)) continue;
                    todo.push({next, top.second+1});
                    visited.insert(next);    
                }
                //step++;
            }
        }
        return -1;
    }

    vector<vector<int>> connectedSet(vector<UndirectedGraphNode*> nodes) {
        // write your code here
        unordered_set<UndirectedGraphNode*> visited;
        vector<vector<int>> res;
        for(auto node: nodes)
        {
            
            if(visited.count(node)) continue;
            visited.insert(node);
            vector<int> cur;
            cur.push_back(node->label);
            queue<UndirectedGraphNode*> todo;
            todo.push(node);
            while(!todo.empty())
            {
                auto top = todo.front();
                todo.pop();
                for(UndirectedGraphNode* next: top->neighbors)
                {
                    if(visited.count(next)) continue;
                    cur.push_back(next->label);
                    todo.push(next);
                    visited.insert(next);    
                }
            }
            res.push_back(cur);
        }
        return res;
    }

    bool hasRoute(vector<DirectedGraphNode*> graph, DirectedGraphNode* s, DirectedGraphNode* t) {
        if(s == t) return 0;

        unordered_set<DirectedGraphNode*> visited;
        visited.insert(s);
        queue<DirectedGraphNode*> todo;
        todo.push(s);
        while(!todo.empty())
        {
            auto top = todo.front();
            todo.pop();
            if(top == t) return true;
            for(DirectedGraphNode* next: top->neighbors)
            {
                if(visited.count(next)) continue;
                todo.push(next);
                visited.insert(next);    
            }
        }
        return false;
    }
};

#endif // GRAPH1_H
