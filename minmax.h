#ifndef MINMAX_H
#define MINMAX_H

#include <set>

using namespace std;
class minMax
{
public:
    minMax();

    int minMaxTree( bool turn, set<int> &cho, int goal, int now, int a, int b )
    {
        if(now>=goal)
        {
            if(turn)
                return -1;
            else return 1;
        }
        set<int>::iterator itr;
        if(turn)//max方
        {
            for(itr=cho.begin();itr!=cho.end();itr++)
            {
                set<int> tmp = cho;
                tmp.erase(tmp.find(*itr));
                a = minMaxTree(0,tmp,goal,now+*itr,a,b);
                if(a>=b)
                    break;
            }
        }
        else
        {
            for(itr=cho.begin();itr!=cho.end();itr++)
            {
                set<int> tmp = cho;
                tmp.erase(tmp.find(*itr));
                b = minMaxTree(1,tmp,goal,now+*itr,a,b);
                if(a>=b)
                    break;
            }
        }
        if(turn) return a;
        else return b;
    }
};

#endif // MINMAX_H
