#ifndef BFS_H
#define BFS_H

#include <vector>
#include <string>
#include <balancetree.h>
#include <graph1.h>
using namespace std;

class BFS
{
  public:
    BFS();
    static void test();
    /*
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if(!dict.count(endWord)) return 0;

        queue<string> cur;
        cur.push(beginWord);
        int step = 0;

        //wordList.push_back(endWord);
        while (!cur.empty())
        {
            int size = cur.size();
            while(--size)
            {
                string str = cur.front();
                cur.pop();
                if(str == endWord) return step;

                unordered_set<string> dict2(dict);
                for(string word: dict2)
                {
                    if(1 == WordGap(str, word))
                    {
                        cur.push(word);
                        dict.erase(word);
                    }
                }
            }
            step++;
        }
        return 0;
    }
    */
    int ladderLength2(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if(!dict.count(endWord)) return 0;

        unordered_set<string> front;
        unordered_set<string> back;
        front.insert(beginWord);
        back.insert(endWord);
        int step = 0;

        while (!front.empty() && !back.empty())
        {
            if(front.size() > back.size())
                front.swap(back);
            unordered_set<string> expand;
            for(string s: front)
            {
                if(back.count(s)) return step+1;
                addWords(expand, dict, s);
            }
            front.swap(expand);
            step++;
        }
        return 0;
    }

    void addWords(unordered_set<string>& todo, unordered_set<string>& dict, string word) {
        for (int i = 0; i < word.size(); i++) {
            char t = word[i];
            for (int j = 0; j < 26; j++) {
                word[i] = 'a' + j;
                if (dict.find(word) != dict.end()) {
                    todo.insert(word);
                    dict.erase(word);
                }
            }
            word[i] = t;
        }
    }

