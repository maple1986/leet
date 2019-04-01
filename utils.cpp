#include "utils.h"
#include "stdio.h"
#include <iostream>

using namespace std;
void Utils::printV(vector<int> &v)
{
    for(int i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}

void Utils::printVV(vector<vector<int> > &vv)
{
    for(auto& v : vv)
    {
        printV(v);
    }
    cout << endl;
}

void Utils::printVS(vector<string> &s)
{
    for(string& c: s)
    {
        cout<<c.c_str()<<" ";
    }
    printf("\n");
}

void Utils::printVVS(vector<vector<string> > &vv)
{
    for(auto& v : vv)
    {
        printVS(v);
    }
    printf("\n");
}

void Utils::printVC(vector<char>& v)
{
}

void Utils::printVVC(vector<vector<char>>& v)
{

}
