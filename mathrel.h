#ifndef MATHREL_H
#define MATHREL_H

#include <math.h>
#include <algorithm>

class MathRel
{
public:
    MathRel();
    static void test();
    int binaryGap(int N)
    {
        int maxGap = 0;
        int last = -1, pos = 0;
        while (N)
        {
            if(N&0x01)
            {
               if(last != -1)
               {
                    maxGap = std::max(maxGap, pos - last);
                    last = pos;
               }
               else
               {
                   last = pos;
               }
            }
            N = N >> 1;
            ++pos;
        }

        return maxGap;
    }
};

#endif // MATHREL_H
