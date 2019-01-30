#include "utils.h"
#include "stdio.h"


void Utils::printV(vector<int> &v)
{
    for(int i : v)
    {
        printf("%d ", i);
    }
    printf("\n");
}

void Utils::printVV(vector<vector<int> > &vv)
{
    for(auto& v : vv)
    {
        printV(v);
    }
    printf("\n");
}

void Utils::printVC(vector<char>& v)
{
}

void Utils::printVVC(vector<vector<char>>& v)
{

}
