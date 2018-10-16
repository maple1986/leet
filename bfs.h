#ifndef BFS_H
#define BFS_H

#include <vector>
#include <string>

using namespace std;

class BFS
{
public:
    BFS();
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList);
    int WordGap(string& left, string& right);
};

#endif // BFS_H