    vector<vector<int>> updateMatrix(vector<vector<int>> &matrix)
    {
        vector<vector<int>> res;
        int m = matrix.size();
        if (!m)
            return res;
        int n = matrix[0].size();
        if (!n)
            return res;

        for (int i = 0; i < m; ++i)
        {
            vector<int> tmp;
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    tmp.push_back(0);
                }
                else
                {
                    tmp.push_back(m + n);
                }
            }
            res.push_back(tmp);
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (res[i][j] != 0)
                {
                }
            }
        }
        return res;
    }

    vector<vector<int>> updateMatrix2(vector<vector<int>> &matrix)
    {
        if (matrix.empty() || matrix[0].empty())
            return matrix;
        int m = matrix.size();
        int n = matrix[0].size();
        //vector<vector<int>> visited(m, vector<int>(n, 0));
        queue<pair<int, int>> q;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    //matrix[i][j] = -1;
                    q.push({i, j});
                }
                if (matrix[i][j] == 1)
                {
                    matrix[i][j] = INT_MAX;
                }
            }
        }
        int step = 1;
        vector<int> dx = {0, 1, 0, -1};
        vector<int> dy = {1, 0, -1, 0};
        while (!q.empty())
        {
            int size = q.size();
            while (size--)
            {
                pair<int, int> cood = q.front();
                int x = cood.first, y = cood.second;
                q.pop();
                for (int i = 0; i < dx.size(); ++i)
                {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && matrix[nx][ny] == INT_MAX)
                    {
                        matrix[nx][ny] = step;
                        q.push({nx, ny});
                    }
                }
            }
            step++;
        }

        return matrix;
    }

    vector<vector<int>> levelOrder(NAryNode *root)
    {
        vector<vector<int>> res;
        if (!root)
            return res;
        queue<NAryNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            vector<int> tmp;
            for (int i = 0; i < size; ++i)
            {
                NAryNode *cur = q.front();
                q.pop();
                tmp.push_back(cur->val);
                for (auto i : cur->children)
                {
                    q.push(i);
                }
            }
        }
        return res;
    }

    int islandPerimeter(vector<vector<int>> &grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;
        int m = grid.size(), n = grid[0].size(), res = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 0)
                    continue;
                res += 4;
                if (i > 0 && grid[i - 1][j] == 1)
                    res--;
                if (i < m - 1 && grid[i + 1][j] == 1)
                    res--;
                if (j > 0 && grid[i][j - 1] == 1)
                    res--;
                if (j < n - 1 && grid[i][j + 1] == 1)
                    res--;
            }
        }
        return res;
    }

    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int K)
    {
        unordered_map<int, vector<pair<int, int>>> graph;
        for (const auto &flight : flights)
        {
            graph[flight[0]].emplace_back(flight[1], flight[2]);
        }

        int res = INT_MAX;
        queue<pair<int, int>> q;
        q.push({src, 0});
        int steps = 0;
        while (!q.empty())
        {
            int size = q.size();
            while (size--)
            {
                int cur = q.front().first;
                int cost = q.front().second;
                if (cur == dst)
                {
                    res = min(res, cost);
                }

                for (const auto &p : graph[cur])
                {
                    if (cost + p.second > res)
                        continue;
                    q.push({p.first, cost + p.second});
                }
            }
            if (steps++ > K)
                break;
        }
        return res == INT_MAX ? -1 : res;
    }

    int shortestBridge(vector<vector<int>> &A)
    {
    }

    int maxVacationDays(vector<vector<int>> &flights, vector<vector<int>> &days)
    {
    }

    vector<int> findMinHeightTrees(int n, vector<pair<int, int>> &edges)
    {
        unordered_map<int, vector<int>> graph;
        for (auto &edge : edges)
        {
            graph[edge.first].push_back(edge.second);
            graph[edge.second].push_back(edge.first);
        }
    }
    /*
     * Your input
[[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
Output
[[0,1,0],[1,0,1],[1,1,1],[0,1,0]]
Expected
[[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
    */
    //define 0, 1, 2, 3 2 live->dead -1 dead->live
    void gameOfLife(vector<vector<int>> &board)
    {
        if (board.empty() || board[0].empty())
            return;
        int m = board.size();
        int n = board[0].size();
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                check(board, i, j);
            }
        }
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (board[i][j] == 2)
                    board[i][j] = 0;
                if (board[i][j] == -1)
                    board[i][j] = 1;
            }
        }
        return;
    }

    vector<pair<int, int>> directions_ = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    void check(vector<vector<int>> &board, int i, int j)
    {
        int surround = 0;
        int m = board.size();
        int n = board[0].size();
        for (const auto &d : directions_)
        {
            int dx = i + d.first;
            int dy = j + d.second;
            if (dx >= 0 && dx < m && dy >= 0 && dy < n && board[dx][dy] >= 1)
                surround++;
        }
        if (board[i][j])
        {
            if (surround < 2 || surround > 3)
            {
                board[i][j] = 2;
            }
        }
        else
        {
            if (surround == 3)
            {
                board[i][j] = -1;
            }
        }
        return;
    }

    vector<vector<int>> policeDistance(vector<vector<int>> &matrix)
    {
        if (matrix.empty() || matrix[0].empty())
            return matrix;
        int m = matrix.size();
        int n = matrix[0].size();
        //vector<vector<int>> res(matrix);
        queue<pair<int, int>> q;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == 1)
                {
                    q.push({i, j});
                    matrix[i][j] = -2;
                }
            }
        }
        int step = 1;
        while (!q.empty())
        {
            int size = q.size();
            while (size--)
            {
                pair<int, int> cood = q.front();
                int x = cood.first, y = cood.second;
                q.pop();
                vector<int> dx = {0, 1, 0, -1};
                vector<int> dy = {1, 0, -1, 0};
                for (int i = 0; i < dx.size(); ++i)
                {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && matrix[nx][ny] == 0)
                    {
                        //res[nx][ny] = step;
                        matrix[nx][ny] = step;
                        q.push({nx, ny});
                    }
                }
            }
            step++;
        }
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == -2)
                {
                    //q.push({i, j});
                    matrix[i][j] = 0;
                }
            }
        }
        return matrix;
    }

    void wallsAndGates(vector<vector<int>> &rooms)
    {
        queue<pair<int, int>> q;
        for (int i = 0; i < rooms.size(); ++i)
        {
            for (int j = 0; j < rooms[i].size(); ++j)
            {
                if (rooms[i][j] == 0)
                    q.push({i, j});
            }
        }
        int step = 1;
        vector<int> dx = {0, 1, 0, -1};
        vector<int> dy = {1, 0, -1, 0};
        while (!q.empty())
        {
            int size = q.size();
            while (size--)
            {
                auto cood = q.front();
                q.pop();
                for (int i = 0; i < dx.size(); ++i)
                {
                    int nx = cood.first + dx[i];
                    int ny = cood.second + dy[i];
                    if (rooms[nx][ny] > step)
                    {
                        rooms[nx][ny] = step;
                        q.push({nx, ny});
                    }
                }
            }
            step++;
        }
        return;
    }

    int shortestDistance2(vector<vector<int>> &grid)
    {
        // write your code here
        if (grid.empty() || grid[0].empty())
            return -1;
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> distance(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)
                {
                    bfs(grid, i, j, distance);
                }
            }
        }
        int res = INT_MAX;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                res = min(res, distance[i][j]);
            }
        }
        return res == INT_MAX ? -1 : res;
    }

    void bfs(vector<vector<int>> &grid, int i, int j, vector<vector<int>> &distance)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        int step = 1;
        while (!q.empty())
        {
            int size = q.size();
            while (size--)
            {
                pair<int, int> cood = q.front();
                int x = cood.first, y = cood.second;
                q.pop();
                vector<int> dx = {0, 1, 0, -1};
                vector<int> dy = {1, 0, -1, 0};
                for (int i = 0; i < dx.size(); ++i)
                {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny] <= 0)
                    {
                        //matrix[nx][ny] = step;
                        distance[nx][ny] += step;
                        q.push({nx, ny});
                    }
                }
            }
            step++;
        }
        return;
    }

    int openLock(vector<string> &deadends, string &target)
    {
        // Write your code here
        string start = "0000";
        if (start == target)
            return 0;
        queue<string> q;
        unordered_set<string> sdeadends(deadends.begin(), deadends.end());
        unordered_set<string> visited;
        if (sdeadends.count(start))
            return -1;
        q.push(start);
        int step = 0;
        while (!q.empty())
        {
            int size = q.size();
            while (size--)
            {
                string &cur = q.front();
                if (cur == target)
                    return step;
                nextValid(cur, sdeadends, visited, q);
                q.pop();
            }
            step++;
        }
        return -1;
    }

    void nextValid(string &origin, unordered_set<string> &deadends, unordered_set<string> &visited, queue<string> &q)
    {
        for (int i = 0; i < 4; ++i)
        {
            string next(origin);
            if (next[i] == '9')
            {
                next[i] = '0';
            }
            else
            {
                next[i]++;
            }
            if (!deadends.count(next) && !visited.count(next))
            {
                visited.insert(next);
                q.push(next);
            }
            next = origin;
            if (next[i] == '0')
            {
                next[i] = '9';
            }
            else
            {
                next[i]--;
            }
            if (!deadends.count(next) && !visited.count(next))
            {
                visited.insert(next);
                q.push(next);
            }
        }
        return;
    }

    int getBestRoad(vector<vector<int>> &grid)
    {
        // Write your code here
        int m = grid.size();
        int n = grid[0].size();
        if (m == 1 && n == 1)
            return 0;
        if (grid[0][0] == 1 && grid.back().back() == 1)
        {
            return -1;
        }
        vector<vector<int>> distanceFromStart(m, vector<int>(n, INT_MAX));
        vector<vector<int>> distanceFromTarget(m, vector<int>(n, INT_MAX));
        bfs(0, 0, grid, distanceFromStart);
        bfs(m - 1, n - 1, grid, distanceFromTarget);
        int res = INT_MAX;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (distanceFromStart[i][j] == INT_MAX || distanceFromTarget[i][j] == INT_MAX)
                    continue;
                res = min(res, distanceFromStart[i][j] + distanceFromTarget[i][j]);
            }
        }
        return res == INT_MAX ? -1 : res;
    }

    void bfs(int sx, int sy, vector<vector<int>> &grid, vector<vector<int>> &distance)
    {

        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        vector<vector<int>> visited(m, vector<int>(n, 0));
        distance[sx][sy] = 0;
        visited[sx][sy] = 1;
        q.push({sx, sy});
        int step = 0;
        while (!q.empty())
        {
            int size = q.size();
            step++;
            while (size--)
            {
                pair<int, int> cur = q.front();
                q.pop();
                vector<int> dx = {0, 1, 0, -1};
                vector<int> dy = {1, 0, -1, 0};
                for (int i = 0; i < dx.size(); ++i)
                {
                    int tx = cur.first + dx[i];
                    int ty = cur.second + dy[i];
                    if (tx >= 0 && tx < m && ty >= 0 && ty < n && !visited[tx][ty])
                    {

                        //if(tgx == tx && tgy == ty) return step;
                        visited[tx][ty] = 1;
                        distance[tx][ty] = step;
                        if (grid[tx][ty] == 0)
                            q.push({tx, ty});
                    }
                }
            }
        }
        return;
    }

    int minMoveStep(vector<vector<int>> &init_state, vector<vector<int>> &final_state)
    {
        // # write your code here
    }

    int shortestDistanceBuildPostOffice(vector<vector<int>> &grid)
    {
        // write your code here
        if (grid.empty() || grid[0].empty())
            return 0;
        int m = grid.size();
        int n = grid[0].size();
        //vector<int> rows, cols;
        vector<int> rows(m, 0);
        vector<int> cols(n, 0);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)
                {
                    //houses.push_back({i, j});
                    rows[i]++;
                    cols[j]++;
                }
            }
        }
        int res = INT_MAX;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 0)
                {
                    int sum = 0;
                    /*
                    for (auto &h : houses)
                    {
                        sum += calcDistance(h.first, h.second, i, j);
                    }
                    */
                    res = min(res, sum);
                }
            }
        }
        return res == INT_MAX ? -1 : res;
    }
    int calcDistance(int dx, int dy, int sx, int sy)
    {
        return abs(dy - sy) + abs(dx - sx);
    }

    int shortestPathLength(vector<vector<int>> &graph)
    {
        if (graph.size() <= 1)
            return 0;
        queue<pair<int, int>> vertex;

        for (int i = 0; i < graph.size(); ++i)
        {
            int state = 1 << i;
            vertex.push({i, state});
        }
        printf("q size[%d]\n", vertex.size());
        unordered_set<int> visited;
        int step = 0;
        int finished = (1 << graph.size()) - 1;
        while (!vertex.empty())
        {
            int size = vertex.size();
            while (size--)
            {
                auto cur = vertex.front();
                vertex.pop();
                int v = cur.first;
                int state = cur.second;
                visited.insert(v << 16 | state);
                if (state == finished)
                    return step;
                for (int i = 0; i < graph[v].size(); ++i)
                {
                    if (visited.count(graph[v][i] << 16 | (state | 1 << graph[v][i])))
                        continue;
                    vertex.push({graph[v][i], state | (1 << graph[v][i])});
                    printf("q size[%d]\n", vertex.size());
                }
            }
            step++;
        }
        return -1;
    }

    bool isBipartite(vector<vector<int>>& graph) {
        if(graph.empty()) return true;
        vector<int> color(graph.size(), 0);
        queue<int> q;
        for(int i=0; i<graph.size(); ++i)
        {
            if(color[i] != 0) continue;
            q.push(i);
            color[i] = 1;
            while(!q.empty())
            {
                int cur = q.front();
                q.pop();
                int c = color[cur];
                for(int j=0; j<graph[cur].size(); ++j)
                {
                    int visit = graph[cur][j];
                    if(color[visit] == c) false;
                    if(color[visit] == -c) continue;
                    color[visit] = -c;
                    q.push(visit);
                }
            }

        }
        return true;
    }

    bool valid(int nx, int ny, int m, int n, vector<vector<int>>& grid, vector<vector<bool>>& flag) {
        if(0 <= nx && nx < m && 0 <= ny && ny < n) {
            if(grid[nx][ny] == 0 && flag[nx][ny] == false) {
                return  true;
            }
        }
        return false;
    }
    int dx[4] = {1,0,-1,0};
    int dy[4] = {0,1,0,-1};
    int shortestDistance(vector<vector<int>> &grid) {
        // write your code here
        if(grid.empty() || grid[0].empty()) return 0;
        int m_ = grid.size(), n_ = grid[0].size();
        int house = 0;
        vector<vector<int>> dist(m_, vector<int>(n_, 0));
        vector<vector<int>> canReach(m_, vector<int>(n_, 0));
        for(int i=0; i<m_; ++i)
        {
            for(int j=0; j<n_; ++j)
            {
                if(grid[i][j] == 1)
                {
                    //bfs
                    house++;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    vector<vector<bool>> flag(m_, vector<bool>(n_, false)) ;
                    int step = 1;
                    while(!q.empty()) {
                        int size = q.size();
                        while(size--)
                        {
                            pair<int, int> now = q.front();
                            q.pop();

                            for(int i = 0; i < 4; i++) {
                                int nx = now.first + dx[i];
                                int ny = now.second + dy[i];
                                if (valid(nx, ny, m_, n_, grid, flag)) {
                                    dist[nx][ny] += step;
                                    canReach[nx][ny]++;
                                    flag[nx][ny] = true;
                                    q.push({nx, ny});
                                }
                            }
                        }
                        step++;
                    }
                }
            }
        }
        Utils::printVV(dist);
        Utils::printVV(canReach);
        int ans = INT_MAX;
        for (int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[i].size(); j++)
                if (grid[i][j] == 0 && canReach[i][j] == house){
                    ans = min(ans, dist[i][j]);
                }
        }
        return ans;
    }
    int ladderLength3(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> dict;
        for (string &s : wordList)
        {
            dict.insert(s);
        }
        if (!dict.count(endWord))
            return false;

        queue<string> cur;
        cur.push(beginWord);

        int step = 0;
        while (!cur.empty())
        {
            int size = cur.size();
            while (size--)
            {
                string str = cur.front();
                cur.pop();
                if (str == endWord)
                    return step;
                for (int i = 0; i < beginWord.length(); ++i)
                {
                    char o = beginWord[i];
                    for (char c = 'a'; c <= 'z'; ++c)
                    {
                        if (c == o)
                            continue;
                        beginWord[i] = c;
                        if (dict.count(beginWord))
                        {
                            cur.push(beginWord);
                            dict.erase(beginWord);
                        }
                    }
                    beginWord[i] = o;
                }
            }
            step++;
        }
        return -1;
    }

    vector<DirectedGraphNode *> topSort(vector<DirectedGraphNode *> &graph)
    {
        // write your code here
        if (graph.empty())
            return {};
        unordered_map<DirectedGraphNode *, int> inDegree;
        for (auto v : graph)
        {
            for (auto v1 : v->neighbors)
                inDegree[v1]++;
        }
        queue<DirectedGraphNode *> q;
        vector<DirectedGraphNode *> res;
        for (auto v : graph)
        {
            if (!inDegree.count(v) || inDegree[v] == 0)
            {
                q.push(v);
            }
        }
        while (!q.empty())
        {
            auto t = q.front();
            q.pop();
            res.push_back(t);
            for (auto nei : t->neighbors)
            {
                if (--inDegree[nei] == 0)
                {
                    q.push(nei);
                }
            }
        }
        for(auto & kv: inDegree)
        {
            if(kv.second > 0) return {};
        }
        return res;
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (!dict.count(endWord)) return {};

        queue<string> cur;
        cur.push(beginWord);
        unordered_map<string, vector<string>> children;

        bool found = false;
        while (!cur.empty() && !found)
        {
            int size = cur.size();
            while (size--)
            {
                unordered_set<string> deleteStep;
                string str = cur.front();
                string w   = str;
                cur.pop();
                for(int i=0; i<str.length(); ++i)
                {
                    char o = str[i];
                    for(char c='a'; c<='z'; ++c)
                    {
                        if(c == o) continue;
                        str[i] = c;
                        if(endWord == str)
                        {
                            children[w].push_back(str);
                            found = true;
                        }
                        if(dict.count(str))
                        {
                            children[w].push_back(str);
                            cur.push(str);
                            deleteStep.insert(str);
                        }
                    }
                    str[i] = o;
                }
                for(const string& s: deleteStep) dict.erase(s);
            }
        }
        vector<vector<string>> res;
        if(found)
        {
            vector<string> cur;
            hasPath(beginWord, endWord, children, cur, res);
        }

        return {};
    }

void hasPath(string& beginWord, string& endWord, unordered_map<string, vector<string>>& children, vector<string>& cur, vector<vector<string>>& res)
{
    if(beginWord == endWord)
    {
        cur.push_back(endWord);
        res.push_back(cur);
        cur.pop_back();
        return;
    }
    for(string& c: children[beginWord])
    {
        cur.push_back(c);
        hasPath(c, endWord, children, cur, res);
        cur.pop_back();
    }
}

};

#endif // BFS_H
