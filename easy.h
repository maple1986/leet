#ifndef EASY_H
#define EASY_H

#include <vector>
#include <algorithm>
using namespace std;
class easy
{
public:
    easy();
    static void test()
    {

    }

    bool isOneBitCharacter(vector<int>& bits)
    {
        if(bits.empty()) return false;
        int size = bits.size();
        if(bits[size-1]) return false;
        bool res = false;
        for(int i=0; i<size;)
        {
            if(i == size-1)
            {
                res = true;
                break;
            }
            if(bits[i] == 1)
            {
                i += 2;
            }
            else
            {
                i += 1;
            }

        }
        return res;
    }

    int arrangeCoins(int n)
    {
        return 0;
    }
};

#endif // EASY_H
