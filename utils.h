#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

using namespace std;
class Utils
{
public:
    //Utils();
    static void printV(vector<int>& v);
    static void printVV(vector<vector<int>>& vv);

    static void printVS(vector<string>& s);
    static void printVVS(vector<vector<string>>& vv);

    static void printVC(vector<char>& v);
    static void printVVC(vector<vector<char>>& v);
};

#endif // UTILS_H
