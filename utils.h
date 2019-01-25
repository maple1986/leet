#ifndef UTILS_H
#define UTILS_H

#include <vector>

using namespace std;
class Utils
{
public:
    //Utils();
    static void printV(vector<int>& v);
    static void printVV(vector<vector<int>>& vv);

    static void printVC(vector<char>& v);
    static void printVVC(vector<vector<char>>& v);
};

#endif // UTILS_H
