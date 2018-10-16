#ifndef SORTREL_H
#define SORTREL_H

#include <vector>
#include <algorithm>
using namespace std;

class sortrel
{
public:
    sortrel();
    int findRadius(vector<int>& houses, vector<int>& heaters)
    {
        int radius = max(abs(houses.front()-heaters.front()), abs(houses.back() - heaters.back()));
        //int radius = *(houses.begin())-*(heaters.begin());
        for(int i=1; i<heaters.size(); ++i)
        {
            radius = max(radius, (heaters[i]-heaters[i-1])/2);
        }
        return radius;
    }
};

#endif // SORTREL_H
