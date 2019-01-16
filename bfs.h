#ifndef BFS_H
#define BFS_H

#include <vector>
#include <string>
#include <balancetree.h>
using namespace std;

class BFS
{
  public:
    BFS();
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList);
    int WordGap(string &left, string &right);
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
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && matrix[nx][ny] == 1)
                    {
                        //res[nx][ny] = step;
                        matrix[nx][ny] = step;
                        //q.push({nx, ny});
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

    int shortestPathLength(vector<vector<int>> &graph)
    {

        //queue<int> q;
        //q.push();
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

    int shortestDistance(vector<vector<int>> &grid)
    {
        // write your code here
        if (grid.empty() || grid[0].empty())
            return 0;
        int m = grid.size();
        int n = grid[0].size();
        //vector<int> rows, cols;
        vector<pair<int, int>> houses;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)
                {
                    houses.push_back({i, j});
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
                    for (auto &h : houses)
                    {
                        sum += calcDistance(h.first, h.second, i, j);
                    }
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
};

#endif // BFS_H
